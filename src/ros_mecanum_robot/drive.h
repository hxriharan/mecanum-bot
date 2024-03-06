extern bool movement, updating;
extern double LF_setpoint, RF_setpoint, LB_setpoint, RB_setpoint;

float wheel_radius = 0.152/2;
float wheel_separation_width = 0.460;
float wheel_separation_length = 0.460;

void loopDrive()
{
  if (!movement || updating)
    return;
  y=-y;
  // Source: https://www.robotsforroboticists.com/drive-kinematics/
  LF_setpoint = (x - y - z * (wheel_separation_width + wheel_separation_length)) / wheel_radius;
  RF_setpoint = (x + y + z * (wheel_separation_width + wheel_separation_length)) / wheel_radius;
  LB_setpoint = (x + y - z * (wheel_separation_width + wheel_separation_length)) / wheel_radius;
  RB_setpoint = (x - y + z * (wheel_separation_width + wheel_separation_length)) / wheel_radius;

  #if DEBUG_DRIVE
    Serial.printf("[DEBUG] (drive) LF: %f, RF: %f, LB: %f, RB: %f\n", LF_setpoint, RF_setpoint, LB_setpoint, RB_setpoint);
  #endif

  movement = false;
}