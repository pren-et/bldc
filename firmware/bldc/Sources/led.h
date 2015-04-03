/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file  led.h
 * \brief
 * \author pren-et
 *
 */

#ifndef LED_H_
#define LED_H_

#include "platform.h"
#include "hardware.h"

/*! \fn void led_r_on(void)
 *  \brief turn red led on
 *
 *  \return void
 */
void led_r_on(void);

/*! \fn void led_r_off(void)
 *  \brief turn red led off
 *
 *  \return void
 */
void led_r_off(void);

/*! \fn void led_r_toggle(void)
 *  \brief toggle red led
 *
 *  \return void
 */
void led_r_toggle(void);

/*! \fn void led_g_on(void)
 *  \brief turn green led on
 *
 *  \return void
 */
void led_g_on(void);

/*! \fn void led_g_off(void)
 *  \brief turn green led off
 *
 *  \return void
 */
void led_g_off(void);

/*! \fn void led_g_toggle(void)
 *  \brief toggle green led
 *
 *  \return void
 */
void led_g_toggle(void);

/*! \fn void led_y_on(void)
 *  \brief turn yellow led on
 *
 *  \return void
 */
void led_y_on(void);

/*! \fn void led_y_off(void)
 *  \brief turn yellow led off
 *
 *  \return void
 */
void led_y_off(void);

/*! \fn void led_y_toggle(void)
 *  \brief toggle yellow led
 *
 *  \return void
 */
void led_y_toggle(void);

#endif /* LED_H_ */
