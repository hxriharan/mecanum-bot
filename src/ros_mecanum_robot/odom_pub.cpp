#include "odometry.h"
// #include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>                    // Include tf header for quaternion operations
#include <tf/transform_broadcaster.h> // Include for TF broadcasting
#include <tf/transform_datatypes.h>

// // Constants
const double L = 0.580;               // Wheelbase (distance between the wheels) in meters
const double ticks_per_meter = 14.64; // Number of encoder ticks per meter
const double W = 0.428;               // Track Width

int leftFrontTicks = 0;
int rightFrontTicks = 0;
int leftBackTicks = 0;
int rightBackTicks = 0;

double LF_vel = 0;
double RF_vel = 0;
double LB_vel = 0;
double RB_vel = 0;

double x_pos = 0;
double y_pos = 0;

bool odom_msg_exists = false;               // Assuming it's a boolean flag indicating whether odom_msg is available
nav_msgs::Odometry odom_msg;                // Assuming it's of type nav_msgs::Odometry
geometry_msgs::TransformStamped odom_trans; // Assuming it's of type geometry_msgs::TransformStamped

// // Global variables for robot pose
double theta = 0.0; // Initial orientation

ros::Publisher odom_pub;

// Function to initialize ROS and pose publisher
void setupOdometryI(ros::NodeHandle &nh)
{
    odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 20); // Advertise odometry publisher
}

// Function to update pose and wheel velocities
void loopOdometryI(int leftFrontTicks, int rightFrontTicks, int leftBackTicks, int rightBackTicks)
{
    // Calculate wheel velocities in meters per second
    double LF_vel = leftFrontTicks / ticks_per_meter;
    double RF_vel = rightFrontTicks / ticks_per_meter;
    double LB_vel = leftBackTicks / ticks_per_meter;
    double RB_vel = rightBackTicks / ticks_per_meter;

    // Update header timestamp
    ros::Time current_time = ros::Time::now();

    // Initialize odom_trans
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = ros::Time::now();
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    // Now you can proceed to use odom_trans to assign values for the transformation
    // For example:
    odom_trans.transform.translation.x = 0.0;
    odom_trans.transform.translation.y = 0.0;
    odom_trans.transform.translation.z = 0.0;
    // Assign rotation using quaternion (if needed)
    odom_trans.transform.rotation.x = 0.0;
    odom_trans.transform.rotation.y = 0.0;
    odom_trans.transform.rotation.z = 0.0;
    odom_trans.transform.rotation.w = 1.0;

    // Calculate linear and angular velocity
    double vx = (LF_vel + RF_vel + LB_vel + RB_vel) / 4.0;
    double vy = (LF_vel - RF_vel + LB_vel - RB_vel) / 4.0; // Sideways velocity
    double omega = (RF_vel - LF_vel) / W;                  // Angular velocity

    // Update robot pose
    double dt = 0.1;             // Time step in seconds (adjust as needed)
    double d_theta = omega * dt; // Change in orientation
    theta += d_theta;

    // Normalize theta to [-pi, pi]
    while (theta > M_PI)
        theta -= 2.0 * M_PI;
    while (theta < -M_PI)
        theta += 2.0 * M_PI;

    // Calculate change in position
    double dx = (vx * cos(theta) - vy * sin(theta)) * dt;
    double dy = (vx * sin(theta) + vy * cos(theta)) * dt;

    // Update position
    x_pos += dx;
    y_pos += dy;

    // Broadcast TF for each wheel
    static tf::TransformBroadcaster wheel_broadcaster;
    geometry_msgs::TransformStamped wheel_trans;

    // Assuming odom_trans is declared somewhere before this function
    // Initialize the header of odom_trans
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link"; // Assuming "base_link" is your robot's base frame


    // Right front wheel
    wheel_trans.header.stamp = current_time;
    wheel_trans.header.frame_id = "base_link"; // Frame relative to the base link
    wheel_trans.child_frame_id = "right_front_wheel_link";
    wheel_trans.transform.translation.x = -0.305; // Adjusted based on URDF
    wheel_trans.transform.translation.y = 0.35;  // Adjusted based on URDF
    wheel_trans.transform.translation.z = 0.0;
    tf::Quaternion right_front_quat;
    right_front_quat.setRPY(1.570795, 0, 0); // Adjusted based on URDF
    tf::quaternionTFToMsg(right_front_quat, wheel_trans.transform.rotation);
    wheel_broadcaster.sendTransform(wheel_trans);

    // Left front wheel
    wheel_trans.header.stamp = current_time;
    wheel_trans.header.frame_id = "base_link"; // Frame relative to the base link
    wheel_trans.child_frame_id = "left_front_wheel_link";
    wheel_trans.transform.translation.x = -0.305; // Adjusted based on URDF
    wheel_trans.transform.translation.y = -0.35;   // Adjusted based on URDF
    wheel_trans.transform.translation.z = 0.0;
    tf::Quaternion left_front_quat;
    left_front_quat.setRPY(1.570795, 0, 0); // Adjusted based on URDF
    tf::quaternionTFToMsg(left_front_quat, wheel_trans.transform.rotation);
    wheel_broadcaster.sendTransform(wheel_trans);

    // Right back wheel
    wheel_trans.header.stamp = current_time;
    wheel_trans.header.frame_id = "base_link"; // Frame relative to the base link
    wheel_trans.child_frame_id = "right_back_wheel_link";
    wheel_trans.transform.translation.x = 0.305; // Adjusted based on URDF
    wheel_trans.transform.translation.y = 0.35; // Adjusted based on URDF
    wheel_trans.transform.translation.z = 0.0;
    tf::Quaternion right_back_quat;
    right_back_quat.setRPY(1.570795, 0, 0); // Adjusted based on URDF
    tf::quaternionTFToMsg(right_back_quat, wheel_trans.transform.rotation);
    wheel_broadcaster.sendTransform(wheel_trans);


    // Left back wheel
    wheel_trans.header.stamp = current_time;
    wheel_trans.header.frame_id = "base_link"; // Frame relative to the base link
    wheel_trans.child_frame_id = "left_back_wheel_link";
    wheel_trans.transform.translation.x = 0.305; // Adjusted based on URDF
    wheel_trans.transform.translation.y = -0.35;  // Adjusted based on URDF
    wheel_trans.transform.translation.z = 0.0;
    tf::Quaternion left_back_quat;
    left_back_quat.setRPY(1.570795, 0, 0); // Adjusted based on URDF
    tf::quaternionTFToMsg(left_back_quat, wheel_trans.transform.rotation);
    wheel_broadcaster.sendTransform(wheel_trans);

    // Update odom_trans orientation
    odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(theta);

    // Fill odometry message
    nav_msgs::Odometry odom_msg;
    odom_msg.header.stamp = current_time;
    odom_msg.header.frame_id = "odom";
    odom_msg.child_frame_id = "base_link";
    odom_msg.pose.pose.position.x = x_pos;
    odom_msg.pose.pose.position.y = y_pos;
    odom_msg.pose.pose.orientation = tf::createQuaternionMsgFromYaw(theta);
    odom_msg.twist.twist.linear.x = vx;
    odom_msg.twist.twist.linear.y = vy;
    odom_msg.twist.twist.angular.z = omega;

    // Publish odometry message
    odom_pub.publish(odom_msg);

    // Broadcast TF
    static tf::TransformBroadcaster odom_broadcaster;
    // geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";
    odom_trans.transform.translation.x = x_pos;
    odom_trans.transform.translation.y = y_pos;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(theta);
    odom_broadcaster.sendTransform(odom_trans);
}

// Main function
int main(int argc, char **argv)
{
    ros::init(argc, argv, "odometry_publisher"); // Initialize the ROS node
    ros::NodeHandle nh;                          // Initialize the ROS node handle
    setupOdometryI(nh);                          // Call setupOdometry function to initialize odometry

    // Main loop
    while (ros::ok())
    {
        // Example: Read encoder values
        int leftFrontTicks = 0;
        int rightFrontTicks = 0;
        int leftBackTicks = 0;
        int rightBackTicks = 0;

        // Call loopOdometry function with encoder values
        loopOdometryI(leftFrontTicks, rightFrontTicks, leftBackTicks, rightBackTicks);

        // Handle ROS events
        ros::spinOnce();
    }

    return 0;
}
