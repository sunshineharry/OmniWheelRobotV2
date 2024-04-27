from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='realsense2_camera',
            namespace='realsense',
            executable='realsense2_camera_node',
            name='realsense2_camera',
            parameters=[{'device_type': 'd435i'}, {'enable_gyro': True}, {'enable_accel': True}, {'unite_imu_method': 'linear_interpolation'}],
            output='screen'
        )
    ])
