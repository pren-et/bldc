/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file  pid.c
 * \brief
 * \author pren-et
 *
 */

#include "pid.h"
#include "interrupts.h"
#include "pwm.h"

static speed_t current_speed, tmp_speed;
int32_t Kp = 10000000;
int32_t Ki = 0;
int32_t Kd = 0;
const int32_t dt = TASK_PID;
int32_t Ke = 1000;

void pid_init(void) {
	current_speed.value = 15000;
	tmp_speed.value = 0x0000;//1500
}

void pid_set_rpm_high(uint8_t sp) {
	tmp_speed.bytefield.high = sp;
}

void pid_set_rpm_low(uint8_t sp) {
	tmp_speed.bytefield.low = sp;
	current_speed.value = tmp_speed.value;
}

void pid_set_rpm(uint16_t sp) {
	current_speed.value = sp;
}

uint8_t pid_get_rpm_high(void) {
	return current_speed.bytefield.high;
}

uint8_t pid_get_rpm_low(void) {
	return current_speed.bytefield.low;
}

uint16_t pid_get_rpm(void) {
    return current_speed.value;
}

void pid_task(void) {
    static int32_t esum = 0;
    static int32_t eprev = 0;
    int32_t e = 0;
    int32_t s = 0;
    uint32_t Time_Avg, rpm_meas;
    Time_Avg = getTime_U();
    Time_Avg += getTime_V();
    Time_Avg += getTime_W();
    Time_Avg = Time_Avg / 3;
    rpm_meas = 5625000 / Time_Avg;
    e = rpm_meas - ((int32_t) current_speed.value);
    esum = esum + e;
    s = (Kp * e) + (Ki * dt * esum) + (Kd * (e - eprev) / dt);
    eprev = e;
    if(motor_get_status() != MOTOR_STATUS_AUTO_FREE)
	{
		esum = 0;
		return;
	}
    pwm_set_raw((uint16_t) (s / Ke));
    return;
}
