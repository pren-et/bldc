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

motor_mode_t mode;
extern uint16_t forced_interval;

void motor_init(void) {
    mode = MOTOR_MODE_OFF;
}

motor_mode_t motor_get_mode(void) {
    return mode;
}

void motor_set_mode(motor_mode_t m) {
    motor_mode_t prev_mode;
    prev_mode = mode;
    mode = m;
    if (mode != prev_mode) {
        /*! \todo set commutation state according to new mode */
        if (prev_mode == MOTOR_MODE_OFF | prev_mode == MOTOR_MODE_BRAKE) { /* Motor previously not running */
            if (mode == MOTOR_MODE_RUN_FREE | mode == MOTOR_MODE_RUN_PID) { /* Motor now running */
                /*! \todo initiate motor startup
                    - Check current speed
                    - if speed is high enough, start with auto commutation
                    - if speed is too slow, restart with forced commutation
                */
                forced_interval = 5000;
                commutate_state(COMM_STATE_FORCED_0);
                TPM2C0V = 512;
            }
        }
        else if(prev_mode == MOTOR_MODE_RUN_FREE | prev_mode == MOTOR_MODE_RUN_PID) { /* Motor previously running */
            if (mode == MOTOR_MODE_OFF) {
                commutate_state(COMM_STATE_OFF);
            }
            else if (mode == MOTOR_MODE_BRAKE) {
                commutate_state(COMM_STATE_BRAKE);
            }
        }
        else { /* Unused state */
        }
    }
}
