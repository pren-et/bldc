/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file spi_ext.c
 * \brief SPI interface for extern communication
 * \author pren-et
 * 
 */
#include "spi_ext.h"

void spi_ext_init(void)
{
	  #pragma MESSAGE DISABLE C4002        /* Disable warning C4002 "Result not used" */
	  (void)SPI1S;                         /* Read the status register */
	  (void)SPI1D16;                       /* Read the data register */
	  /* SPI1C2: SPMIE=0,SPIMODE=1,??=0,MODFEN=0,BIDIROE=0,??=0,SPISWAI=0,SPC0=0 */
	  SPI1C2 = (byte) 0x40U;              /* Configure the SPI port - control register 2 */ 
	  /* SPI1C1: SPIE=1,SPE=1,SPTIE=1,MSTR=0,CPOL=0,CPHA=1,SSOE=0,LSBFE=1 */
	  SPI1C1 = (byte) 0xE5U;             /*  Configure the SPI port - control register 1 */ 
}

void spi_ext_irq(void)
{
	
}
