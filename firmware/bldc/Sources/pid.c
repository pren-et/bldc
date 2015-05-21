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
#include "led.h"

#define Buffersize 255
uint32_t dBuffer[Buffersize];
uint8_t MeasurementInProgress = 0;
uint8_t buffWrtInx = 0;

static speed_t current_speed, tmp_speed;

#if PID_PARAM_FOR_TEAM_NR == 32
	// Values for Team 32 (Yves Studer)
	const int32_t Kp = -800;
	const int32_t Ki = -30;
	const int32_t Kd = -0;
	const int32_t dt = TASK_PID;
	const int32_t Ke = 10000;
	const int16_t Kf = 0; /*Feed forward controll*/
    #define DEFAULT_SPEED 5000
#elif PID_PARAM_FOR_TEAM_NR == 27
	// Values for Team 27 (Daniel Winz)
	const int32_t Kp = -10000;
	const int32_t Ki = -100;
	const int32_t Kd = -50;
	const int32_t dt = TASK_PID;
	const int32_t Ke = 10000;
	const int16_t Kf = 0; /*Feed forward controll*/
    #define DEFAULT_SPEED 1400
#else
	// Default no PID with 75% pwm
	const int32_t Kp = -0;
	const int32_t Ki = -0;
	const int32_t Kd = -0;
	const int32_t dt = TASK_PID;
	const int32_t Ke = 1;
	const int16_t Kf = 767; /*Feed forward controll*/
    #define DEFAULT_SPEED 2000
#endif

/* 
 *           sec/min          us/s            see BEMF-Timing    avg       Timer-resolution
 * rmp    =    60     *    1_000_000us    /      (( 2*T       /   3)    *   5.3333333333us) 
 *  = 16875000 / T
 */
#define calc_Const 16875000

void pid_init(void) {
	tmp_speed.value = current_speed.value = DEFAULT_SPEED;//rpm
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

void pid_start_Measurement(void)
{
	MeasurementInProgress = 1;
	buffWrtInx = 0;
	led_g_off();
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
    Time_sum  = getTime_U();
    Time_sum += getTime_V();
    Time_sum += getTime_W();
    rpm_meas = calc_Const / Time_sum; // Average on time is calculated into the strange number in the numerator
    e = rpm_meas - ((int32_t) current_speed.value);
    esum = esum + e;
    s = (Kp * e) + (Ki * dt * esum) + (Kd * (e - eprev) / dt);
    eprev = e;
    pwmValue = (int16_t)(s / Ke);
    pwmValue += Kf;
    pwmValue = pwmValue > 1020 ? 1020 : pwmValue;
    pwmValue = pwmValue < 0    ? 0    : pwmValue;
    if ((pwmValue >= 1020) || (pwmValue <=0)) {
    	led_g_on();
    }
    else {
    	led_g_off();
    }
    if ( MeasurementInProgress && (buffWrtInx < Buffersize) )
    {
    	dBuffer[buffWrtInx++] = rpm_meas;
    }
    if( buffWrtInx >= Buffersize )
    	led_g_on();
    if(motor_get_status() == MOTOR_STATUS_AUTO_PID)
    {
        pwm_set_raw(pwmValue);        
    }
    else
    {
		esum = 0;
		return;
	}

    return;
}
