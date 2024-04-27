from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # 配置文件的路径声明
    ekf_config = LaunchConfiguration('ekf_config')

    return LaunchDescription([
        DeclareLaunchArgument(
            'ekf_config',  # 唯一的参数名
            default_value=[FindPackageShare('sensors_fusion_start'), '/config/ekf_filter_node_parms.yaml'],
            description='Path to the EKF config file.',
        ),
        Node(
            package='robot_localization',
            executable='ekf_node',
            name='ekf_filter_node',
            output='screen',
            parameters=[ekf_config],
            # arguments=['--ros-args', '--log-level', 'DEBUG'],
            remappings=[('/odometry/filtered', 'filtered/odom')],
        ),
        Node(
            package='multi_angle',
            executable='multi_angle_node',
            name='multi_angle_node',
            output='screen',
        ),
    ])
