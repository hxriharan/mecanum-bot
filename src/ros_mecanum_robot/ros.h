// #include "ros/subscriber.h"
#ifndef ROS_H_
#define ROS_H_
#include <ros.h>
// #include "odometry.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <ros/node_handle.h>
#include <std_msgs/Header.h>

// double received_x = 0.0;
// double received_y = 0.0;

extern ros::NodeHandle nh;
extern std_msgs::Header header_msg;
#endif /* ROS_H_ */

#define LED_BUILTIN 2

bool connected = false;
bool movement = false;
double x = 0, y = 0, z = 0;

void onTwist(const geometry_msgs::Twist &msg);
// void odomCallback(const nav_msgs::Odometry &msg);

// ROS serial server
ros::NodeHandle node;
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &onTwist);
// ros::Subscriber<nav_msgs::Odometry> odom_sub("/odom", &odomCallback);

void setupROS()
{
  // Connect to rosserial socket server and init node. (Using default port of 11411)
  Serial.printf("[INFO] (ros) Connecting to ROS serial server at %s\n", server.toString().c_str());
  node.getHardware()->setConnection(server);
  node.initNode();
  node.subscribe(sub);
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

// void odomCallback(const nav_msgs::Odometry &msg)
// {
//   if (connected)
//   {
//     // Extract pose data from the received odometry message
//     received_x = msg.pose.pose.position.x;
//     received_y = msg.pose.pose.position.y;
//     geometry_msgs::Quaternion theta = msg.pose.pose.orientation;

//     // Assuming theta is available in quaternion form, you can extract it as follows:
//     // double theta = atan2(2.0 * (msg.pose.pose.orientation.w * msg.pose.pose.orientation.z + msg.pose.pose.orientation.x * msg.pose.pose.orientation.y),
//     //             1.0 - 2.0 * (msg.pose.pose.orientation.y * msg.pose.pose.orientation.y + msg.pose.pose.orientation.z * msg.pose.pose.orientation.z));

// #if DEBUG_ROS
//     Serial.print("[DEBUG] (ros) Pose - X: ");
//     Serial.print(received_x);
//     Serial.print(", Y: ");
//     Serial.print(received_y);
//     Serial.print(", Quaternion: (");
//     Serial.print(theta.x);
//     Serial.print(", ");
//     Serial.print(theta.y);
//     Serial.print(", ");
//     Serial.print(theta.z);
//     Serial.print(", ");
//     Serial.print(theta.w);
//     Serial.println(")");
// #endif
//   }
//   else
//     stop();
// }
