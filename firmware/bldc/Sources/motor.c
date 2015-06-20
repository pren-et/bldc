/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file  motor.c
 * \brief Motor control
 * \author pren-et
 *
 */

#include "motor.h"

motor_mode_t    mode            = MOTOR_MODE_OFF;
motor_status_t  motor_status    = MOTOR_STATUS_OFF;
uint16_t force_interval;
uint8_t motor_timeout;
uint8_t restart_cnt;

void motor_init(void) {
    mode            = MOTOR_MODE_OFF;
    motor_status    = MOTOR_STATUS_OFF;
    force_interval  = 5000;
    motor_timeout   = 0;
    pwm_set_100(PWM_100_FORCED);
}

motor_mode_t motor_get_mode(void) {
    return mode;
}

void motor_set_mode(motor_mode_t m) {
	if ((m == MOTOR_MODE_RUN_FREE && mode != MOTOR_MODE_RUN_FREE) || 
			(m == MOTOR_MODE_RUN_PID && mode != MOTOR_MODE_RUN_PID)) {
		pwm_set_100(PWM_100_FORCED);
	}
    else if (m == MOTOR_MODE_SOUND && mode != MOTOR_MODE_SOUND) {
        pwm_set_100(PWM_100_SOUND);
        sound_start();
    }
    mode = m;
    motor_task();
}

motor_status_t motor_get_status(void) {
    return motor_status;
}

uint16_t motor_get_force_interval(void) {
    return force_interval;
}

void motor_task(void) {
    static motor_mode_t prev_mode = MOTOR_MODE_OFF;
    switch (mode) {
        case MOTOR_MODE_OFF:
            commutate_state(COMM_STATE_OFF);
            motor_status = MOTOR_STATUS_OFF;
            break;
        case MOTOR_MODE_BRAKE:
            commutate_state(COMM_STATE_BRAKE);
            motor_status = MOTOR_STATUS_BRAKE;
            break;
        case MOTOR_MODE_RUN_FREE:
            if ((prev_mode != MOTOR_MODE_RUN_FREE) && (prev_mode != MOTOR_MODE_RUN_PID)) {
                /* initiate motor startup, if motor not previously running */
                force_interval = 5000;
                commutate_state(COMM_STATE_FORCED_0);
                pwm_set_100(PWM_100_FORCED);
                motor_status = MOTOR_STATUS_FORCED;
                motor_timeout = 0;
                restart_cnt = 0;
            }
            if (prev_mode == MOTOR_MODE_RUN_PID) {
            	motor_status = MOTOR_STATUS_AUTO_FREE;
            }
            if (motor_status == MOTOR_STATUS_FORCED) {
                if (force_interval > 10000) {
                    force_interval -= 200;
                }
                else if (force_interval > 5000) {
                    force_interval -= 100;
                }
                else if (force_interval > 2000) {
                    force_interval -= 100;
                }
                else if (force_interval > 1000) {
                    force_interval -= 50;
                }
                else if (force_interval > 500) {
                    if (force_interval == 600) {
              //          pwm_set_100(77);
                    }
                    force_interval -= 25;
                }
                //else if (force_interval > 300) {
                //    force_interval -= 10;
                //}
                else {
                    /* Final speed for forced commutation reached */
//                    led_g_on();
                    pwm_set_100(PWM_100_RUN);
                    motor_status = MOTOR_STATUS_AUTO_FREE;
                    motor_timeout = 0;
                }
            }
            break;
        case MOTOR_MODE_RUN_PID:
            motor_status = MOTOR_STATUS_AUTO_PID;
            break;
        case MOTOR_MODE_SOUND:
            if (prev_mode != MOTOR_MODE_SOUND) {
                commutate_state(COMM_STATE_SOUND_0);
            }
            motor_status = MOTOR_STATUS_SOUND;
            break;
        default:
            commutate_state(COMM_STATE_OFF);
            break;
    }
    prev_mode = mode;
}

void motor_timeout_reset(void) {
    motor_timeout = 0;
}

void motor_task_timeout(void) {
    if ((mode == MOTOR_MODE_RUN_FREE) || (mode == MOTOR_MODE_RUN_PID)) {
        if (motor_timeout >= TIMEOUT_THRESHOLD) {
            if (restart_cnt < RESTART_THRESHOLD) {
                /* initiate motor startup */
                motor_set_mode(MOTOR_MODE_BRAKE);
                motor_set_mode(MOTOR_MODE_RUN_FREE);
                motor_timeout = 0;
                restart_cnt++;
            }
            else {
                motor_set_mode(MOTOR_MODE_BRAKE);
            }
        }
        else {
            motor_timeout++;
        }
    }
}
