/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file spi_drv.c
 * \brief SPI interface to DRV8301
 * \author pren-et
 * 
 */

#include "spi_drv.h"

void spi_drv_init(void) {
    #pragma MESSAGE DISABLE C4002        /* Disable warning C4002 "Result not used" */
    (void)SPI2S;                         /* Read the status register */
    (void)SPI2D16;                       /* Read the data register */
    /* SPI2BR: ??=0,SPPR2=0,SPPR1=1,SPPR0=0,??=0,SPR2=0,SPR1=1,SPR0=0 */
    SPI2BR = (uint8_t) 0x22U;            /* Set the baud rate register */ 
    /* SPI2C2: SPMIE=0,SPIMODE=1,??=0,MODFEN=1,BIDIROE=0,??=0,SPISWAI=0,SPC0=0 */
    SPI2C2 = (uint8_t)  0x50U;           /* Configure the SPI port - control register 2 */ 
    /* SPI2C1: SPIE=0,SPE=0,SPTIE=0,MSTR=1,CPOL=0,CPHA=1,SSOE=1,LSBFE=0 */
    SPI2C1 = (uint8_t) 0x16U;            /* Configure the SPI port - control register 1 */ 
    SPI2C1_SPE = 1U;                     /* Enable device */
}

uint16_t spi_drv_read_write(uint16_t data) {
	uint16_t tmp;
    DisableInterrupts;
    (void) SPI2S;
    SPI2D16 = data;                      /* Store char to transmitter register */
    while(!SPI2S_SPTEF);    			 /* Warten bis gesendet wurde */
    while(!SPI2S_SPRF);		    	     /* Warten bis ein Byte empfangen wurde */
    tmp =  SPI2D16;
    EnableInterrupts;
    return tmp;
}
