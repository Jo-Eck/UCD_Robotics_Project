#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int64


def listener_callback(msg):
    rospy.loginfo('I heard "%d"' % msg.data)

def main():
    rospy.init_node("sum_counter", anonymous=True)
    rospy.Subscriber('/number_count', Int64, listener_callback)
    rospy.spin()


if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass