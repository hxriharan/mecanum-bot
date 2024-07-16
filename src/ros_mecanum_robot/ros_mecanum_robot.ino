#define DEBUG_ROS 0
#define DEBUG_ENCODERS 0
#define DEBUG_DRIVE 0
#define DEBUG_ODOM 1

#include "wifi.h"
#include "ota.h"
#include "ros.h"
#include "drive.h"
#include "encoder.h"
#include "pid.h"
#include "motor.h"

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/tf.h>
#include "odom.h"

ros::NodeHandle nh;
ros::Publisher odom_pub("/odom", &odom_msg);
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", onTwist);
tf::TransformBroadcaster broadcaster;

nav_msgs::Odometry odom_msg;
#define LED_BUILTIN 2

void setup()
{
  // Status LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  Serial.println();

  setupWifi();
  setupOTA();
  setupROS();
  setupEncoders();
  setupPID();
  setupMotor();
}

void loop()
{
  loopOTA();
  loopROS();
  loopDrive();
  loopEncoders();
  loopPID();
  loopMotor();
  loopOdom();
}
