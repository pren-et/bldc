/*
 * pid.c
 *
 *  Created on: Apr 7, 2015
 *      Author: studer.yves
 */

#include "pid.h"

typedef union 
{
    struct
    {
        uint8_t high;   /*!< High byte */
        uint8_t low;    /*!< Low byte */
    } bytefield;        /*!< Nibbles */
    uint16_t value;     /*!< Byte */
} speed_t;
static speed_t speed;

void init_pid(void)
{
	speed.value = 0xD173;
}

void set_prm_high(uint8_t sp)
{
	speed.bytefield.high = sp;
}

void set_prm_low(uint8_t sp)
{
	speed.bytefield.low = sp;
}

uint8_t get_prm_High(void)
{
	return speed.bytefield.high;
}

uint8_t get_prm_low(void)
{
	return speed.bytefield.low;
}
