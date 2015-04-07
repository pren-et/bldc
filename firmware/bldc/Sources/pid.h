/*
 * pid.h
 *
 *  Created on: Apr 7, 2015
 *      Author: studer.yves
 */

#ifndef PID_H_
#define PID_H_

#include "hardware.h"

void init_pid(void);

void set_prm_high(uint8_t sp);
void set_prm_low(uint8_t sp);
uint8_t get_prm_High(void);
uint8_t get_prm_low(void);

#endif /* PID_H_ */
