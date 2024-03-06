// #ifndef ODOM_H
// #define ODOM_H

// #include <cmath>
// #include "distance.h"
// #include "encoder.h"
// // Constants
// extern const double ticks_per_meter;
// float wheel_radius = 0.152/2;
// float wheel_separation_width = 0.460;
// float wheel_separation_length = 0.460;


// // Function to calculate odometry
// void calculateOdometry(int leftFront_ticks, int rightFront_ticks, int leftBack_ticks, int rightBack_ticks) {
    
//     // Print encoder values
//     Serial.print("Left Front Encoder Ticks: ");
//     Serial.println(leftFront_ticks);
//     Serial.print("Right Front Encoder Ticks: ");
//     Serial.println(rightFront_ticks);
//     Serial.print("Left Back Encoder Ticks: ");
//     Serial.println(leftBack_ticks);
//     Serial.print("Right Back Encoder Ticks: ");
//     Serial.println(rightBack_ticks);

//     // Calculate wheel velocities
//     float LF_vel = leftFront_ticks / ticks_per_meter;
//     float RF_vel = rightFront_ticks / ticks_per_meter;
//     float LB_vel = leftBack_ticks / ticks_per_meter;
//     float RB_vel = rightBack_ticks / ticks_per_meter;

//     // Calculate total distance traveled
//     double total_distance_traveled = calculateTotalDistanceTraveled(leftFront_ticks, rightFront_ticks, leftBack_ticks, rightBack_ticks);

//     // Print wheel velocities
//     Serial.print("LF_vel: ");
//     Serial.print(LF_vel);
//     Serial.print(", RF_vel: ");
//     Serial.print(RF_vel);
//     Serial.print(", LB_vel: ");
//     Serial.print(LB_vel);
//     Serial.print(", RB_vel: ");
//     Serial.println(RB_vel);

//     // Print total distance traveled
//     Serial.print("Total Distance Traveled: ");
//     Serial.print(total_distance_traveled);
//     Serial.println(" meters");
// }

// #endif // ODOM_H
