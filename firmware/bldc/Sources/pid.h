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
#include "motor.h"

#define TASK_PID            10    /* Period for PID task */
typedef union {
    struct {
        uint8_t high;   /*!< High byte */
        uint8_t low;    /*!< Low byte */
    } bytefield;        /*!< Nibbles */
    uint16_t value;     /*!< Byte */
} speed_t;

void pid_init(void);

void pid_set_rpm_high(uint8_t sp);
void pid_set_rpm_low(uint8_t sp);
void pid_set_rpm(uint16_t sp);
void pid_start_Measurement(void);
uint8_t pid_get_rpm_high(void);
uint8_t pid_get_rpm_low(void);
uint16_t pid_get_rpm(void);

/* \fn void pid_task(void)
 * \brief task to perform pid control
 *
 * \return void
 */
void pid_task(void);

#endif /* PID_H_ */
