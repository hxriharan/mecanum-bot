#ifndef ROS_H_
#define ROS_H_

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <ros/node_handle.h>
#include <std_msgs/Header.h>
#include "odom_f.h"

// extern ros::NodeHandle nh;
// extern std_msgs::Header header_msg;
#endif /* ROS_H_ */

#define LED_BUILTIN 2

bool connected = false;
bool movement = false;
double x = 0, y = 0, z = 0;

void onTwist(const geometry_msgs::Twist &msg);
void odom(const nav_msgs::Odometry &msg);

// ROS serial server
ros::NodeHandle node;
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &onTwist);
geometry_msgs::TransformStamped t;
nav_msgs::Odometry odom_msg;
ros::Publisher odom_pub("odom", &odom_msg);
tf::TransformBroadcaster broadcaster;

void setupROS()
{
  // Connect to rosserial socket server and init node. (Using default port of 11411)
  Serial.printf("[INFO] (ros) Connecting to ROS serial server at %s\n", server.toString().c_str());
  node.getHardware()->setConnection(server);
  node.initNode();
  node.subscribe(sub);      // setup subscriber
  node.advertise(odom_pub); // setup publisher
  broadcaster.init(node);   // set up broadcaster
}

void loopROS()
{
  // If value changes, notify via LED and console.
  bool conn = node.connected();
  if (connected != conn)
  {
    connected = conn;
    if (!connected)
      stop();

    // digitalWrite(LED_BUILTIN, connected? HIGH : LOW);
    Serial.print("[INFO] (ros) ");
    Serial.println(connected ? "ROS connected" : "ROS disconnected");
  }

  node.spinOnce();
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

void odometry(const nav_msgs::Odometry &msg)
{
  static tf::TransformBroadcaster broadcaster;

  // Prepare transform data
  geometry_msgs::TransformStamped odom_trans;
  odom_trans.header.frame_id = "odom";
  odom_trans.child_frame_id = "base_link";
  odom_trans.header.stamp = node.now();
  odom_trans.transform.translation.x = x_pos;
  odom_trans.transform.translation.y = y_pos;
  odom_trans.transform.translation.z = 0.0;
  odom_trans.transform.rotation = tf::createQuaternionFromYaw(theta_pos);

  // Broadcast transform
  broadcaster.sendTransform(odom_trans);

  // Publish odometry message
  odom_msg.header.stamp = node.now();
  odom_msg.pose.pose.position.x = x_pos;
  odom_msg.pose.pose.position.y = y_pos;
  odom_msg.pose.pose.position.z = 0.0;
  odom_msg.pose.pose.orientation = tf::createQuaternionFromYaw(theta_pos);

  // Set linear and angular velocities
  odom_msg.twist.twist.linear.x = x_vel;
  odom_msg.twist.twist.linear.y = y_vel;
  odom_msg.twist.twist.angular.z = theta_vel;

  // Print information about the odometry message
  Serial.println("[INFO] Publishing Odometry Message:");
  Serial.printf("  Position: x=%f, y=%f, z=%f\n", odom_msg.pose.pose.position.x, odom_msg.pose.pose.position.y, odom_msg.pose.pose.position.z);
  Serial.printf("  Orientation: qx=%f, qy=%f, qz=%f, qw=%f\n", odom_msg.pose.pose.orientation.x, odom_msg.pose.pose.orientation.y, odom_msg.pose.pose.orientation.z, odom_msg.pose.pose.orientation.w);
  // Serial.printf("  Linear Velocity: x=%f, y=%f\n", odom_msg.twist.twist.linear.x, odom_msg.twist.twist.linear.y);
  // Serial.printf("  Angular Velocity: z=%f\n", odom_msg.twist.twist.angular.z);

  // Publish odometry message
  odom_pub.publish(&odom_msg);
}
