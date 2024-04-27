#!/usr/bin/env python

import rclpy
from rclpy import Node
from sensor_msgs.msg import JointState
from geometry_msgs.msg import Twist
import time
import numpy as np

# class MotorEncoder(object):
#     def __init__(self) -> None:
#         self.motors  = rospy.Publisher('motor/cmds', JointState, queue_size=10)
#         self.cmd_vel = rospy.Subscriber('control/cmd_vel', Twist, self.ros_callback)

#         self.moters = rospy.Subscriber('motor/cmds', JointState, self.encoder)
#         self.vel    = rospy.Publisher('motor/cmds', JointState, queue_size=10)
#         self.r = rospy.get_param("/wheel_radius", 0.35)
#         self.R = rospy.get_param("/wheel_radius", 0.075)

class MotorEncoder(Node):
    def __init__(self) -> None:
        self.motors  = self.create_publisher(JointState,'motor/cmds',qos_profile=10)
        self.cmd_vel = self.create_subscription(Twist,'control/cmd_vel',self.ros_callback)

        self.moters = self.create_subscription(JointState,'motor/cmds',self.encoder)
        self.vel    = self.create_publisher(JointState,'motor/cmds',qos_profile=10)
        self.r      = self.get_parameter("/wheel_radius",0.35).value
        self.R      = self.get_parameter("/wheel_radius",0.075).value