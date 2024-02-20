// #ifndef POSE_H_
// #define POSE_H_

// #include <ros.h>
// #include <cmath>
// #include <geometry_msgs/PoseStamped.h>
// #include <tf/tf.h>
// #include <std_msgs/Float64.h>
// #include <iostream>
// #include <ostream>

// // Constants
// const double L = 0.580;               // Wheelbase (distance between the wheels) in meters
// const double ticks_per_meter = 14.64; // Number of encoder ticks per meter

// int leftFrontTicks = 0;
// int rightFrontTicks = 0;
// int leftBackTicks = 0;
// int rightBackTicks = 0;

// double LF_vel=0;
// double RF_vel=0;
// double LB_vel=0;
// double RB_vel=0;

// // Global variables for robot pose
// double theta = 0.0; // Initial orientation

// // ROS objects
// ros::NodeHandle nh;
// geometry_msgs::PoseStamped pose_msg;
// ros::Publisher pose_pub("/pose", &pose_msg);
// geometry_msgs::Vector3 wheel_vel_msg;
// ros::Publisher wheel_vel_pub("/wheel_velocities", &wheel_vel_msg);

// // Function to initialize ROS and pose publisher
// void setupPose()
// {
//     // nh.initNode();
//     nh.advertise(pose_pub);
//     nh.advertise(wheel_vel_pub);
// }

// // Function to update pose and wheel velocities
// void loopPose(int leftFrontTicks, int rightFrontTicks, int leftBackTicks, int rightBackTicks)
// {
//     if ((LF_vel != 0 || RF_vel != 0 || LB_vel != 0 || RB_vel != 0)
//         && (leftFrontTicks == 0 && rightFrontTicks == 0 && leftBackTicks == 0 && rightBackTicks == 0))
//         {
//             double LF_vel = 0.0;
//             double RF_vel = 0.0;
//             double LB_vel = 0.0;
//             double RB_vel = 0.0;
//         }

//     else
//     {
//         // wheel vel
//         double LF_vel = leftFrontTicks / ticks_per_meter;
//         double RF_vel = rightFrontTicks / ticks_per_meter;
//         double LB_vel = leftBackTicks / ticks_per_meter;
//         double RB_vel = rightBackTicks / ticks_per_meter;

//         // linear and angular displacement
//         double d_left = (leftFrontTicks + leftBackTicks) / 2.0;
//         double d_right = (rightFrontTicks + rightBackTicks) / 2.0;
//         double d = (d_left + d_right) / 2.0 / ticks_per_meter;
//         double d_theta = (d_right - d_left) / L / ticks_per_meter;

//         // updating robot pose
//         x += d * cos(theta + d_theta / 2.0);
//         y += d * sin(theta + d_theta / 2.0);
//         theta += d_theta;

//         // theta is within [-pi, pi] range
//         theta = fmod(theta + M_PI, 2 * M_PI) - M_PI;

//         // publishing pose message
//         pose_msg.header.stamp = nh.now();
//         pose_msg.pose.position.x = x;
//         pose_msg.pose.position.y = y;
//         pose_msg.pose.orientation = tf::createQuaternionFromYaw(theta);
//         pose_pub.publish(&pose_msg);

//         // publishing wheel velocities
//         wheel_vel_msg.x = LF_vel;
//         wheel_vel_msg.y = RF_vel;
//         wheel_vel_msg.z = (LB_vel + RB_vel) / 2.0; // Assuming a four-wheeled robot with two wheels on each side
//         wheel_vel_pub.publish(&wheel_vel_msg);
//     }

//     // print pose and wheel values
//     //  ROS_INFO("Pose - X: %f, Y: %f, Theta: %f", x, y, theta);
//     //  ROS_INFO("Wheel Velocities - LF: %f, RF: %f, LB: %f, RB: %f", LF_vel, RF_vel, LB_vel, RB_vel);

//     // print pose and wheel values
//     Serial.print("Pose-X: ");
//     Serial.print(x);
//     Serial.print(", Y: ");
//     Serial.print(y);
//     Serial.print(", Theta: ");
//     Serial.println(theta);

//     Serial.print("Wheel Velocities-LF: ");
//     Serial.print(LF_vel);
//     Serial.print(", RF: ");
//     Serial.print(RF_vel);
//     Serial.print(", LB: ");
//     Serial.print(LB_vel);
//     Serial.print(", RB: ");
//     Serial.println(RB_vel);

//     // print pose and wheel values
//     //  ROS_H_("Pose - X: %f, Y: %f, Theta: %f", x, y, theta);
//     //  ROS_H_("Wheel Velocities - LF: %f, RF: %f, LB: %f, RB: %f", LF_vel, RF_vel, LB_vel, RB_vel);

//     // nh.spinOnce();
// }

// #endif /* POSE_H_ */


// #ifndef POSE_H_
// #define POSE_H_

// #include <ros.h>
// #include <cmath>
// #include <geometry_msgs/PoseStamped.h>
// #include <tf/tf.h>
// #include <std_msgs/Float64.h>
// #include <iostream>
// #include <ostream>

// // Constants
// const double L = 0.580; // Wheelbase (distance between the wheels) in meters
// const double ticks_per_meter = 14.64; // Number of encoder ticks per meter

// int leftFrontTicks = 0;
// int rightFrontTicks = 0;
// int leftBackTicks = 0;
// int rightBackTicks = 0;

// // Global variables for robot pose
// double theta = 0.0;   // Initial orientation

// // Variable to store previous encoder ticks
// int prev_leftFrontTicks = 0;
// int prev_rightFrontTicks = 0;
// int prev_leftBackTicks = 0;
// int prev_rightBackTicks = 0;

// // ROS objects
// ros::NodeHandle nh;
// geometry_msgs::PoseStamped pose_msg;
// ros::Publisher pose_pub("/pose", &pose_msg);
// geometry_msgs::Vector3 wheel_vel_msg;
// ros::Publisher wheel_vel_pub("/wheel_velocities", &wheel_vel_msg);

// // Function to initialize ROS and pose publisher
// void setupPose() {
//     // nh.initNode();
//     nh.advertise(pose_pub);
//     nh.advertise(wheel_vel_pub);
// }

// // Function to update pose and wheel velocities
// void loopPose(int leftFrontTicks, int rightFrontTicks, int leftBackTicks, int rightBackTicks) {
//     // Calculate wheel velocities
//     double LF_vel = 0.0;
//     double RF_vel = 0.0;
//     double LB_vel = 0.0;
//     double RB_vel = 0.0;

//     if (leftFrontTicks != 0 || rightFrontTicks != 0 || leftBackTicks != 0 || rightBackTicks != 0) {
//         // Calculate velocities only if there is movement
//         LF_vel = (leftFrontTicks - prev_leftFrontTicks) / ticks_per_meter;
//         RF_vel = (rightFrontTicks - prev_rightFrontTicks) / ticks_per_meter;
//         LB_vel = (leftBackTicks - prev_leftBackTicks) / ticks_per_meter;
//         RB_vel = (rightBackTicks - prev_rightBackTicks) / ticks_per_meter;

//         // Update previous tick counts
//         prev_leftFrontTicks = leftFrontTicks;
//         prev_rightFrontTicks = rightFrontTicks;
//         prev_leftBackTicks = leftBackTicks;
//         prev_rightBackTicks = rightBackTicks;
//     }

//     // Update robot pose
//     double d_left = (leftFrontTicks + leftBackTicks) / 2.0;
//     double d_right = (rightFrontTicks + rightBackTicks) / 2.0;
//     double d = (d_left + d_right) / 2.0;
//     double d_theta = (d_right - d_left) / L;
//     x += d * cos(theta + d_theta / 2.0);
//     y += d * sin(theta + d_theta / 2.0);
//     theta += d_theta;
//     theta = fmod(theta + M_PI, 2 * M_PI) - M_PI;

//     // Publish pose message
//     pose_msg.header.stamp = nh.now();
//     pose_msg.pose.position.x = x;
//     pose_msg.pose.position.y = y;
//     pose_msg.pose.orientation = tf::createQuaternionFromYaw(theta);
//     pose_pub.publish(&pose_msg);

//     // Publish wheel velocities
//     wheel_vel_msg.x = LF_vel;
//     wheel_vel_msg.y = RF_vel;
//     wheel_vel_msg.z = (LB_vel + RB_vel) / 2.0; // Assuming a four-wheeled robot with two wheels on each side
//     wheel_vel_pub.publish(&wheel_vel_msg);

//     // Print pose and wheel values
//     Serial.print("Pose-X: ");
//     Serial.print(x);
//     Serial.print(", Y: ");
//     Serial.print(y);
//     Serial.print(", Theta: ");
//     Serial.println(theta);

//     Serial.print("Wheel Velocities-LF: ");
//     Serial.print(LF_vel);
//     Serial.print(", RF: ");
//     Serial.print(RF_vel);
//     Serial.print(", LB: ");
//     Serial.print(LB_vel);
//     Serial.print(", RB: ");
//     Serial.println(RB_vel);
// }

// #endif /* POSE_H_ */