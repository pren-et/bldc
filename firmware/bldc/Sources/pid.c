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
#include "drv8301.h"

static speed_t current_speed, tmp_speed;
const int32_t Kp = -50;
const int32_t Ki = -2;
const int32_t Kd = 0;
const int32_t dt = TASK_PID;
const int32_t Ke = 1000;

/* 
 *           sec/min          us/s            see BEMF-Timing    avg       Timer-resolution
 * rmp    =    60     *    1_000_000us    /      (( 2*T       /   3)    *   5.3333333333us) 
 *  = 16875000 / T
 */
#define calc_Const 16875000

void pid_init(void) {
	tmp_speed.value = current_speed.value = 45000;//rpm
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
    int16_t pwmValue = 0;
    int32_t e = 0;
    int32_t s = 0;
    uint32_t Time_sum, rpm_meas;
    uint32_t debug1, debug2, debug3;
    debug1 = getTime_U();
    debug2 = getTime_V();
    debug3 = getTime_W();
    Time_sum = debug1 + debug2 + debug3;
//    Time_sum  = getTime_U();
//    Time_sum += getTime_V();
//    Time_sum += getTime_W();
    rpm_meas = calc_Const / Time_sum; // Average on time is calculated into the strange number in the numerator
    e = rpm_meas - ((int32_t) current_speed.value);
    esum = esum + e;
    s = (Kp * e) + (Ki * dt * esum) + (Kd * (e - eprev) / dt);
    eprev = e;
    pwmValue = (int16_t)(s / Ke);
    pwmValue += 200; /* Vorsteuerung */
    pwmValue = pwmValue > 1023 ? 1023 : pwmValue;
    pwmValue = pwmValue < 0    ? 0    : pwmValue;
    if(motor_get_status() == MOTOR_STATUS_AUTO_PID)
    {
    	static uint16_t pid_cnt = 0;
    	pid_cnt++;
    	if (pid_cnt >= 300) {
            //drv8301_disable();
    		asm{
            	nop
    		}
    	}
        pwm_set_raw(pwmValue);        
    }
    else
    {
		esum = 0;
		return;
	}

    return;
}
