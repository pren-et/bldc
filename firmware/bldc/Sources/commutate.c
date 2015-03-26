/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file  interrupts.c
 * \brief Motor commutation
 * \author pren-et
 * 
 */

#include "commutate.h"

comm_state_t state;

void commutate_init(void) {
    state = COMM_STATE_OFF;
}

void commutate(void) {
    switch (state) {
        case COMM_STATE_OFF:
            PTADD = 0xFF;
            break;
        case COMM_STATE_BRAKE:
            PTADD = FET_H_U | FET_H_V | FET_H_W;
            break;
        case COMM_STATE_0:
            PTADD = ~(FET_L_V | FET_H_U);
            break;
        case COMM_STATE_1:
            PTADD = ~(FET_L_W | FET_H_U);
            break;
        case COMM_STATE_2:
            PTADD = ~(FET_L_W | FET_H_V);
            break;
        case COMM_STATE_3:
            PTADD = ~(FET_L_U | FET_H_V);
            break;
        case COMM_STATE_4:
            PTADD = ~(FET_L_U | FET_H_W);
            break;
        case COMM_STATE_5:
            PTADD = ~(FET_L_V | FET_H_W);
            break;
        default:
            PTADD = 0xFF;
            break;
    }
}

void commutate_state(comm_state_t n_state) {
    state = n_state;
    commutate();
}

void commutate_next(void) {
    switch (state) {
        case COMM_STATE_OFF:
            state = COMM_STATE_OFF;
            break;
        case COMM_STATE_BRAKE:
            state = COMM_STATE_BRAKE;
            break;
        case COMM_STATE_0:
            state = COMM_STATE_1;
            break;
        case COMM_STATE_1:
            state = COMM_STATE_2;
            break;
        case COMM_STATE_2:
            state = COMM_STATE_3;
            break;
        case COMM_STATE_3:
            state = COMM_STATE_4;
            break;
        case COMM_STATE_4:
            state = COMM_STATE_5;
            break;
        case COMM_STATE_5:
            state = COMM_STATE_0;
            break;
        default:
            break;
    }
    commutate();
}
