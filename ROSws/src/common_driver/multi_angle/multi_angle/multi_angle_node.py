import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from std_msgs.msg import Float64
from tf_transformations import euler_from_quaternion
from rclpy.qos import qos_profile_system_default
from math import pi

class MultiAngle(Node):
    def __init__(self):
        super().__init__('multi_angle')
        # 订阅filtered/odom话题
        self.single_angle_listener = self.create_subscription(Odometry, 'filtered/odom', self.multi_angle, qos_profile_system_default)
        self.multi_angle_publisher = self.create_publisher(Float64, 'filtered/yaw', qos_profile_system_default)
        self.start_angle = 0
        self.last_angle = -999
        self.cycle = 0

    def multi_angle(self, msg: Odometry):
        orientation = msg.pose.pose.orientation
        (_, _, y) = euler_from_quaternion([orientation.x, orientation.y, orientation.z, orientation.w])
        # 第一次运行
        if self.last_angle == -999:
            # self.start_angle = y
            self.last_angle = y
        # 正常的循环
        if (y - self.last_angle) < (-1.5 * pi):
            self.cycle += 1
        if (y - self.last_angle) > (1.5 * pi):
            self.cycle -= 1
        self.last_angle = y
        theta = self.cycle * 2 * pi + y - self.start_angle
        self.multi_angle_publisher.publish(Float64(data=theta))

def main(args=None):
    print("--------------")
    rclpy.init(args=args)
    multi_angle = MultiAngle()
    rclpy.spin(multi_angle)
    multi_angle.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
