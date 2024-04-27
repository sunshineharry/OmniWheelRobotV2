import threading
import time
import serial


import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Quaternion, PoseWithCovarianceStamped, TwistWithCovarianceStamped, TransformStamped, Vector3Stamped, Pose, Twist, Vector3
from tf_transformations import quaternion_from_euler, euler_from_quaternion, compose_matrix, decompose_matrix, quaternion_from_matrix, quaternion_matrix
from rclpy.qos import qos_profile_system_default
import tf2_ros
from tf2_ros import Buffer, TransformListener
from rclpy.duration import Duration
from um982.assic_driver import UM982Driver
import numpy as np
from typing import Iterable, Optional, Tuple

class PT2D():
    def __init__(self) -> None:
        self.pose2D    = Vector3()
        self.pose2Dstd = Vector3()
        self.yaw       = 0
        self.yawstd    = 0
        self.initx     = 440649.38+0.17
        self.inity     = 4423950.45+0.02+0.04
        self.inityaw   = np.radians(260+18-90)

class UM982SerialDriverNode(Node):
    def __init__(self, ser:serial.Serial) -> None:
        Node.__init__(self, 'um982_serial_driver_node')
        self.ser        = ser
        self.solver     = UM982Driver()
        self.isrunning  = True
        self.antenna_pose_pub    = self.create_publisher(PoseWithCovarianceStamped,  '/rtk/antenna/pose',   qos_profile_system_default)
        # self.antenna_twist_pub   = self.create_publisher(TwistWithCovarianceStamped, '/rtk/antenna/twist',  qos_profile_system_default)
        self.broadcaster = tf2_ros.TransformBroadcaster(self)
        self.timer  = self.create_timer(0.04, self.run)
        self.utm_pt = PT2D()
        self.map_pt = PT2D()


    def get_nmea_msg(self) -> bool:
        all_msg = str(self.ser.read_all(),'utf-8')
        if ( len(all_msg) == 0 ):
            return False
        else:
            self.solver.decode(all_msg)
            return True

    def nmea_msg_read(self) -> None:
        self.utm_pt.pose2D.x    = self.solver.utm_x
        self.utm_pt.pose2D.y    = self.solver.utm_y
        self.utm_pt.pose2Dstd.x = 5 * self.solver.bestpos_lonstd ** 2
        self.utm_pt.pose2Dstd.y = 5 * self.solver.bestpos_latstd ** 2
        self.utm_pt.yaw         = np.radians(360-self.solver.heading)


    def utm2map(self) -> None:
        self.map_pt.pose2D.x      = ( (self.utm_pt.pose2D.x    - self.utm_pt.initx) * np.cos( -self.utm_pt.inityaw ) - (self.utm_pt.pose2D.y    - self.utm_pt.inity) * np.sin( -self.utm_pt.inityaw ) ) * 0.98
        self.map_pt.pose2D.y      =   (self.utm_pt.pose2D.x    - self.utm_pt.initx) * np.sin( -self.utm_pt.inityaw ) + (self.utm_pt.pose2D.y    - self.utm_pt.inity) * np.cos( -self.utm_pt.inityaw )
        self.map_pt.pose2Dstd.x   = ( (self.utm_pt.pose2Dstd.x                    ) * np.cos( -self.utm_pt.inityaw ) - (self.utm_pt.pose2Dstd.y                    ) * np.sin( -self.utm_pt.inityaw ) ) * 0.98
        self.map_pt.pose2Dstd.y   =   (self.utm_pt.pose2Dstd.x                    ) * np.sin( -self.utm_pt.inityaw ) + (self.utm_pt.pose2Dstd.y                    ) * np.cos( -self.utm_pt.inityaw )
        self.map_pt.yaw           =   self.utm_pt.yaw
        self.map_pt.yawstd        =   np.radians(30)
        # self.get_logger().info("x: " + str(self.map_pt.pose2D.x))
        # self.get_logger().info("yaw: " + str(self.map_pt.yaw))


    def broadcost_pose_twist(self):
        antenna_pose_msg  = PoseWithCovarianceStamped()
        antenna_twist_msg = TwistWithCovarianceStamped()
        antenna_pose_msg.header.stamp = self.get_clock().now().to_msg()
        antenna_pose_msg.header.frame_id = 'map'
        antenna_twist_msg.header.stamp = self.get_clock().now().to_msg()
        antenna_twist_msg.header.frame_id = 'map'

        ## 设置位置
        antenna_pose_msg.pose.pose.position.x = self.map_pt.pose2D.x
        antenna_pose_msg.pose.pose.position.y = self.map_pt.pose2D.y
        antenna_pose_msg.pose.pose.position.z = 0.0

        # 使用roll, pitch, heading设置方向
        q = quaternion_from_euler(0, 0, self.map_pt.yaw)
        antenna_pose_msg.pose.pose.orientation = Quaternion(x=q[0], y=q[1], z=q[2], w=q[3])

        # 填充位置的方差
        antenna_pose_msg.pose.covariance[0]  = self.map_pt.pose2Dstd.x    # position.x的方差
        antenna_pose_msg.pose.covariance[7]  = self.map_pt.pose2Dstd.y    # position.y的方差
        antenna_pose_msg.pose.covariance[35] = self.map_pt.yawstd         # yaw的方差

        self.antenna_pose_pub.publish(antenna_pose_msg)



    def broadcost_tf(self):
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = 'map'
        t.child_frame_id = 'base_link'

        t.transform.translation.x = self.map_pt.pose2D.x
        t.transform.translation.y = self.map_pt.pose2D.y

        q = quaternion_from_euler(0, 0, self.map_pt.yaw)
        t.transform.rotation.x = q[0]
        t.transform.rotation.y = q[1]
        t.transform.rotation.z = q[2]
        t.transform.rotation.w = q[3]

        self.broadcaster.sendTransform(t)


    def run(self):
        if self.isrunning:
            if( self.get_nmea_msg() ):
                self.nmea_msg_read()
                self.utm2map()
                self.broadcost_pose_twist()
                self.broadcost_tf()

    def terminate(self):
        self.isrunning = False
        self.ser.close()



def main():
    rclpy.init()
    parm_getter = Node("parm_getter_for_um982_serial_driver")
    serial_port = parm_getter.declare_parameter('serial_port', '/dev/rtk').get_parameter_value().string_value
    baud_rate   = parm_getter.declare_parameter('baud_rate', 921600).get_parameter_value().integer_value
    parm_getter.get_logger().info("UM982 Starting... port: " + serial_port + ", baudrate: " + str(baud_rate))
    parm_getter.destroy_node()
    um982_serial_driver = UM982SerialDriverNode(serial.Serial(serial_port, baud_rate))
    try:
        rclpy.spin(um982_serial_driver)
    except KeyboardInterrupt:
        pass
    finally:
        um982_serial_driver.terminate()
        if rclpy.ok():
            rclpy.shutdown()
