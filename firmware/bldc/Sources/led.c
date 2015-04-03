/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file  led.c
 * \brief
 * \author pren-et
 *
 */

#include "led.h"

void led_r_on(void) {
    PTDD &= ~(LED_R);   /* red LED on */
}

void led_r_off(void) {
    PTDD |= LED_R;      /* red LED off */
}

void led_r_toggle(void) {
    PTDD ^= LED_R;      /* red LED toggle */
}

void led_g_on(void) {
    PTDD &= ~(LED_G);   /* green LED on */
}

void led_g_off(void) {
    PTDD |= LED_G;      /* green LED off */
}

void led_g_toggle(void) {
    PTDD ^= LED_G;      /* green LED toggle */
}

void led_y_on(void) {
    PTDD &= ~(LED_Y);   /* yellow LED on */
}

void led_y_off(void) {
    PTDD |= LED_Y;      /* yellow LED off */
}

void led_y_toggle(void) {
    PTDD ^= LED_Y;      /* yellow LED toggle */
}

