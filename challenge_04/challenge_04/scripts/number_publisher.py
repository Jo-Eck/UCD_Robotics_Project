#!/usr/bin/env python3
import rospy
import random
from std_msgs.msg import Int64


def main():
    rospy.init_node('number_publisher', anonymous=True)
    publish = rospy.Publisher('/number', Int64,queue_size=10)
    num = random.randint(1, 100)
    time_period = 1
    timer = rospy.Rate(time_period)

    msg = Int64()
    msg.data = num
    while not rospy.is_shutdown():
        rospy.loginfo(msg)
        publish.publish(msg)
        timer.sleep()

    


if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass