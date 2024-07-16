#!/usr/bin/env python3

import rospy
import numpy as np
import matplotlib.pyplot as plt
import heapq
import math
from geometry_msgs.msg import PoseStamped
from nav_msgs.msg import Path
from visualization_msgs.msg import Marker

class Node:
    def __init__(self, x, y, theta, g, h):
        self.x = x
        self.y = y
        self.theta = theta
        self.g = g  # cost to reach this node
        self.h = h  # heuristic cost to goal
        self.f = g + h  # total cost
        self.parent = None

    def __lt__(self, other):
        return self.f < other.f

class HybridAStar:
    def __init__(self, start, goal, resolution, wheel_radius, a, b):
        self.start = Node(start[0], start[1], start[2], 0, 0)
        self.goal = Node(goal[0], goal[1], goal[2], 0, 0)
        self.resolution = resolution
        self.wheel_radius = wheel_radius
        self.a = a
        self.b = b
        self.open_list = []
        self.closed_list = set()
        self.path = []

    def heuristic(self, node):
        return math.sqrt((node.x - self.goal.x) ** 2 + (node.y - self.goal.y) ** 2)

    def is_collision(self, x, y):
        # Implement your collision checking here
        return False

    def reconstruct_path(self, node):
        path = []
        while node:
            path.append((node.x, node.y, node.theta))
            node = node.parent
        return path[::-1]

    def inverse_kinematics(self, Vx, Vy, omega):
        a, b, R = self.a, self.b, self.wheel_radius
        velocities = np.array([
            [1, 1, -(a + b)],
            [-1, 1, (a + b)],
            [1, 1, -(a + b)],
            [-1, 1, (a + b)]
        ]) @ np.array([Vx, Vy, omega]) / R
        return velocities

    def run(self):
        self.start.h = self.heuristic(self.start)
        heapq.heappush(self.open_list, self.start)

        while self.open_list:
            current_node = heapq.heappop(self.open_list)
            self.closed_list.add((current_node.x, current_node.y, current_node.theta))

            if self.heuristic(current_node) < self.resolution:
                self.path = self.reconstruct_path(current_node)
                return True

            for delta_x, delta_y, delta_theta, cost in self.generate_actions(current_node.theta):
                new_x = current_node.x + delta_x
                new_y = current_node.y + delta_y
                new_theta = (current_node.theta + delta_theta) % (2 * np.pi)
                if not self.is_collision(new_x, new_y):
                    new_node = Node(new_x, new_y, new_theta, current_node.g + cost, self.heuristic(current_node))
                    new_node.parent = current_node
                    if (new_node.x, new_node.y, new_node.theta) not in self.closed_list:
                        heapq.heappush(self.open_list, new_node)
                        self.closed_list.add((new_node.x, new_node.y, new_node.theta))

        return False

    def generate_actions(self, theta):
        actions = []
        Vx_set = [0.5, -0.5, 0, 0]  # Example velocities
        Vy_set = [0, 0, 0.5, -0.5]
        omega_set = [0.1, -0.1]

        for Vx in Vx_set:
            for Vy in Vy_set:
                for omega in omega_set:
                    wheel_velocities = self.inverse_kinematics(Vx, Vy, omega)
                    cost = np.sum(np.abs(wheel_velocities))  # Example cost function
                    delta_x = Vx * np.cos(theta) - Vy * np.sin(theta)
                    delta_y = Vx * np.sin(theta) + Vy * np.cos(theta)
                    delta_theta = omega
                    actions.append((delta_x, delta_y, delta_theta, cost))
        return actions

    def get_ros_path(self):
        ros_path = Path()
        ros_path.header.frame_id = "map"
        for x, y, theta in self.path:
            pose = PoseStamped()
            pose.pose.position.x = x
            pose.pose.position.y = y
            pose.pose.orientation.z = np.sin(theta / 2.0)
            pose.pose.orientation.w = np.cos(theta / 2.0)
            ros_path.poses.append(pose)
        return ros_path

class HybridAStarNode:
    def __init__(self):
        rospy.init_node('hybrid_astar_node')
        self.goal_sub = rospy.Subscriber('/move_base_simple/goal', PoseStamped, self.goal_callback)
        self.path_pub = rospy.Publisher('/hybrid_astar_path', Path, queue_size=1)
        self.start = (0, 0, 0)
        self.goal = None
        self.resolution = 0.5
        self.wheel_radius = 0.1
        self.a = 0.5
        self.b = 0.5
        rospy.spin()

    def goal_callback(self, goal_msg):
        self.goal = (goal_msg.pose.position.x, goal_msg.pose.position.y, 0)
        hybrid_astar = HybridAStar(self.start, self.goal, self.resolution, self.wheel_radius, self.a, self.b)
        if hybrid_astar.run():
            ros_path = hybrid_astar.get_ros_path()
            self.path_pub.publish(ros_path)
        else:
            rospy.loginfo("Path not found")

if __name__ == "__main__":
    try:
        HybridAStarNode()
    except rospy.ROSInterruptException:
        pass

