#!/usr/bin/env python

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
from geometry_msgs.msg import Twist
from std_msgs.msg import Bool, Float64
import time
import numpy as np
from rclpy.qos import qos_profile_system_default

class KenematicsModel(Node):
    def __init__(self,name) -> None:
        super().__init__(name)
        self.motors  = self.create_publisher(JointState,'motor/cmds', qos_profile_system_default)
        self.cmd_vel = self.create_subscription(Twist,'control/cmd_vel', self.__ros_callback,qos_profile_system_default)
        self.is_run_pub = self.create_subscription(Bool,'control/is_run', self.__set_run_state, qos_profile_system_default)
        self.yaw_sub = self.create_subscription(Float64,'filtered/yaw', self.__set_yaw, qos_profile_system_default)
        self.yaw = 0
        self.is_run = True
        self.r = self.get_parameter_or("robot_radius", alternative_value=0.175)
        self.R = self.get_parameter_or("wheel_radius", alternative_value=0.0375)

    def __set_run_state(self, data:Bool):
        self.is_run = data.data
        if self.is_run == False:
            motor_cmds = JointState()
            motor_cmds.velocity = [0,0,0]
            self.motors.publish(motor_cmds)

    def __set_yaw(self, data:Float64):
        self.yaw = float(data.data)

    def run_model(self, vx, vy, theta):
        # _theta = -np.pi/3 - self.yaw
        _theta = -np.pi/3
        vx_new = np.cos(_theta)*vx - np.sin(_theta)*vy
        vy_new = np.sin(_theta)*vx + np.cos(_theta)*vy
        convert_matrix = np.array([
            [0,             1,     self.r],
            [-np.sqrt(3)/2, -0.5,  self.r],
            [+np.sqrt(3)/2, -0.5,  self.r]
        ])
        dphi = (1/self.R)*convert_matrix@np.array([[vx_new],[vy_new],[theta]])
        return dphi.reshape(-1).tolist()

    def __ros_callback(self, ros_data:Twist):
        vx    = ros_data.linear.x
        vy    = ros_data.linear.y
        theta = ros_data.angular.z
        dphi = self.run_model(vx, vy, theta)
        motor_cmds = JointState()
        motor_cmds.velocity = dphi
        if self.is_run == False:
            motor_cmds.velocity = [0,0,0]
        self.motors.publish(motor_cmds)

def main(args=None):
    rclpy.init(args=args)
    kenematics_model_1 = KenematicsModel("kenematics_model_1")
    rclpy.spin(kenematics_model_1)
