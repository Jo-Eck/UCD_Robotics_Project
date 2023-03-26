import numpy as np
import math
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider



# Rotation matrix around z-axis
def rot_z(theta):
    # convert to radians
    theta = np.deg2rad(theta)
    return np.array([[np.cos(theta), -np.sin(theta), 0],
                  [np.sin(theta), np.cos(theta), 0],
                  [0, 0, 1]]).round(4)
    
    
def rot_x(theta):
    theta = np.deg2rad(theta)
    return np.array([[1, 0, 0],
                  [0, np.cos(theta), -np.sin(theta)],
                  [0, np.sin(theta), np.cos(theta)]]).round(4)


def rot_y(theta):
    theta = np.deg2rad(theta)
    return np.array([[np.cos(theta), 0, np.sin(theta)],
                  [0, 1, 0],
                  [-np.sin(theta), 0, np.cos(theta)]]).round(4)
    
def angle_between_vectors(v1, v2):
    dot_product = sum((a*b) for a, b in zip(v1, v2))
    magnitude_v1 = math.sqrt(sum((a**2) for a in v1))
    magnitude_v2 = math.sqrt(sum((a**2) for a in v2))
    cos_angle = dot_product / (magnitude_v1 * magnitude_v2)
    angle_in_radians = math.acos(cos_angle)
    angle_in_degrees = math.degrees(angle_in_radians)
    return angle_in_degrees

# Define the lengths of the links
# as vectors int the base position
base_elbow = np.array([-9.3, 0, 3.5]).reshape(3,1)
elbow_wrist = np.array([17,0,0]).reshape(3,1)


# Angle of the base
base_rot = 30

# Angle of the arm
arm_direction = -20


# getting the vector between the base and the hand
print (rot_z(base_rot).dot(rot_y(arm_direction).dot(elbow_wrist)+base_elbow))