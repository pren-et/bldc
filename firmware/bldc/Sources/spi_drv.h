/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file spi_drv.h
 * \brief SPI interface to DRV8301
 * \author pren-et
 * 
 */

#ifndef SPI_DRV_H_
#define SPI_DRV_H_

#include "platform.h"
#include "hardware.h"
	  
void spi_drv_init(void);
uint16_t spi_drv_read_write(uint16_t);

#endif /* SPI_DRV_H_ */
