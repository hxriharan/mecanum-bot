const int odomRate = 10;

unsigned long odom_time = 0, _odom_time = 0;

extern double x_pos, y_pos, theta_pos;
extern double x_vel, y_vel, theta_vel;

extern float wheel_radius, wheel_separation_width, wheel_separation_length;
extern double LF_vel, RF_vel, LB_vel, RB_vel;

const double ticks_per_rotation = 40;
int LF_prev_pos, RF_prev_pos, LB_prev_pos, RB_prev_pos;

void loopOdom() {

    if (millis() - odom_time > 1000 / odomRate) {
        
        _odom_time = odom_time;
        odom_time = millis();
        double dt = (odom_time - _odom_time) / 1000.0;

        // Calculate resultant linear velocities
        x_vel = (LF_vel + RF_vel + LB_vel + RB_vel) / 4.0 * wheel_radius;
        y_vel = (-LF_vel + RF_vel + LB_vel - RB_vel) / 4.0 * wheel_radius;
        theta_vel = (-LF_vel + RF_vel - LB_vel + RB_vel) * wheel_radius / (4.0 * (wheel_separation_width + wheel_separation_length));

        // Update positions using forward kinematics
        x_pos += cos(theta_pos) * x_vel * dt - sin(theta_pos) * y_vel * dt;
        y_pos += sin(theta_pos) * x_vel * dt + cos(theta_pos) * y_vel * dt;
        theta_pos += theta_vel * dt;

        // Normalize theta_pos to keep it within [0, 2 * PI)
        // theta_pos = fmod(theta_pos, 2 * PI);
        // if (theta_pos < 0) theta_pos += 2 * PI;

         if (theta_pos >= 2 * PI)
        {
            theta_pos -= 2 * PI;
        }
        if (theta_pos <= (-2 * PI))
        {
            theta_pos += 2 * PI;
        }

		#if DEBUG_ODOM
            Serial.printf("[DEBUG] (odom) x_pos: %f, y_pos: %f, theta_pos: %f\n", x_pos, y_pos, theta_pos);
        #endif
	}
}
