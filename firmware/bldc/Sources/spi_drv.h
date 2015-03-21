/*
 * SPI_DRV_H_.h
 *
 *  Created on: Mar 21, 2015
 *      Author: studer.yves
 */

#ifndef SPI_DRV_H_
#define SPI_DRV_H_
#include "platform.h"
#include "hardware.h"
	  
void Spi_drv_init(void);
word spi_drv_read_write(word);

#endif /* SPI_DRV_H_ */
