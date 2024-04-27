#!/opt/anaconda/envs/ros2/bin/ python

import serial
from scipy.interpolate import interp1d
import numpy as np
import struct
import rclpy            #change
import rclpy.logging
from rclpy.node import Node  #change
import time
from collections import deque
import threading
from rclpy.qos import qos_profile_sensor_data, qos_profile_system_default
from sensor_msgs.msg import JointState
import signal
import warnings
import sys



warnings.filterwarnings('ignore')
rclpy.init()
logger = rclpy.logging.get_logger("motors_state")

motor_filter_states = [(0,0),(0,0),(0,0)]

#change
class Motor(threading.Thread):

    def __init__(self, ser, id) -> None:
        super().__init__()
        # 运行标志位
        self.running = True
        # 构造串口对象
        self.ser = ser
        self.id = id
        # 扭矩与电流的换算
        _currents = np.array([50,    100,   150,   200,   250,   300,   350,   400,   450,   500,   550,   600,   650,   700,   750  ])
        _torques  = np.array([0.084, 0.155, 0.228, 0.303, 0.380, 0.451, 0.524, 0.597, 0.669, 0.743, 0.817, 0.893, 0.973, 1.050, 1.126])
        currents = np.hstack( (-_currents, _currents) )
        torques  = np.hstack( (-_torques, _torques) )
        self.current2torque = interp1d(currents, torques, 'cubic')
        self.torque2current = interp1d(torques, currents, 'cubic')
        # 打开电机
        self.open()
        # 滤波参数
        self.speed_filter = deque(maxlen=5)
        self.torque_filter = deque(maxlen=5)
        # self.rate = Node.create_rate(60)
        # 期望
        self.expect_speed = 0
        self.need_set_speed = False

    def _open(self):
        error = True
        data2send = bytearray(5)
        data2send[0] = 0x3E
        data2send[1] = 0x88
        data2send[2] = self.id
        data2send[3] = 0x00
        data2send[4] = (data2send[0] + data2send[1] + data2send[2] + data2send[3]) % 256
        self.ser.write(data2send)
        # 数据接收
        time.sleep(0.1)
        data_receive = self.ser.read_all()
        try:
            if data_receive[4] == data2send[4]:
                error = False
            else:
                error = True
        except:
            error = True
        return error

    def open(self):
        error = self._open()
        while error:
            try:
                logger.error("Open moter " + str(self.id) + " failed !") #change
                # rospy.logerr("Open moter " + str(self.id) + " failed !")
                error = self._open()
                time.sleep(1)
            except:
                break

        logger.info("Open moter " + str(self.id) + " successed !")       #change
        # rospy.loginfo("Open moter " + str(self.id) + " successed !")

    def _read_speed_and_torque(self):
        error = False
        # 构造待发送数据
        data2send = bytearray(5)
        data2send[0] = 0x3E
        data2send[1] = 0x9C
        data2send[2] = self.id
        data2send[3] = 0x00
        data2send[4] = (data2send[0] + data2send[1] + data2send[2] + data2send[3]) % 256
        # 数据发送
        self.ser.write(data2send)
        # 数据接收
        time.sleep(0.005)
        data_receive = self.ser.read_all()
        # 数据校验
        try:
            # TODO check the condition
            if not data_receive[0]==data2send[0] and data_receive[1]==data2send[1] and data_receive[2]==data2send[2] and data_receive[3]==data2send[3]:
                error = True
                return(0, 0, error)
            if not (data_receive[5]+data_receive[6]+data_receive[7]+data_receive[8]+data_receive[9]+data_receive[10]+data_receive[11])%256 == data_receive[12]:
                error = True
                return(0, 0, error)
        except:
            error = True
            return(0, 0, error)

        # 数据解析
        current_bytes = bytearray([data_receive[6], data_receive[7]])
        current = struct.unpack('<h', current_bytes)[0]
        torque = float(self.current2torque(current))
        speed_bytes = bytearray([data_receive[8], data_receive[9]])
        speed = struct.unpack('<h', speed_bytes)[0]
        # 函数返回
        return(torque, speed, error)

    def read_speed_and_torque(self):
        (torque, speed, error) = self._read_speed_and_torque()
        while error:
            try:
                logger.error("Read moter " + str(self.id) + " failed !") #change
                # rospy.logerr("Read moter " + str(self.id) + " failed !")
                (torque, speed, error) = self._read_speed_and_torque()
            except:
                pass

        self.speed_filter.append(speed)
        self.torque_filter.append(torque)
        global motor_filter_states
        motor_filter_states[self.id-1] = self.cal_state()

    def _set_speed(self, expect_speed:float):
        error = False
        # 将实际速度转换为待发送的格式
        int_speed = int(expect_speed * 100)
        bytes_speed  = struct.pack('<i', int_speed)
        # 构造待发送的数据
        data2send = bytearray(10)
        data2send[0] = 0x3E
        data2send[1] = 0xA2
        data2send[2] = self.id
        data2send[3] = 0x04
        data2send[4] = (data2send[0] + data2send[1] + data2send[2] + data2send[3]) % 256
        data2send[5] =  bytes_speed[0]
        data2send[6] =  bytes_speed[1]
        data2send[7] =  bytes_speed[2]
        data2send[8] =  bytes_speed[3]
        data2send[9] = (data2send[5] + data2send[6] + data2send[7] + data2send[8]) % 256
        # 数据发送
        self.ser.write(data2send)
        # 数据接收
        time.sleep(0.005)
        data_receive = self.ser.read_all()
        # 数据校验
        try:
            if not data_receive[0]==data2send[0] and data_receive[1]==data2send[1] and data_receive[2]==data2send[2] and data_receive[3]==data2send[3]:
                error = True
                return(0, 0, error)
            if not (data_receive[5]+data_receive[6]+data_receive[7]+data_receive[8]+data_receive[9]+data_receive[10]+data_receive[11])%256 == data_receive[12]:
                error = True
                return(0, 0, error)
        except:
            error = True
            return(0, 0, error)
        # 数据解析
        current_bytes = bytearray([data_receive[6], data_receive[7]])
        current = struct.unpack('<h', current_bytes)[0]
        torque = float(self.current2torque(current))
        speed_bytes = bytearray([data_receive[8], data_receive[9]])
        speed = struct.unpack('<h', speed_bytes)[0]
        # 函数返回
        return(torque, speed, error)

    def set_speed(self):
        (torque, speed, error) = self._set_speed(self.expect_speed)
        while error:
            logger.info("Set moter " + str(self.id), " speed failed !")
            (torque, speed, error) = self._set_speed(self.expect_speed)
            self.speed_filter.append(speed)
            self.torque_filter.append(torque)
        self.need_set_speed = False

    def asyn_set_speed(self, expect_speed):
        self.expect_speed = expect_speed
        self.need_set_speed = True

    def cal_state(self):
        speed_array = np.array(self.speed_filter)
        speed = np.mean(speed_array[np.logical_and(speed_array != np.max(speed_array), speed_array != np.min(speed_array))])
        if np.isnan(speed):
            speed = np.mean(speed_array)
        # speed = np.mean(speed_array)
        torque_array = np.array(self.torque_filter)
        torque = np.mean(torque_array[np.logical_and(torque_array != np.max(torque_array), torque_array != np.min(torque_array))])
        if np.isnan(torque):
            torque = np.mean(torque_array)
        # print("speed: ", speed, "  torque: ", torque)
        return(speed, torque)

    def run(self):
        while self.running:
            if self.need_set_speed:
                self.set_speed()
            else:
                self.read_speed_and_torque()
            # self.rate.sleep()
            time.sleep(0.02)

    def stop(self):
        self._set_speed(0)
        self._set_speed(0)
        self._set_speed(0)
        logger.info("Motor" + str(self.id) + " stop!")
        # rospy.loginfo("Motor" + str(self.id) + " stop!")

    def terminate(self):
        self.running = False
        self.stop()
        logger.info("Motor" + str(self.id) + " terminate!")


class MotorControlNode(Node, threading.Thread):
    def __init__(self, motor1, motor2, motor3):
        # 初始化 ROS Node 和多线程
        Node.__init__(self, "motor_control")
        threading.Thread.__init__(self)
        self.get_logger().info("MotorControl_node online")
        self.__create_ros_communication()
        # self.rate = self.create_rate(50)
        # 传入电机控制类
        self.motor1, self.motor2, self.motor3 = motor1, motor2, motor3



    def __create_ros_communication(self):
        self.publisher_motors = self.create_publisher   (JointState, 'motor/states', qos_profile_system_default)
        self.lister_motors    = self.create_subscription(JointState, 'motor/cmds', self.__ros_callback, qos_profile_system_default)
        logger.info("Motors are running successfully !")
        self.running = True


    def __ros_callback(self, ros_data:JointState):
        if self.running:
            self.motor1.asyn_set_speed(float(np.rad2deg(-ros_data.velocity[0])))
            self.motor2.asyn_set_speed(float(np.rad2deg(-ros_data.velocity[1])))
            self.motor3.asyn_set_speed(float(np.rad2deg(-ros_data.velocity[2])))


    def run(self):
        time.sleep(1)
        while self.running:
            motor_states = JointState()
            global motor_filter_states
            speed1, torque1 = motor_filter_states[0]
            speed2, torque2 = motor_filter_states[1]
            speed3, torque3 = motor_filter_states[2]
            motor_states.velocity = [float(np.deg2rad(-speed1)), float(np.deg2rad(-speed2)), float(np.deg2rad(-speed3))]
            motor_states.effort   = [float(-torque1), float(-torque2), float(-torque3)]
            self.publisher_motors.publish(motor_states)
            time.sleep(0.02)
            # self.rate.sleep()


    def terminate(self):
        self.running = False
        self.motor1.terminate()
        self.motor2.terminate()
        self.motor3.terminate()
        time.sleep(0.1)
        # sys.exit(0)


def main():
    # 启动串口
    baudrate = 2000000
    port1 = "/dev/motor1"
    port2 = "/dev/motor2"
    port3 = "/dev/motor3"
    ser1 = serial.Serial(port1, baudrate)
    ser2 = serial.Serial(port2, baudrate)
    ser3 = serial.Serial(port3, baudrate)
    logger.info("Motor starting... port:"+ port1 + "," + port2 + "," + port3 +" , baudrate:"+str(baudrate))
    # 初始化电机
    motor1 = Motor(ser1, 1)
    motor2 = Motor(ser2, 2)
    motor3 = Motor(ser3, 3)
    motor3.start()
    motor1.start()
    motor2.start()
    # 启动ROS通讯
    moter_node = MotorControlNode(motor1, motor2, motor3)
    try:
        moter_node.start()
        rclpy.spin(moter_node)
    except KeyboardInterrupt:
        pass
    finally:
        moter_node.terminate()
        moter_node.join()
        if rclpy.ok():
            rclpy.shutdown()


