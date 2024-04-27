import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TransformStamped,PointStamped
from tf2_ros.static_transform_broadcaster import StaticTransformBroadcaster
from tf_transformations import quaternion_from_euler
import tf2_ros
from nav_msgs.msg import Odometry
from numpy import deg2rad

class UTM2Ground(Node):

    def __init__(self):
        super().__init__('world_to_map_node')
        self.broadcaster = StaticTransformBroadcaster(self)
        self.static_transform_stamped = TransformStamped()
        self.broadcaster2 = StaticTransformBroadcaster(self)
        self.static_transform_stamped2 = TransformStamped()
        self.world_to_map()
        self.timer = self.create_timer(1, self.world_to_map)
        # self.rtk_odom_sub = self.create_subscription(Odometry,'/rtk_odom',self.world_to_map,10)

    def world_to_map(self):
        self.static_transform_stamped.header.stamp = self.get_clock().now().to_msg()
        self.static_transform_stamped.header.frame_id = 'world'
        self.static_transform_stamped.child_frame_id = 'map'

        # 假设的ground坐标参考点, 测试获得
        self.static_transform_stamped.transform.translation.x = 440649.38+0.17  # 示例坐标
        self.static_transform_stamped.transform.translation.y = 4423950.45+0.02  # 示例坐标
        self.static_transform_stamped.transform.translation.z = 50.35  # 示例坐标

        # 无旋转
        q = quaternion_from_euler(deg2rad(0),deg2rad(0),deg2rad(260+17.5-90))
        self.static_transform_stamped.transform.rotation.x = q[0]
        self.static_transform_stamped.transform.rotation.y = q[1]
        self.static_transform_stamped.transform.rotation.z = q[2]
        self.static_transform_stamped.transform.rotation.w = q[3]

        self.broadcaster.sendTransform(self.static_transform_stamped)


        # self.static_transform_stamped2.header.stamp = self.get_clock().now().to_msg()
        # self.static_transform_stamped2.header.frame_id = 'world'
        # self.static_transform_stamped2.child_frame_id = 'odom'

        # # 假设的ground坐标参考点, 测试获得
        # self.static_transform_stamped2.transform.translation.x = 0.0  # 示例坐标
        # self.static_transform_stamped2.transform.translation.y = 0.0  # 示例坐标
        # self.static_transform_stamped2.transform.translation.z = 0.0 # 示例坐标

        # # 无旋转
        # q = quaternion_from_euler(deg2rad(0),deg2rad(0),deg2rad(0))
        # self.static_transform_stamped2.transform.rotation.x = q[0]
        # self.static_transform_stamped2.transform.rotation.y = q[1]
        # self.static_transform_stamped2.transform.rotation.z = q[2]
        # self.static_transform_stamped2.transform.rotation.w = q[3]


        # self.broadcaster2.sendTransform(self.static_transform_stamped2)


def main(args=None):
    rclpy.init(args=args)
    node = UTM2Ground()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()

if __name__ == '__main__':
    main()
