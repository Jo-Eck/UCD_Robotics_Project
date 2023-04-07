# Copyright 2016 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import rclpy
from rclpy.node import Node

from std_msgs.msg import Int64


class Number_publisher(Node):

    def __init__(self):
        super().__init__('number_publisher')
        self.publisher_ = self.create_publisher(Int64, 'number_count', 10)
        self.sum = 0
        self.i = 0
        
        self.subscription = self.create_subscription(
            Int64,
            'number',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%d"' % msg.data)
        self.sum += msg.data
        self.pass_on()

    def pass_on(self):
        msg = Int64()
        msg.data = self.sum
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing sum as: "%d"' % msg.data)
        self.i += 1
        

def main(args=None):
    rclpy.init(args=args)

    number_publisher = Number_publisher()

    rclpy.spin(number_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    number_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
