/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file  pwm.h
 * \brief
 * \author pren-et
 *
 */

#ifndef PWM_H_
#define PWM_H_

#include "platform.h"
#include "hardware.h"

#define PWM_WIDTH 10

/*! \fn uint8_t pwm_get_8(void)
 *  \brief read pwm with 8 bit resolution
 *
 *  \return pwm
 */
uint8_t pwm_get_8(void);

/*! \fn uint16_t pwm_get_16(void)
 *  \brief read pwm with 16 bit resolution
 *
 *  \return pwm
 */
uint16_t pwm_get_16(void);

/*! \fn uint16_t pwm_get_100(void)
 *  \brief read pwm in percent
 *
 *  \return pwm
 */
uint8_t pwm_get_100(void);

/*! \fn uint16_t pwm_get_raw(void)
 *  \brief read pwm raw value
 *
 *  \return pwm
 */
uint16_t pwm_get_raw(void);

/*! \fn void pwm_get_8(uint8_t pwm)
 *  \brief set pwm with 8 bit resolution
 *
 *  \param  pwm ratio with 8 bit resolution
 *  \return void
 */
void pwm_set_8(uint8_t pwm);

/*! \fn void pwm_get_16(uint16_t pwm)
 *  \brief set pwm with 16 bit resolution
 *
 *  \param  pwm ratio with 16 bit resolution
 *  \return void
 */
void pwm_set_16(uint16_t pwm);

/*! \fn void pwm_get_100(uint8_t pwm)
 *  \brief set pwm in percent
 *
 *  \param  pwm ratio in percent
 *  \return void
 */
void pwm_set_100(uint8_t pwm);

/*! \fn void pwm_get_raw(uint16_t pwm)
 *  \brief set pwm raw value
 *
 *  \param  pwm ratio raw value
 *  \return void
 */
void pwm_set_raw(uint16_t pwm);

#endif /* PWM_H_ */
