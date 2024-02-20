// #ifndef ODOMETRY_H_
// #define ODOMETRY_H_

// // #include <ros.h>
// #include <cmath>
// #include <nav_msgs/Odometry.h>
// #include <tf/tf.h>
// #include <std_msgs/Float64.h>
// #include <iostream>
// #include <ostream>

// extern double x_pos;  // x position
// extern double y_pos;  // y position
// extern const double L;  // wheelbase (distance between the wheels) in meters
// extern const double ticks_per_meter;  // number of encoder ticks per meter
// extern const double W;  // track width
// extern double vx;  // Linear velocity
// extern double vy;  // Sideways velocity
// extern double omega;  // Angular velocity
// extern int leftFrontTicks;
// extern int rightFrontTicks;
// extern int leftBackTicks;
// extern int rightBackTicks;
// extern double LF_vel;
// extern double RF_vel;
// extern double LB_vel;
// extern double RB_vel;
// extern double theta;  // Initial orientation

// // ROS objects
// extern ros::NodeHandle nh;
// extern ros::Publisher odom_pub;
// ros::Publisher odom_pub("/odom", &odom_pub);

// // Function to initialize ROS and pose publisher
// void setupOdometry()
// {
//     nh.advertise(odom_pub);
// }

// // Function to update pose and wheel velocities
// void loopOdometry(int leftFrontTicks, int rightFrontTicks, int leftBackTicks, int rightBackTicks)
// {
//     if ((LF_vel != 0 || RF_vel != 0 || LB_vel != 0 || RB_vel != 0) && (leftFrontTicks == 0 && rightFrontTicks == 0 && leftBackTicks == 0 && rightBackTicks == 0))
//     {
//         double LF_vel = 0.0;
//         double RF_vel = 0.0;
//         double LB_vel = 0.0;
//         double RB_vel = 0.0;
//     }

//     else
//     {
//         // Wheel velocities
//         double LF_vel = leftFrontTicks / ticks_per_meter;
//         double RF_vel = rightFrontTicks / ticks_per_meter;
//         double LB_vel = leftBackTicks / ticks_per_meter;
//         double RB_vel = rightBackTicks / ticks_per_meter;

//         // Linear and angular displacement
//         // double d_left = (leftFrontTicks + leftBackTicks) / 2.0;
//         // double d_right = (rightFrontTicks + rightBackTicks) / 2.0;
//         // double d = (d_left + d_right) / 2.0 / ticks_per_meter;
//         // double d_theta = (d_right - d_left) / L / ticks_per_meter;

//         // Calculate linear and angular velocity
//         double vx = (LF_vel + RF_vel + LB_vel + RB_vel) / 4.0;
//         double vy = (LF_vel - RF_vel + LB_vel - RB_vel) / 4.0; // Sideways velocity
//         double omega = (RF_vel - LF_vel) / W;                  // Angular velocity

//         // Update robot pose
//         double dt = 0.1;             // Time step in seconds (adjust as needed)
//         double d_theta = omega * dt; // Change in orientation
//         theta += d_theta;

//         // Normalize theta to [-pi, pi]
//         while (theta > M_PI)
//             theta -= 2.0 * M_PI;
//         while (theta < -M_PI)
//             theta += 2.0 * M_PI;

//         // Calculate change in position
//         double dx = (vx * cos(theta) - vy * sin(theta)) * dt;
//         double dy = (vx * sin(theta) + vy * cos(theta)) * dt;

//         // Update position
//         x_pos += dx;
//         y_pos += dy;

//         // Updating robot pose
//         // x += d * cos(theta + d_theta / 2.0);
//         // y += d * sin(theta + d_theta / 2.0);
//         // theta += d_theta;

//         // // Theta is within [-pi, pi] range
//         // theta = fmod(theta + M_PI, 2 * M_PI) - M_PI;

//         // Publishing odometry message
//         odom_msg.header.stamp = nh.now();
//         odom_msg.pose.pose.position.x = x_pos;
//         odom_msg.pose.pose.position.y = y_pos;
//         odom_msg.pose.pose.orientation = tf::createQuaternionFromYaw(theta);
//         odom_msg.twist.twist.linear.x = vx;
//         odom_msg.twist.twist.linear.y = vy;
//         odom_msg.twist.twist.angular.z = omega;
//         odom_msg.twist.twist.linear.x = (LF_vel + RF_vel + LB_vel + RB_vel) / 4.0; // Average linear velocity
//         odom_msg.twist.twist.angular.z = (RF_vel - LF_vel) / L;                    // Angular velocity based on differential drive model
//         odom_msg.twist.twist.angular.x = LF_vel;                                   // Left front wheel velocity
//         odom_msg.twist.twist.angular.y = RF_vel;                                   // Right front wheel velocity
//         odom_msg.twist.twist.angular.z = (LB_vel + RB_vel) / 2.0;                  // Average of left and right back wheel velocities
//         odom_pub.publish(&odom_msg);
//     }

//     // // Print pose and wheel values
//     // Serial.print("Pose-X: ");
//     // Serial.print(x_pos);
//     // Serial.print(", Y: ");
//     // Serial.print(y_pos);
//     // Serial.print(", Theta: ");
//     // Serial.println(theta);

//     // Serial.print("Linear Velocity (vx): ");
//     // Serial.print(vx);
//     // Serial.print(", Sideways Velocity (vy): "); // Add this line
//     // Serial.println(vy);                         // Add this line

//     // Serial.print("Angular Velocity (omega): ");
//     // Serial.println(omega);

//     // Serial.print("Wheel Velocities-LF: ");
//     // Serial.print(LF_vel);
//     // Serial.print(", RF: ");
//     // Serial.print(RF_vel);
//     // Serial.print(", LB: ");
//     // Serial.print(LB_vel);
//     // Serial.print(", RB: ");
//     // Serial.println(RB_vel);
// }

// #endif /* ODOMETRY_H_ */
