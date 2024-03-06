// #ifndef DISTANCE_H_
// #define DISTANCE_H_

// #include <cmath>

// const double wheel_diameter_mm = 152; // Wheel size in mm
// const double pi = 3.14159265358979323846;
// extern const double ticks_per_meter = 14; // Adjust as needed

// double wheel_circumference_mm = pi * wheel_diameter_mm;

// double calculateDistanceTraveled(int encoder_ticks) {
//     double distance_traveled_mm = encoder_ticks * (wheel_circumference_mm / ticks_per_meter);
//     return distance_traveled_mm;
// }

// double calculateTotalDistanceTraveled(int leftFront_ticks, int rightFront_ticks, int leftBack_ticks, int rightBack_ticks) {
//     double leftFront_distance_traveled_mm = calculateDistanceTraveled(leftFront_ticks);
//     double rightFront_distance_traveled_mm = calculateDistanceTraveled(rightFront_ticks);
//     double leftBack_distance_traveled_mm = calculateDistanceTraveled(leftBack_ticks);
//     double rightBack_distance_traveled_mm = calculateDistanceTraveled(rightBack_ticks);

//     // Calculate the average distance traveled by all four wheels
//     double total_distance_traveled_mm = (leftFront_distance_traveled_mm + rightFront_distance_traveled_mm + leftBack_distance_traveled_mm + rightBack_distance_traveled_mm) / 4.0;

//     return total_distance_traveled_mm;
// }

// #endif /* DISTANCE_H_ */
