// #define USE_USBCON
#define DEBUG_ROS false
#define DEBUG_ENCODERS false
#define DEBUG_DRIVE false

#include "wifi.h"
#include "ota.h"
#include "ros.h"
#include "drive.h"
// #include "odom_f.h"
#include "encoder.h"
#include "pid.h"
#include "motor.h"
#include "pose.h"
#include "odometry.h"

#define LED_BUILTIN 2


void setup()
{
  // Status LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(115200); //115200
  Serial.println();

  setupWifi();
  setupOTA();
  setupROS();
  setupEncoders();
  setupPID();
  setupMotor();
  // setupPose();
  setupOdometry();
  // setupOdom();
}

void loop()
{
  loopOTA();
  loopROS();
  loopDrive();
  loopEncoders();
  loopPID();
  loopMotor();
  // loopPose(leftFrontTicks, rightFrontTicks, leftBackTicks, rightBackTicks);
  loopOdometry(leftFrontTicks, rightFrontTicks, leftBackTicks, rightBackTicks);
  // loopPose();
  // loopOdom();
}