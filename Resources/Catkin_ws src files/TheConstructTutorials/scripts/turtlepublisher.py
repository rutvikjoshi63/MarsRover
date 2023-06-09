#/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist

rospy.init_node('topic_publisher')
pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size= 2)
rate = rospy.Rate(2)

var = Twist()
print("Moving the robot")
var.linear.x = 0.2
var.linear.y = 0.3
var.linear.z = 0.4
var.angular.x = 0
var.angular.y = 0
var.angular.z = 0.2



while not rospy.is_shutdown():
    pub.publish(var)
    rate.sleep()

