#include <ESPRotary.h>

const int enc_rate = 10;

const uint8_t LF_ENA = 36;
const uint8_t LF_ENB = 39;

const uint8_t RF_ENA = 26;
const uint8_t RF_ENB = 25;

const uint8_t LB_ENA = 32;
const uint8_t LB_ENB = 33;

const uint8_t RB_ENA = 35;
const uint8_t RB_ENB = 34;

ESPRotary LF_ENC, RF_ENC, LB_ENC, RB_ENC;
int LF_pos = 0, RF_pos = 0, LB_pos = 0, RB_pos = 0;
double LF_vel = 0, RF_vel = 0, LB_vel = 0, RB_vel = 0;
unsigned long LF_time = 0, RF_time = 0, LB_time = 0, RB_time = 0;
extern const double ticks_per_rotation;

void updateLF(ESPRotary& r)
{
	unsigned long time = millis();
	int pos = r.getPosition();
	// LF_vel = (2 * PI * (pos - LF_pos)) / (ticks_per_rotation * (time - LF_time) * 0.001); // LF_vel is in rad/s
  LF_vel = (float)(pos - LF_pos) / (time - LF_time) * 6.283185;
  // LF_vel = (float)(pos - LF_pos) * 6.283185 / ((time - LF_time) * 0.001);
	LF_pos = pos;
	LF_time = time;
	#if DEBUG_ENCODERS
		Serial.printf("[DEBUG] (encoder) LF: %d, %f\n", LF_pos, LF_vel);
	#endif
}

void updateRF(ESPRotary& r)
{
	unsigned long time = millis();
	int pos = r.getPosition();
	// RF_vel = (2 * PI * (pos - RF_pos)) / (ticks_per_rotation * (time - RF_time) * 0.001);
  RF_vel = (float)(pos - RF_pos) / (time - RF_time) * 6.283185;
  // RF_vel = (float)(pos - RF_pos) * 6.283185 / ((time - RF_time) * 0.001);
	RF_pos = pos;
	RF_time = time;
	#if DEBUG_ENCODERS
		Serial.printf("[INFO] (encoder) RF: %d, %f\n", RF_pos, RF_vel);
	#endif
}

void updateLB(ESPRotary& r)
{
	unsigned long time = millis();
	int pos = r.getPosition();
	// LB_vel = (2 * PI * (pos - LB_pos)) / (ticks_per_rotation * (time - LB_time) * 0.001);
  LB_vel = (float)(pos - LB_pos) / (time - LB_time) * 6.283185;
  // LB_vel = (float)(pos - LB_pos) * 6.283185 / ((time - LB_time) * 0.001);
	LB_pos = pos;
	LB_time = time;
	#if DEBUG_ENCODERS
		Serial.printf("[INFO] (encoder) LB: %d, %f\n", LB_pos, LB_vel);
	#endif
}

void updateRB(ESPRotary& r)
{
	unsigned long time = millis();
	int pos = r.getPosition();
	// RB_vel = (2 * PI * (pos - RB_pos)) / (ticks_per_rotation * (time - RB_time) * 0.001);
  RB_vel = (float)(pos - RB_pos) / (time - RB_time) * 6.283185;
  // RB_vel = (float)(pos - RB_pos) * 6.283185 / ((time - RB_time) * 0.001);
	RB_pos = pos;
	RB_time = time;
	#if DEBUG_ENCODERS
		Serial.printf("[INFO] (encoder) RB: %d, %f\n", RB_pos, RB_vel);
	#endif
}


void setupEncoders(){
	LF_ENC.begin(LF_ENB, LF_ENA, 7);
	RF_ENC.begin(RF_ENB, RF_ENA, 7);
	LB_ENC.begin(LB_ENB, LB_ENA, 7);
	RB_ENC.begin(RB_ENB, RB_ENA, 7);

	// LF_ENC.setChangedHandler(updateLF);
	// RF_ENC.setChangedHandler(updateRF);
	// LB_ENC.setChangedHandler(updateLB);
	// RB_ENC.setChangedHandler(updateRB);
}

void loopEncoders(){
	LF_ENC.loop();
	RF_ENC.loop();
	LB_ENC.loop();
	RB_ENC.loop();

	if (millis() - LF_time > 1000/enc_rate)
	{
		updateLF(LF_ENC);
	}
	if (millis() - RF_time > 1000/enc_rate)
	{
		updateRF(RF_ENC);
	}
	if (millis() - LB_time > 1000/enc_rate)
	{
		updateLB(LB_ENC);
	}
	if (millis() - RB_time > 1000/enc_rate)
	{
		updateRB(RB_ENC);
	}
}
