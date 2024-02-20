#include <WiFi.h>
#include "encoder.h"
#include "motor.h"
#include "pid.h"


int serialTime=0;
double setpoint=0.3; //previously 0.3


void setup()
{
	Serial.begin(115200);

	setupEncoders();
	setupMotor();
	setupPID();

	// Wait for enter key to be pressed
	while (Serial.available() <= 0) {
		Serial.println("Press enter to start PID tuning");
		delay(500);
	}

	RF_setpoint = 0.5; // previously 0.5
	LF_setpoint = 0.5;
	LB_setpoint = 0.5;
	RB_setpoint = 0.5;
}


void loop()
{
	loopEnc();
	loopMotor();
	loopPID();

	if(millis()>serialTime)
	{

		
    // Serial.println(RB_vel);

    Serial.print(RF_vel);
    Serial.print(',');
    Serial.print(LF_vel);
    Serial.print(',');
    Serial.print(RB_vel);
    Serial.print(',');
    Serial.print(LB_vel);
    Serial.print(',');
    Serial.println();

		// Serial.print("setpoint:");
		// Serial.print(setpoint);
		// Serial.print(" RB_vel: ");
		// Serial.print(RB_vel);
		// Serial.println(" RB: ");

		// Serial.print(setpoint);
		// Serial.print(" LB_vel: ");
		// Serial.print(LB_vel);
		// Serial.println(" LB: ");

		// Serial.print(RB_pos);
		// Serial.print(" ");
		// Serial.println(LB_pos);
		// Serial.print(" ");
		// Serial.print(RB_pos);
		// Serial.print(" ");
		// Serial.println(LB_pos);

		serialTime+=500;
	}
}
