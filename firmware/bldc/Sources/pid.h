/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file  pid.h
 * \brief
 * \author pren-et
 *
 */

#ifndef PID_H_
#define PID_H_

#include "hardware.h"

void pid_init(void);

void pid_set_rpm_high(uint8_t sp);
void pid_set_rpm_low(uint8_t sp);
void pid_set_rpm(uint16_t sp);
uint8_t pid_get_rpm_high(void);
uint8_t pid_get_rpm_low(void);
uint16_t pid_get_rpm(void);

#endif /* PID_H_ */
