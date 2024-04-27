from coppeliasim_zmqremoteapi_client import *
import threading
from rclpy.executors import MultiThreadedExecutor
import rclpy
from rclpy.node import Node
from rclpy.qos  import qos_profile_system_default
import tf2_ros
from sensor_msgs.msg   import JointState
from nav_msgs.msg      import Odometry
from geometry_msgs.msg import Quaternion, TransformStamped

client = RemoteAPIClient(host='192.168.1.24')
sim    = client.require('sim')
lock   = threading.Lock()

def start_sim():
    sim.startSimulation()

def stop_sim():
    sim.stopSimulation()

class VrepOmniRobot(object):
    def __init__(self, index) -> None:
        with lock:
            self.robot = sim.getObject(f"/robot{index}")
            self.joint1 = sim.getObject(f"/robot{index}/joint1")
            self.joint2 = sim.getObject(f"/robot{index}/joint2")
            self.joint3 = sim.getObject(f"/robot{index}/joint3")
            self.point_clouds = sim.getObject(f"/robot{index}/VPL16_To1/ptCloud")

    def set_joint(self, v1, v2, v3):
        with lock:
            sim.setJointTargetVelocity(self.joint1, v1)
            sim.setJointTargetVelocity(self.joint2, v2)
            sim.setJointTargetVelocity(self.joint3, v3)

    def get_pose(self):
        with lock:
            pose = sim.getObjectPose(self.robot)
            position = pose[0:3]
            quaternion = pose[3:]
        return (position, quaternion)

    def get_speed(self):
        with lock:
            linear_velocity, angular_velocity = sim.getObjectVelocity(self.robot)
        return(linear_velocity, angular_velocity)

    def get_laser(self):
        with lock:
            point_cloud = sim.getPointCloudPoints(self.point_clouds)
        return point_cloud


class VrepOmniRosRobot(Node):
    def __init__(self, index):
        self.index          = index
        Node.__init__(self, f"robot{self.index}_vrep_sim")
        self.get_logger().info(f"robot{self.index}_vrep_sin node online")
        self.vrobot         = VrepOmniRobot(index)
        self.lister_motors  = self.create_subscription(JointState, f"robot{self.index}/motor/cmds", self.__set_vrobot_joints, qos_profile_system_default)
        self.timer          = self.create_timer((1/60), self.__get_odom_and_tf)
        self.tfbroadcaster  = tf2_ros.TransformBroadcaster(self)
        self.odom_puber     = self.create_publisher(Odometry, f"robot{self.index}/filter/odom", qos_profile_system_default)


    def __set_vrobot_joints(self, joint_velocity:JointState):
        self.vrobot.set_joint(-joint_velocity.velocity[0], -joint_velocity.velocity[1], -joint_velocity.velocity[2])

    def __get_odom_and_tf(self):
        # self.get_logger().info("----------------")
        msg = Odometry()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = "map"
        msg.child_frame_id = f"robot{self.index}_base_link_filter"

        position, orientation = self.vrobot.get_pose()
        msg.pose.pose.position.x = position[0]
        msg.pose.pose.position.y = position[1]
        msg.pose.pose.position.z = position[2]
        msg.pose.pose.orientation = Quaternion(x=orientation[0], y=orientation[1], z=orientation[2], w=orientation[3])

        linear_velocity, angular_velocity = self.vrobot.get_speed()
        msg.twist.twist.linear.x  = linear_velocity[0]
        msg.twist.twist.linear.y  = linear_velocity[1]
        msg.twist.twist.linear.z  = linear_velocity[2]
        msg.twist.twist.angular.x = angular_velocity[0]
        msg.twist.twist.angular.y = angular_velocity[1]
        msg.twist.twist.angular.z = angular_velocity[2]

        self.odom_puber.publish(msg)

        tf_msg = TransformStamped()
        tf_msg.header.stamp = msg.header.stamp
        tf_msg.header.frame_id = "map"
        tf_msg.child_frame_id = f"robot{self.index}_base_link_filter"
        tf_msg.transform.translation.x = position[0]
        tf_msg.transform.translation.y = position[1]
        tf_msg.transform.translation.z = position[2]
        tf_msg.transform.rotation = msg.pose.pose.orientation
        self.tfbroadcaster.sendTransform(tf_msg)


def main():
    rclpy.init()
    start_sim()
    robot1  = VrepOmniRosRobot(1)
    robot2  = VrepOmniRosRobot(2)
    # 使用多线程执行器
    executor = MultiThreadedExecutor(num_threads=2)
    executor.add_node(robot1)
    executor.add_node(robot2)

    try:
        # 使用executor代替单独的线程来运行两个节点
        executor.spin()
    except KeyboardInterrupt:
        stop_sim()
    finally:
        if rclpy.ok():
            robot1.destroy_node()
            robot2.destroy_node()
            executor.shutdown()
            rclpy.shutdown()
        stop_sim()

if __name__ == '__main__':
    main()
