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
    COMM_STATE_FORCED_0,    /*!< Commutation position 0 with forced commutation */
    COMM_STATE_FORCED_1,    /*!< Commutation position 1 with forced commutation */
    COMM_STATE_FORCED_2,    /*!< Commutation position 2 with forced commutation */
    COMM_STATE_FORCED_3,    /*!< Commutation position 3 with forced commutation */
    COMM_STATE_FORCED_4,    /*!< Commutation position 4 with forced commutation */
    COMM_STATE_FORCED_5,    /*!< Commutation position 5 with forced commutation */
    COMM_STATE_AUTO_0,      /*!< Commutation position 0 with auto commutation */
    COMM_STATE_AUTO_1,      /*!< Commutation position 1 with auto commutation */
    COMM_STATE_AUTO_2,      /*!< Commutation position 2 with auto commutation */
    COMM_STATE_AUTO_3,      /*!< Commutation position 3 with auto commutation */
    COMM_STATE_AUTO_4,      /*!< Commutation position 4 with auto commutation */
    COMM_STATE_AUTO_5,      /*!< Commutation position 5 with auto commutation */
} comm_state_t;

/*! \name comm_out
 * @{
 */
#define COMM_OUT_STATE_OFF      (0xFF)                              /*!< Bridge off */
#define COMM_OUT_STATE_BRAKE    (~(FET_L_U | FET_L_V | FET_L_W))    /*!< U, V, W low */
#define COMM_OUT_STATE_FORCED_0 (~(FET_L_V | FET_H_U))              /*!< U high, V low , W open */
#define COMM_OUT_STATE_FORCED_1 (~(FET_L_W | FET_H_U))              /*!< U high, V open, W low  */
#define COMM_OUT_STATE_FORCED_2 (~(FET_L_W | FET_H_V))              /*!< U open, V high, W low  */
#define COMM_OUT_STATE_FORCED_3 (~(FET_L_U | FET_H_V))              /*!< U low , V high, W open */
#define COMM_OUT_STATE_FORCED_4 (~(FET_L_U | FET_H_W))              /*!< U low , V open, W high */
#define COMM_OUT_STATE_FORCED_5 (~(FET_L_V | FET_H_W))              /*!< U open, V low , W high */
#define COMM_OUT_STATE_AUTO_0   (~(FET_L_V | FET_H_U))              /*!< U high, V low , W open */
#define COMM_OUT_STATE_AUTO_1   (~(FET_L_W | FET_H_U))              /*!< U high, V open, W low  */
#define COMM_OUT_STATE_AUTO_2   (~(FET_L_W | FET_H_V))              /*!< U open, V high, W low  */
#define COMM_OUT_STATE_AUTO_3   (~(FET_L_U | FET_H_V))              /*!< U low , V high, W open */
#define COMM_OUT_STATE_AUTO_4   (~(FET_L_U | FET_H_W))              /*!< U low , V open, W high */
#define COMM_OUT_STATE_AUTO_5   (~(FET_L_V | FET_H_W))              /*!< U open, V low , W high */
#define COMM_OUT_STATE_DEFAULT  (0xFF)                              /*!< Bridge off */
/*! @} */

/*! \name comm_next
 * @{
 */
#define COMM_NEXT_STATE_OFF         COMM_STATE_OFF          /*!< COMM_STATE_OFF             -> COMM_STATE_OFF       */
#define COMM_NEXT_STATE_BRAKE       COMM_STATE_BRAKE        /*!< COMM_STATE_BRAKE           -> COMM_STATE_BRAKE     */
#define COMM_NEXT_STATE_FORCED_0    COMM_STATE_FORCED_1     /*!< COMM_STATE_STATE_FORCED_0  -> COMM_STATE_FORCED_1  */
#define COMM_NEXT_STATE_FORCED_1    COMM_STATE_FORCED_2     /*!< COMM_STATE_STATE_FORCED_1  -> COMM_STATE_FORCED_2  */
#define COMM_NEXT_STATE_FORCED_2    COMM_STATE_FORCED_3     /*!< COMM_STATE_STATE_FORCED_2  -> COMM_STATE_FORCED_3  */
#define COMM_NEXT_STATE_FORCED_3    COMM_STATE_FORCED_4     /*!< COMM_STATE_STATE_FORCED_3  -> COMM_STATE_FORCED_4  */
#define COMM_NEXT_STATE_FORCED_4    COMM_STATE_FORCED_5     /*!< COMM_STATE_STATE_FORCED_4  -> COMM_STATE_FORCED_5  */
#define COMM_NEXT_STATE_FORCED_5    COMM_STATE_FORCED_0     /*!< COMM_STATE_STATE_FORCED_5  -> COMM_STATE_FORCED_0  */
#define COMM_NEXT_STATE_AUTO_0      COMM_STATE_AUTO_1       /*!< COMM_STATE_STATE_AUTO_0    -> COMM_STATE_AUTO_1    */
#define COMM_NEXT_STATE_AUTO_1      COMM_STATE_AUTO_2       /*!< COMM_STATE_STATE_AUTO_1    -> COMM_STATE_AUTO_2    */
#define COMM_NEXT_STATE_AUTO_2      COMM_STATE_AUTO_3       /*!< COMM_STATE_STATE_AUTO_2    -> COMM_STATE_AUTO_3    */
#define COMM_NEXT_STATE_AUTO_3      COMM_STATE_AUTO_4       /*!< COMM_STATE_STATE_AUTO_3    -> COMM_STATE_AUTO_4    */
#define COMM_NEXT_STATE_AUTO_4      COMM_STATE_AUTO_5       /*!< COMM_STATE_STATE_AUTO_4    -> COMM_STATE_AUTO_5    */
#define COMM_NEXT_STATE_AUTO_5      COMM_STATE_AUTO_0       /*!< COMM_STATE_STATE_AUTO_5    -> COMM_STATE_AUTO_0    */
#define COMM_NEXT_STATE_DEFAULT     COMM_STATE_OFF          /*!< COMM_STATE_DEFAULT         -> COMM_STATE_OFF       */
/*! @} */

/*! \fn void commutate_init(void)
 *  \brief Initialisation of commutator
 *
 *  \return void
 */
void commutate_init(void);

/*! \fn void commutate(void)
 *  \brief Perform commutation
 *
 *  \return void
 */
void commutate(void);

/*! \fn void commutate_init(void)
 *  \brief Set commutator state
 *
 *  \return void
 */
void commutate_state(comm_state_t n_state);

/*! \fn void commutate_init(void)
 *  \brief set commutator state to next state and perform commutation
 *
 *  \return void
 */
void commutate_next(void);

#endif /* COMMUTATE_H_ */
