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
extern uint16_t force_interval;
extern uint8_t  force_flag;

void motor_init(void) {
    mode            = MOTOR_MODE_OFF;
    motor_status    = MOTOR_STATUS_OFF;
    force_flag      = 1;
}

motor_mode_t motor_get_mode(void) {
    return mode;
}

void motor_set_mode(motor_mode_t m) {
    mode = m;
}

motor_status_t motor_get_status(void) {
    return motor_status;
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
            if (prev_mode != MOTOR_MODE_RUN_FREE) {
                /* initiate motor startup, if motor not previously running */
                force_interval = 5000;
                commutate_state(COMM_STATE_FORCED_0);
                motor_status = MOTOR_STATUS_FORCED;
            }
            if (motor_status == MOTOR_STATUS_FORCED) {
                if (force_interval > 10000) {
                    force_interval -= 500;
                }
                else if (force_interval > 5000) {
                    force_interval -= 200;
                }
                else if (force_interval > 2000) {
                    force_interval -= 100;
                }
                else if (force_interval > 1000) {
                    force_interval -= 50;
                }
                else if (force_interval > 500) {
                    if (force_interval == 600) {
                        //pwm_set_100(77);
                    }
                    force_interval -= 20;
                }
                //else if (force_interval > 300) {
                //    force_interval -= 10;
                //}
                else {
                    /* Final speed for forced commutation reached */
                    led_g_on();
                    //pwm_set_100(50);
                    force_flag = 0;         /* disable forced commutation, enable autocommutation */
                    status = MOTOR_STATUS_AUTO;
                }
            }
            break;
        case MOTOR_MODE_RUN_PID:
            /* not implemented yet */
            break;
        case MOTOR_MODE_SOUND:
            /* not implemented yet */
            break;
        default:
            commutate_state(COMM_STATE_OFF);
            break;
    }
    prev_mode = mode;
}
