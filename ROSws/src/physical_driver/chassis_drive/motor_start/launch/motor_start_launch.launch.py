from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # 配置文件的路径声明
    # serial_driver_config = LaunchConfiguration('serial_driver_config')
    # ekf_config = LaunchConfiguration('ekf_config')

    return LaunchDescription([
        Node(
            package='motor_control',
            executable='motor_control_node',
            name='motor_control_n',
            output='screen',
        ),
        Node(
            package='motor_twist',
            executable='motor_twist',
            name='motor_twist',
            output='screen',
        ),
    ])
