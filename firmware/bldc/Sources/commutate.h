/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file  commutate.h
 * \brief Motor commutation
 * \author pren-et
 * 
 */
#ifndef COMMUTATE_H_
#define COMMUTATE_H_

#include "platform.h"
#include "hardware.h"

/*! \typedef comm_state_t
 *  \brief Type for commutation state machine
 */
typedef enum {
    COMM_STATE_OFF,         /*!< H Bridge off */
    COMM_STATE_BRAKE,       /*!< Brake Motor */
    COMM_STATE_0,           /*!< Commutation position 0 */
    COMM_STATE_1,           /*!< Commutation position 1 */
    COMM_STATE_2,           /*!< Commutation position 2 */
    COMM_STATE_3,           /*!< Commutation position 3 */
    COMM_STATE_4,           /*!< Commutation position 4 */
    COMM_STATE_5,           /*!< Commutation position 5 */
} comm_state_t;

void commutate_init(void);

void commutate(void);

void commutate_state(comm_state_t n_state);

void commutate_next(void);

#endif /* COMMUTATE_H_ */
