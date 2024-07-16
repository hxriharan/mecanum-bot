#include <PID_v1.h>

double kp_LF = 20, ki_LF = 0.01, kd_LF = 0.1;
double kp_RF = 20, ki_RF = 0.01, kd_RF = 0.1;
double kp_LB = 20, ki_LB = 0.01, kd_LB = 0.1;
double kp_RB = 20, ki_RB = 0.01, kd_RB = 0.1;
double LF_setpoint = 0, RF_setpoint = 0, LB_setpoint = 0, RB_setpoint = 0;

PID *RF_PID, *LF_PID, *LB_PID, *RB_PID;

extern double LF_vel, RF_vel, LB_vel, RB_vel;
extern double LF_pwm, RF_pwm, LB_pwm, RB_pwm;

void setupPID(){
	RF_PID = new PID(&RF_vel, &RF_pwm, &RF_setpoint, kp_RF, ki_RF, kd_RF, DIRECT);
	LF_PID = new PID(&LF_vel, &LF_pwm, &LF_setpoint, kp_LF, ki_LF, kd_LF, DIRECT);
	LB_PID = new PID(&LB_vel, &LB_pwm, &LB_setpoint, kp_LB, ki_LB, kd_LB, DIRECT);
	RB_PID = new PID(&RB_vel, &RB_pwm, &RB_setpoint, kp_RB, ki_RB, kd_RB, DIRECT);

  RF_PID->SetMode(AUTOMATIC);
	RF_PID->SetOutputLimits(-255,255);

	LF_PID->SetMode(AUTOMATIC);
	LF_PID->SetOutputLimits(-255,255);

	LB_PID->SetMode(AUTOMATIC);
	LB_PID->SetOutputLimits(-255,255);

	RB_PID->SetMode(AUTOMATIC);
	RB_PID->SetOutputLimits(-255,255);
}

void loopPID(){
	RF_PID->Compute();
	LF_PID->Compute();
	LB_PID->Compute();
	RB_PID->Compute();
}
