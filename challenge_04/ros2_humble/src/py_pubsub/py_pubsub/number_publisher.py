import rclpy
import random
from rclpy.node import Node

from std_msgs.msg import Int64


class MinimalPublisher(Node):

    def __init__(self):
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(Int64, 'number', 10)
        timer_period = 0.5  # seconds
        self.num = random.randint(0, 100)
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        msg = Int64()
        msg.data = self.num
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%d"' % msg.data)


def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = MinimalPublisher()

    rclpy.spin(minimal_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()