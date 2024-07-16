#ifndef ROS_H
#define ROS_H

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/tf.h>
// #include "odom.h"

#define LED_BUILTIN 2

bool connected = false;
bool movement = false;
float x = 0, y = 0, z = 0;

extern ros::NodeHandle nh;
extern ros::Publisher odom_pub;
extern ros::Subscriber<geometry_msgs::Twist> sub;
extern tf::TransformBroadcaster broadcaster;  // Declare broadcaster here
extern nav_msgs::Odometry odom_msg;
extern geometry_msgs::TransformStamped odom_trans;
void onTwist(const geometry_msgs::Twist &msg);


// Odometry variables
double x_pos = 0, y_pos = 0, theta_pos = 0;
double x_vel = 0, y_vel = 0, theta_vel = 0;

geometry_msgs::Quaternion createQuaternionMsgFromYaw(double yaw) {
  geometry_msgs::Quaternion q;
  q.w = cos(yaw * 0.5);
  q.x = 0.0;
  q.y = 0.0;
  q.z = sin(yaw * 0.5);
  return q;
}

void setupROS()
{
  // Connect to rosserial socket server and init node. (Using default port of 11411)
  Serial.printf("[INFO] (ros) Connecting to ROS serial server at %s\n", server.toString().c_str());
  nh.getHardware()->setConnection(server);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(odom_pub);
  broadcaster.init(nh);
}

void publishOdometry()
{
  // Publish odometry message
  static nav_msgs::Odometry odom_msg;
  
  // Populate odometry message fields
  odom_msg.header.stamp = nh.now();
  odom_msg.header.frame_id = "odom";  
  // Position
  odom_msg.pose.pose.position.x = x_pos * 100;
  odom_msg.pose.pose.position.y = y_pos * 100;
  odom_msg.pose.pose.position.z = 0.0;
  odom_msg.pose.pose.orientation = createQuaternionMsgFromYaw(theta_pos);
  
  odom_msg.child_frame_id = "base_link";
  // Velocity
  odom_msg.twist.twist.linear.x = x_vel;
  odom_msg.twist.twist.linear.y = y_vel;
  odom_msg.twist.twist.angular.z = theta_vel;
  // Publish the odometry message
  odom_pub.publish(&odom_msg);

  // Serial.print("Odometry message size: ");
  // Serial.println(sizeof(odom_msg));

  // Broadcast the transform odom->base_link
  static geometry_msgs::TransformStamped odom_trans;
  odom_trans.header.stamp = nh.now();
  odom_trans.header.frame_id = "odom";
  odom_trans.child_frame_id = "base_link";

  odom_trans.transform.translation.x = x_pos * 100;
  odom_trans.transform.translation.y = y_pos * 100;
  odom_trans.transform.translation.z = 0.0; // Ensure z is 0.0 for a 2D robot
  odom_trans.transform.rotation = createQuaternionMsgFromYaw(theta_pos);

  // Send the transform
  broadcaster.sendTransform(odom_trans);
}

void loopROS()
{
  // If value changes, notify via LED and console.
  bool conn = nh.connected();
  if (connected != conn)
  {
    connected = conn;
    if (!connected)
      stop();
      
    // digitalWrite(LED_BUILTIN, connected? HIGH : LOW);
    Serial.print("[INFO] (ros) ");
    Serial.println(connected ? "ROS connected" : "ROS disconnected");
  }
  
  nh.spinOnce(); 
  publishOdometry();
}

void stop()
{
  x = y = z = 0;
  movement = true;
}

void onTwist(const geometry_msgs::Twist &msg)
{
  if (connected)
  {
    // Cap values at [-1 .. 1]
    x = max(min(msg.linear.x, 1.0f), -1.0f);
    y = max(min(msg.linear.y, 1.0f), -1.0f);
    z = max(min(msg.angular.z, 1.0f), -1.0f);
    movement = true;

  #if DEBUG_ROS
    Serial.printf("[DEBUG] (ros) x: %f, y: %f, z: %f\n", x, y, z);
  #endif
  }
  else
    stop();
}

#endif // ROS_H