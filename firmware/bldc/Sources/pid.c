/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file  pid.c
 * \brief
 * \author pren-et
 *
 */

#include "pid.h"

typedef union {
    struct {
        uint8_t high;   /*!< High byte */
        uint8_t low;    /*!< Low byte */
    } bytefield;        /*!< Nibbles */
    uint16_t value;     /*!< Byte */
} speed_t;
static speed_t speed;

void pid_init(void) {
	speed.value = 0xD173;
}

void pid_set_rpm_high(uint8_t sp) {
	speed.bytefield.high = sp;
}

void pid_set_rpm_low(uint8_t sp) {
	speed.bytefield.low = sp;
}

void pid_set_rpm(uint16_t sp) {
    speed.value = sp;
}

uint8_t pid_get_rpm_high(void) {
	return speed.bytefield.high;
}

uint8_t pid_get_rpm_low(void) {
	return speed.bytefield.low;
}

uint16_t pid_get_rpm(void) {
    return speed.value;
}
