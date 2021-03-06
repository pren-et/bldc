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

uint8_t led_load_var = 0;

void led_r_on(void) {
    PTDD &= ~(LED_R);   /* red LED on */
    return;
}

void led_r_off(void) {
    PTDD |= LED_R;      /* red LED off */
    return;
}

void led_r_toggle(void) {
    PTDD ^= LED_R;      /* red LED toggle */
    return;
}

void led_g_on(void) {
    PTDD &= ~(LED_G);   /* green LED on */
    return;
}

void led_g_off(void) {
    PTDD |= LED_G;      /* green LED off */
    return;
}

void led_g_toggle(void) {
    PTDD ^= LED_G;      /* green LED toggle */
    return;
}

void led_y_on(void) {
    PTDD &= ~(LED_Y);   /* yellow LED on */
    return;
}

void led_y_off(void) {
    PTDD |= LED_Y;      /* yellow LED off */
    return;
}

void led_y_toggle(void) {
    PTDD ^= LED_Y;      /* yellow LED toggle */
    return;
}

void led_load_on(void) {
    led_load_var++;
    PTDD &= ~(LED_LOAD_MASK);   /* semaphore LED on */
    return;
}

void led_load_off(void) {
    if (led_load_var <= 1) {
        led_load_var--;
        PTDD |= LED_LOAD_MASK;  /* semaphore LED off */
    }
    return;
}
