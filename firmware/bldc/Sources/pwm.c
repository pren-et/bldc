/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file  pwm.c
 * \brief
 * \author pren-et
 *
 */

#include "pwm.h"

uint8_t pwm_get_8(void) {
    return (uint8_t)(TPM2C0V >> (PWM_WIDTH - 8));
}

uint16_t pwm_get_16(void) {
    return (TPM2C0V << (16 - PWM_WIDTH));
}

uint8_t pwm_get_100(void) {
    return ((uint8_t) (((uint32_t) TPM2C0V) * 100 / TPM2MOD));
}

uint16_t pwm_get_raw(void) {
    return TPM2C0V;
}

void pwm_set_8(uint8_t pwm) {
    TPM2C0V = pwm << (PWM_WIDTH - 8);
    return;
}

void pwm_set_16(uint16_t pwm) {
    TPM2C0V = pwm >> (16 - PWM_WIDTH);
    return;
}

void pwm_set_100(uint8_t pwm) {
    TPM2C0V = ((uint16_t) (((uint32_t) pwm) * TPM2MOD / 100));
    return;
}

void pwm_set_raw(uint16_t pwm) {
    TPM2C0V = pwm;
    return;
}
