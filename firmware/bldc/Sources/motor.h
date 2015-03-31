/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file  motor.h
 * \brief Motor control
 * \author pren-et
 *
 */
#ifndef MOTOR_H_
#define MOTOR_H_

#include "platform.h"
#include "hardware.h"
#include "commutate.h"

/*! \enum comm_mode_t
 *  \brief Type for controlling the motor operation mode
 */
typedef enum {
    MOTOR_MODE_OFF,             /*!< Motor off */
    MOTOR_MODE_BRAKE,           /*!< Motor braked */
    MOTOR_MODE_RUN_FREE,        /*!< Motor running with pwm control */
    MOTOR_MODE_RUN_PID,         /*!< Motor running with pid controller */
    MOTOR_MODE_SOUND,           /*!< Motor playing sound */
} motor_mode_t;

/*! \fn void motor_init(void)
 *  \brief Initialize motor
 *
 *  \return void
 */
void motor_init(void);

/*! \fn motor_mode_t motor_get_mode(void)
 *  \brief Get motor mode
 *
 *  \return Motor mode
 */
motor_mode_t motor_get_mode(void);

/*! \fn void motor_set_mode(motor_mode_t m)
 *  \brief Set motor mode
 *
 *  \param  m Motor mode
 *  \return void
 */
void motor_set_mode(motor_mode_t m);

#endif /* MOTOR_H_ */
