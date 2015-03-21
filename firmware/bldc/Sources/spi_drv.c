#include "spi_drv.h"

 
 word spi_drv_read_write(word data)
 {
	 (void) SPI2S;
	 SPI2D16 = data;                       /* Store char to transmitter register */
	 while((SPI2S_SPTEF)== 0);
	 return SPI2D16;
 }
 

/*
** ===================================================================
**     Method      :  initSpiAsMaster (component SynchroMaster)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void Spi_drv_init(void)
{
	#pragma MESSAGE DISABLE C4002        /* Disable warning C4002 "Result not used" */
	(void)SPI2S;                         /* Read the status register */
	(void)SPI2D16;                       /* Read the data register */
	/* SPI2BR: ??=0,SPPR2=0,SPPR1=1,SPPR0=0,??=0,SPR2=0,SPR1=1,SPR0=0 */
	SPI2BR = (byte) 0x22U;               /* Set the baud rate register */ 
	/* SPI2C2: SPMIE=0,SPIMODE=1,??=0,MODFEN=1,BIDIROE=0,??=0,SPISWAI=0,SPC0=0 */
	SPI2C2 = (byte)  0x50U;              /* Configure the SPI port - control register 2 */ 
	/* SPI2C1: SPIE=0,SPE=0,SPTIE=0,MSTR=1,CPOL=0,CPHA=1,SSOE=1,LSBFE=0 */
	SPI2C1 = (byte) 0x16U;               /* Configure the SPI port - control register 1 */ 
	SPI2C1_SPE = 1U;                     /* Enable device */
}
