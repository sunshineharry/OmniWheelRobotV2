from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare
import os

def generate_launch_description():
    # 查找包的共享目录
    rtk_start_dir = FindPackageShare('rtk_start').find('rtk_start')
    sensors_fusion_dir = FindPackageShare('sensors_fusion_start').find('sensors_fusion_start')
    # wit_dir = FindPackageShare('witmotion_ros').find('witmotion_ros')

    # 构建launch文件的路径
    rtk_start_launch_path = os.path.join(rtk_start_dir, 'launch', 'rtk_start_launch.launch.py')
    sensors_fusion_start_launch_path = os.path.join(sensors_fusion_dir, 'launch', 'sensors_fusion_start.launch.py')
    # wit_start_launch_path = os.path.join(wit_dir, 'launch', 'wt901.launch.py')

    # 包含其他launch文件
    rtk_start_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(rtk_start_launch_path)
    )
    sensors_fusion_start_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(sensors_fusion_start_launch_path)
    )

    # wit_start_launch = IncludeLaunchDescription(
    #     PythonLaunchDescriptionSource(wit_start_launch_path)
    # )

    # 定义节点
    motor_control_node = Node(
        package='motor_control',
        executable='motor_control_node',
        name='motor_control_node'
    )
    kinematics_model2_node = Node(
        package='kinematics_model',
        executable='kinematics_model2_node',
        name='kinematics_model2_node'
    )
    wht101 = Node(
        package='wht101',
        executable='wht101',
        name='wht101'
    )

    # 创建并返回LaunchDescription
    return LaunchDescription([
        rtk_start_launch,
        sensors_fusion_start_launch,
        motor_control_node,
        kinematics_model2_node,
        wht101
    ])

