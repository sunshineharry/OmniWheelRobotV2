import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TransformStamped
from tf2_ros.static_transform_broadcaster import StaticTransformBroadcaster
from tf2_ros.transform_broadcaster import TransformBroadcaster
import tf2_ros
from numpy import deg2rad
from tf_transformations import quaternion_from_euler, euler_from_quaternion



class RTK2Baselink(Node):

    def __init__(self):
        super().__init__('rtkantenna_to_baselink_node')
        self.broadcaster = StaticTransformBroadcaster(self)
        self.broadcast_transform()
        self.timer = self.create_timer(1, self.broadcast_transform)

    def broadcast_transform(self):
        static_transform_stamped = TransformStamped()
        static_transform_stamped.header.stamp = self.get_clock().now().to_msg()
        static_transform_stamped.header.frame_id = 'rtkantenna'
        static_transform_stamped.child_frame_id = 'base_link'

        # 位置
        static_transform_stamped.transform.translation.x = 0.0
        static_transform_stamped.transform.translation.y = 0.1354                #
        static_transform_stamped.transform.translation.z = 0.0

        # 旋转
        q = quaternion_from_euler(deg2rad(0),deg2rad(0),deg2rad(180))
        static_transform_stamped.transform.rotation.x = q[0]
        static_transform_stamped.transform.rotation.y = q[1]
        static_transform_stamped.transform.rotation.z = q[2]
        static_transform_stamped.transform.rotation.w = q[3]
        self.broadcaster.sendTransform(static_transform_stamped)

def main(args=None):
    rclpy.init(args=args)
    node = RTK2Baselink()
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
