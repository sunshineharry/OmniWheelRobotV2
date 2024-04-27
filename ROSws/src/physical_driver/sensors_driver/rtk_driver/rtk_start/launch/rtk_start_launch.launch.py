from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # 配置文件的路径声明
    serial_driver_config = LaunchConfiguration('serial_driver_config')
    # ekf_config = LaunchConfiguration('ekf_config')

    return LaunchDescription([
        DeclareLaunchArgument(
            'serial_driver_config',  # 唯一的参数名
            default_value=[FindPackageShare('rtk_start'), '/config/um982_serial_driver_params.yaml'],
            description='Path to the serial driver config file.',
        ),
        # DeclareLaunchArgument(
        #     'ekf_config',  # 唯一的参数名
        #     default_value=[FindPackageShare('rtk_start'), '/config/ekf_filter_node_parms.yaml'],
        #     description='Path to the EKF config file.',
        # ),
        Node(
            package='um982_tf',
            executable='world_to_map_node',
            name='world_to_map_node',
            output='screen',
        ),
        # Node(
        #     package='um982_tf',
        #     executable='rtkantenna_to_baselink_node',
        #     name='rtkantenna_to_baselink_node',
        #     output='screen',
        # ),
        Node(
            package='um982_driver',
            executable='um982_serial_driver_node',
            name='um982_serial_driver_node',
            output='screen',
            parameters=[serial_driver_config]
        ),
        # Node(
        #     package='robot_localization',
        #     executable='ekf_node',
        #     name='ekf_filter_node',
        #     output='screen',
        #     parameters=[ekf_config],
        #     # arguments=['--ros-args', '--log-level', 'DEBUG'],
        #     remappings=[('/odometry/filtered', 'filtered/odom')],
        # ),
    ])
