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
            PTADD = COMM_OUT_STATE_OFF;
            break;
        case COMM_STATE_BRAKE:
            PTADD = COMM_OUT_STATE_BRAKE;
            break;
        case COMM_STATE_FORCED_0:
            PTADD = COMM_OUT_STATE_FORCED_0;
            break;
        case COMM_STATE_FORCED_1:
            PTADD = COMM_OUT_STATE_FORCED_1;
            break;
        case COMM_STATE_FORCED_2:
            PTADD = COMM_OUT_STATE_FORCED_2;
            break;
        case COMM_STATE_FORCED_3:
            PTADD = COMM_OUT_STATE_FORCED_3;
            break;
        case COMM_STATE_FORCED_4:
            PTADD = COMM_OUT_STATE_FORCED_4;
            break;
        case COMM_STATE_FORCED_5:
            PTADD = COMM_OUT_STATE_FORCED_5;
            break;
        case COMM_STATE_AUTO_0:
            PTADD = COMM_OUT_STATE_AUTO_0;
            break;
        case COMM_STATE_AUTO_1:
            PTADD = COMM_OUT_STATE_AUTO_1;
            break;
        case COMM_STATE_AUTO_2:
            PTADD = COMM_OUT_STATE_AUTO_2;
            break;
        case COMM_STATE_AUTO_3:
            PTADD = COMM_OUT_STATE_AUTO_3;
            break;
        case COMM_STATE_AUTO_4:
            PTADD = COMM_OUT_STATE_AUTO_4;
            break;
        case COMM_STATE_AUTO_5:
            PTADD = COMM_OUT_STATE_AUTO_5;
            break;
        default:
            PTADD = COMM_OUT_STATE_DEFAULT;
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
            state = COMM_NEXT_STATE_OFF;
            PTADD = COMM_OUT_STATE_OFF;
            break;
        case COMM_STATE_BRAKE:
            state = COMM_NEXT_STATE_BRAKE;
            PTADD = COMM_OUT_STATE_BRAKE;
            break;
        case COMM_STATE_FORCED_0:
            state = COMM_NEXT_STATE_FORCED_0;
            PTADD = COMM_OUT_STATE_FORCED_0;
            break;
        case COMM_STATE_FORCED_1:
            state = COMM_NEXT_STATE_FORCED_1;
            PTADD = COMM_OUT_STATE_FORCED_1;
            break;
        case COMM_STATE_FORCED_2:
            state = COMM_NEXT_STATE_FORCED_2;
            PTADD = COMM_OUT_STATE_FORCED_2;
            break;
        case COMM_STATE_FORCED_3:
            state = COMM_NEXT_STATE_FORCED_3;
            PTADD = COMM_OUT_STATE_FORCED_3;
            break;
        case COMM_STATE_FORCED_4:
            state = COMM_NEXT_STATE_FORCED_4;
            PTADD = COMM_OUT_STATE_FORCED_4;
            break;
        case COMM_STATE_FORCED_5:
            state = COMM_NEXT_STATE_FORCED_5;
            PTADD = COMM_OUT_STATE_FORCED_5;
            break;
        case COMM_STATE_AUTO_0:
            state = COMM_NEXT_STATE_AUTO_0;
            PTADD = COMM_OUT_STATE_AUTO_0;
            break;
        case COMM_STATE_AUTO_1:
            state = COMM_NEXT_STATE_AUTO_1;
            PTADD = COMM_OUT_STATE_AUTO_1;
            break;
        case COMM_STATE_AUTO_2:
            state = COMM_NEXT_STATE_AUTO_2;
            PTADD = COMM_OUT_STATE_AUTO_2;
            break;
        case COMM_STATE_AUTO_3:
            state = COMM_NEXT_STATE_AUTO_3;
            PTADD = COMM_OUT_STATE_AUTO_3;
            break;
        case COMM_STATE_AUTO_4:
            state = COMM_NEXT_STATE_AUTO_4;
            PTADD = COMM_OUT_STATE_AUTO_4;
            break;
        case COMM_STATE_AUTO_5:
            state = COMM_NEXT_STATE_AUTO_5;
            PTADD = COMM_OUT_STATE_AUTO_5;
            break;
        default:
            state = COMM_NEXT_STATE_DEFAULT;
            PTADD = COMM_OUT_STATE_DEFAULT;
            break;
    }
}
