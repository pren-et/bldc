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
#include "led.h"
#include "pwm.h"
#include "commutate.h"
#include "sound.h"
#include "team.h"

#define TIMEOUT_THRESHOLD 20
#define RESTART_THRESHOLD 3

#if TEAM == 32
    #define PWM_100_FORCED  75
    #define PWM_100_RUN     75
    #define PWM_100_SOUND   50
#elif TEAM == 27
    #define PWM_100_FORCED  75
    #define PWM_100_RUN     75
    #define PWM_100_SOUND   60
#else
    #define PWM_100_FORCED  75
    #define PWM_100_RUN     25
    #define PWM_100_SOUND   25
#endif /* TEAM */

/*! \enum motor_mode_t
 *  \brief Type for controlling the motor operation mode
 */
typedef enum {
    MOTOR_MODE_OFF,             /*!< Motor off */
    MOTOR_MODE_BRAKE,           /*!< Motor braked */
    MOTOR_MODE_RUN_FREE,        /*!< Motor running with pwm control */
    MOTOR_MODE_RUN_PID,         /*!< Motor running with pid controller */
    MOTOR_MODE_SOUND,           /*!< Motor playing sound */
} motor_mode_t;

/*! \enum motor_status_t
 *  \brief Type for controlling the motor status
 */
typedef enum {
    MOTOR_STATUS_OFF,           /*!< Motor off */
    MOTOR_STATUS_BRAKE,         /*!< Motor braked */
    MOTOR_STATUS_FORCED,        /*!< Motor running with forced commutation */
    MOTOR_STATUS_AUTO_FREE,     /*!< Motor running with auto commutation */
    MOTOR_STATUS_AUTO_PID,      /*!< Motor running with auto commutation and PID speed control */
    MOTOR_STATUS_SOUND,         /*!< Motor playing sound */
} motor_status_t;

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

/*! \fn motor_status_t motor_get_status(void)
 *  \brief Get motor status
 *
 *  \return Motor status
 */
motor_status_t motor_get_status(void);

/*! \fn uint16_t motor_get_force_interval(void)
 *  \brief Get forced commutation interval
 *
 *  \return forced commutation interval
 */
uint16_t motor_get_force_interval(void);

/*! \fn void motor_task(void)
 *  \brief task for motor control
 *
 *  \return void
 */
void motor_task(void);

/*! \fn void motor_timeout_reset(void)
 *  \brief reset timeout counter
 *
 *  \return void
 */
void motor_timeout_reset(void);

/*! \fn void motor_task_timeout(void)
 *  \brief task to control timeout for protecting motor windings from overheating
 *
 *  \return void
 */
void motor_task_timeout(void);

#endif /* MOTOR_H_ */
