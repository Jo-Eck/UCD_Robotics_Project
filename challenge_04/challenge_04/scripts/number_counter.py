#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int64
import time

sum = 0
global target
target = None

def listener_callback(msg):
     global target
     rospy.loginfo( "I heard %d", msg.data)
     if target == None:
          target = msg.data
     if target == msg.data:
        with open ("./log", "a") as f:
          f.write(str(time.time())+"\n")
     global sum
     sum += msg.data

def main():
        rospy.init_node('number_counter', anonymous=True)
        publisher = rospy.Publisher('/number_count', Int64, queue_size=10)
        i = 0
        rospy.Subscriber('/number', Int64, listener_callback)
        time_period = 1
        timer = rospy.Rate(time_period)
    
        while not rospy.is_shutdown():
            msg = Int64()
            global sum
            msg.data = sum
            publisher.publish(msg)
            rospy.loginfo('Publishing sum as: "%d"' % msg.data)
            i += 1
            timer.sleep()



if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass
