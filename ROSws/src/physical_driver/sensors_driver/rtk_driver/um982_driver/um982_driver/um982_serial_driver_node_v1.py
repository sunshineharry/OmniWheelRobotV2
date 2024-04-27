import threading
import time
import serial


import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Quaternion, PoseWithCovarianceStamped, TwistWithCovarianceStamped, TransformStamped, Vector3Stamped, Pose, Twist
from tf_transformations import quaternion_from_euler, euler_from_quaternion, compose_matrix, decompose_matrix, quaternion_from_matrix, quaternion_matrix
from rclpy.qos import qos_profile_system_default
import tf2_ros
from tf2_ros import Buffer, TransformListener
from rclpy.duration import Duration
from um982.assic_driver import UM982Driver
import numpy as np
from typing import Iterable, Optional, Tuple

def transform_pose_with_covariance_stamped(pose_msg: PoseWithCovarianceStamped, transform):
    # Compose the transformation matrix from the translation and rotation
    trans_matrix = compose_matrix(
        translate = (
            transform.transform.translation.x,
            transform.transform.translation.y,
            transform.transform.translation.z
        ),
        angles = euler_from_quaternion([
            transform.transform.rotation.x,
            transform.transform.rotation.y,
            transform.transform.rotation.z,
            transform.transform.rotation.w
        ])
    )

    # Compose the pose matrix from the pose message
    pos_matrix = compose_matrix(
        translate = (
            pose_msg.pose.pose.position.x,
            pose_msg.pose.pose.position.y,
            pose_msg.pose.pose.position.z
        ),
        angles = euler_from_quaternion([
            pose_msg.pose.pose.orientation.x,
            pose_msg.pose.pose.orientation.y,
            pose_msg.pose.pose.orientation.z,
            pose_msg.pose.pose.orientation.w
        ])
    )

    # Multiply the pose matrix by the transformation matrix
    new_pos_matrix = np.dot(pos_matrix, trans_matrix)

    # Decompose the new pose matrix to get new translation and rotation
    _, _, _, new_translate, _ = decompose_matrix(new_pos_matrix)
    new_orientation = quaternion_from_matrix(new_pos_matrix)

    # Convert quaternion to matrix to compute the Jacobian for orientation part
    orientation_matrix = quaternion_matrix([pose_msg.pose.pose.orientation.x, pose_msg.pose.pose.orientation.y,
                                            pose_msg.pose.pose.orientation.z, pose_msg.pose.pose.orientation.w])

    # Assuming a simple Jacobian that might only consider rotational effects, you might need a more complex one depending on your system
    J = np.zeros((6, 6))
    J[:3, :3] = trans_matrix[:3, :3]  # Position part
    J[3:, 3:] = orientation_matrix[:3, :3]  # Orientation part

    # Original covariance matrix reshaped into 6x6
    orig_cov = np.array(pose_msg.pose.covariance).reshape(6, 6)
    new_cov = J @ orig_cov @ J.T

    # Create a new PoseWithCovarianceStamped message
    new_pose_msg = PoseWithCovarianceStamped()
    new_pose_msg.header.stamp = pose_msg.header.stamp
    new_pose_msg.header.frame_id = pose_msg.header.frame_id
    new_pose_msg.pose.pose.position.x = new_translate[0]
    new_pose_msg.pose.pose.position.y = new_translate[1]
    new_pose_msg.pose.pose.position.z = new_translate[2]
    new_pose_msg.pose.pose.orientation.x = new_orientation[0]
    new_pose_msg.pose.pose.orientation.y = new_orientation[1]
    new_pose_msg.pose.pose.orientation.z = new_orientation[2]
    new_pose_msg.pose.pose.orientation.w = new_orientation[3]
    new_pose_msg.pose.covariance = tuple(new_cov.flatten())

    return new_pose_msg

def transform_twist_with_covariance_stamped(twist_msg: TwistWithCovarianceStamped, transform):
    # Extract the rotation part from the transform
    rotation_matrix = quaternion_matrix([
        transform.transform.rotation.x,
        transform.transform.rotation.y,
        transform.transform.rotation.z,
        transform.transform.rotation.w
    ])[:3, :3]

    # Extract linear and angular velocities
    linear_vel = np.array([
        twist_msg.twist.twist.linear.x,
        twist_msg.twist.twist.linear.y,
        twist_msg.twist.twist.linear.z
    ])
    angular_vel = np.array([
        twist_msg.twist.twist.angular.x,
        twist_msg.twist.twist.angular.y,
        twist_msg.twist.twist.angular.z
    ])

    # Apply rotation to linear and angular velocities
    transformed_linear_vel = rotation_matrix @ linear_vel
    transformed_angular_vel = rotation_matrix @ angular_vel

    # Assuming the Jacobian for the twist is the rotation matrix for both linear and angular parts
    J = np.block([
        [rotation_matrix, np.zeros((3, 3))],
        [np.zeros((3, 3)), rotation_matrix]
    ])

    # Original covariance matrix reshaped into 6x6
    orig_cov = np.array(twist_msg.twist.covariance).reshape(6, 6)
    new_cov = J @ orig_cov @ J.T

    # Create a new TwistWithCovarianceStamped message
    new_twist_msg = TwistWithCovarianceStamped()
    new_twist_msg.header.stamp = twist_msg.header.stamp
    new_twist_msg.header.frame_id = twist_msg.header.frame_id
    new_twist_msg.twist.twist.linear.x = transformed_linear_vel[0]
    new_twist_msg.twist.twist.linear.y = transformed_linear_vel[1]
    new_twist_msg.twist.twist.linear.z = transformed_linear_vel[2]
    new_twist_msg.twist.twist.angular.x = transformed_angular_vel[0]
    new_twist_msg.twist.twist.angular.y = transformed_angular_vel[1]
    new_twist_msg.twist.twist.angular.z = transformed_angular_vel[2]
    new_twist_msg.twist.covariance = tuple(new_cov.flatten())

    return new_twist_msg

class UM982SerialDriverNode(Node):
    def __init__(self, ser:serial.Serial) -> None:
        Node.__init__(self, 'um982_serial_driver_node')
        self.ser        = ser
        self.solver     = UM982Driver()
        self.isrunning  = True
        self.antenna_pose_pub    = self.create_publisher(PoseWithCovarianceStamped,  '/rtk/antenna/pose',   qos_profile_system_default)
        self.antenna_twist_pub   = self.create_publisher(TwistWithCovarianceStamped, '/rtk/antenna/twist',  qos_profile_system_default)
        # self.baselink_pose_pub   = self.create_publisher(PoseWithCovarianceStamped,  '/rtk/baselink/pose',  qos_profile_system_default)
        # self.baselink_twist_pub  = self.create_publisher(TwistWithCovarianceStamped, '/rtk/baselink/twist', qos_profile_system_default)
        self.broadcaster = tf2_ros.TransformBroadcaster(self)
        # self.tf_buffer = Buffer()
        # self.tf_listener = TransformListener(self.tf_buffer, self)
        self.timer = self.create_timer(0.04, self.run)


    def get_nmea_msg(self) -> bool:
        all_msg = str(self.ser.read_all(),'utf-8')
        if ( len(all_msg) == 0 ):
            return False
        else:
            self.solver.decode(all_msg)
            return True

    def nmea_msg_to_pose_and_twist(self) -> None:
        antenna_pose_msg  = PoseWithCovarianceStamped()
        antenna_twist_msg = TwistWithCovarianceStamped()
        antenna_pose_msg.header.stamp = self.get_clock().now().to_msg()
        antenna_pose_msg.header.frame_id = 'world'
        antenna_twist_msg.header.stamp = self.get_clock().now().to_msg()
        antenna_twist_msg.header.frame_id = 'world'

        ## 设置位置
        antenna_pose_msg.pose.pose.position.x = self.solver.utm_x
        antenna_pose_msg.pose.pose.position.y = self.solver.utm_y
        antenna_pose_msg.pose.pose.position.z = self.solver.bestpos_hgt

        # 使用roll, pitch, heading设置方向
        q = quaternion_from_euler(0, 0, np.radians(360-self.solver.heading+180))
        antenna_pose_msg.pose.pose.orientation = Quaternion(x=q[0], y=q[1], z=q[2], w=q[3])
        # self.get_logger().info("x      : " + str(self.solver.utm_x))
        # self.get_logger().info("y      : " + str(self.solver.utm_y))
        # self.get_logger().info("z      : " + str(self.solver.bestpos_hgt))
        # self.get_logger().info("heading: " + str(360-self.solver.heading))

        # 填充位置的方差
        antenna_pose_msg.pose.covariance[0]  = 5*self.solver.bestpos_latstd ** 2    # position.x的方差
        antenna_pose_msg.pose.covariance[7]  = 5*self.solver.bestpos_lonstd ** 2    # position.y的方差
        antenna_pose_msg.pose.covariance[14] = 5*self.solver.bestpos_hgtstd ** 2    # position.z的方差
        small_var = 1e-4
        antenna_pose_msg.pose.covariance[21] = 5*small_var  # roll的方差
        antenna_pose_msg.pose.covariance[28] = 5*small_var  # pitch的方差
        antenna_pose_msg.pose.covariance[35] = 0.2  # yaw的方差

        ## 设置速度
        antenna_twist_msg.twist.twist.linear.x = self.solver.vel_north
        antenna_twist_msg.twist.twist.linear.y = self.solver.vel_east
        antenna_twist_msg.twist.twist.linear.z = self.solver.vel_up

        # 填充速度标准差
        antenna_twist_msg.twist.covariance[0]  = 5*self.solver.vel_east_std  ** 2   # linear.x 的方差
        antenna_twist_msg.twist.covariance[1]  = 5*self.solver.vel_hor_cov ** 2     # linear.x和linear.y的协方差
        antenna_twist_msg.twist.covariance[6]  = 5*self.solver.vel_hor_cov ** 2     # linear.y和linear.x的协方差
        antenna_twist_msg.twist.covariance[7]  = 5*self.solver.vel_north_std ** 2   # linear.y 的方差
        antenna_twist_msg.twist.covariance[14] = 5*self.solver.vel_up_std ** 2      # linear.z 的方差

        self.antenna_pose_pub.publish(antenna_pose_msg)
        self.antenna_twist_pub.publish(antenna_twist_msg)


        # rtkantenna_to_baselink_transform = self.tf_buffer.lookup_transform('base_link', 'rtkantenna', rclpy.time.Time())
        # baselink_pose  = transform_pose_with_covariance_stamped(antenna_pose_msg, rtkantenna_to_baselink_transform)
        # baselink_twist = transform_twist_with_covariance_stamped(antenna_twist_msg, rtkantenna_to_baselink_transform)

        # self.baselink_pose_pub.publish(baselink_pose)
        # self.baselink_twist_pub.publish(baselink_twist)

    def rtkantenna_to_world_transform(self):
        t = TransformStamped()

        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = 'world'
        # t.child_frame_id = 'rtkantenna'
        t.child_frame_id = 'base_link'

        # 示例: 从某个数据源动态获取位置和旋转信息
        # 这里使用时间函数模拟位置变化
        t.transform.translation.x = self.solver.utm_x
        t.transform.translation.y = self.solver.utm_y
        t.transform.translation.z = self.solver.bestpos_hgt

        q = quaternion_from_euler(0, 0, np.radians(360-self.solver.heading+180))
        t.transform.rotation.x = q[0]
        t.transform.rotation.y = q[1]
        t.transform.rotation.z = q[2]
        t.transform.rotation.w = q[3]

        self.broadcaster.sendTransform(t)

    def run(self):
        if self.isrunning:
            if( self.get_nmea_msg() ):
                self.nmea_msg_to_pose_and_twist()
                self.rtkantenna_to_world_transform()

    def terminate(self):
        self.isrunning = False
        self.ser.close()



def main():
    rclpy.init()
    parm_getter = Node("parm_getter_for_um982_serial_driver")
    serial_port = parm_getter.declare_parameter('serial_port', '/dev/ttyACM0').get_parameter_value().string_value
    baud_rate   = parm_getter.declare_parameter('baud_rate', 921600).get_parameter_value().integer_value
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
