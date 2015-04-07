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

static speed_t speed;
int32_t Kp = 0;
int32_t Ki = 0;
int32_t Kd = 0;
int32_t dt = 10;
int32_t Ke = 1000;

void pid_init(void) {
	speed.value = 0xD173;
}

void pid_set_rpm_high(uint8_t sp) {
	speed.bytefield.high = sp;
}

void pid_set_rpm_low(uint8_t sp) {
	speed.bytefield.low = sp;
}

void pid_set_rpm(uint16_t sp) {
    speed.value = sp;
}

uint8_t pid_get_rpm_high(void) {
	return speed.bytefield.high;
}

uint8_t pid_get_rpm_low(void) {
	return speed.bytefield.low;
}

uint16_t pid_get_rpm(void) {
    return speed.value;
}

void pid_task(void) {
    static int32_t esum = 0;
    static int32_t eprev = 0;
    int32_t e;
    int32_t s;
    e = 0;
    // e = ((int32_t) motor_get_speed_rpm()) - ((int32_t) speed.value)
    esum = esum + e;
    s = (Kp * e) + (Ki * dt * esum) + (Kd * (e - eprev) / dt);
    eprev = e;
    pwm_set_raw((uint16_t) (s / Ke));
    return;
}
