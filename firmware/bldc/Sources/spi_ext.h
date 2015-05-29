/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file spi_ext.h
 * \brief SPI interface to DRV8301
 * \author pren-et
 *
 */

#ifndef SPI_EXT_H_
#define SPI_EXT_H_

#include "platform.h"
#include "hardware.h"

#define CMD_DUMMY		       0x01
#define CMD_START              0x10
#define CMD_STOP               0x20
#define CMD_SET_RPM		       0x32
#define CMD_SET_VOLATGE        0x42
#define CMD_SET_CURRENT        0x51
#define CMD_GET_STATUS         0x64
#define CMD_ARE_YOU_ALIVE      0x71
#define CMD_SET_PWM            0x81
#define CMD_PLAY_SOUND         0x91
#define CMD_MEASUREMENT_PARAM  0xC0
#define CMD_MEASUREMENT        0xD0

#define I_AM_ALIVE			   0x55


void spi_ext_init(void);


#endif /* SPI_EXT_H_ */
