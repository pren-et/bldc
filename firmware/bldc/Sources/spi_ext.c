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
#include "drv8301.h"


void (*spi_ext_irq) (void);

void ReceiveCmd(void);
void receiveRpm(void);
void sendRunningState(void);
void sendRpm(void);
void getDrvConfig(void);
void setDrvConfig(void);
void iAmAlive(void);


void spi_ext_init(void)
{
	#pragma MESSAGE DISABLE C4002        /* Disable warning C4002 "Result not used" */
	(void)SPI1S;                         /* Read the status register */
	(void)SPI1D16;                       /* Read the data register */
	/* SPI1C2: SPMIE=0,SPIMODE=1,??=0,MODFEN=0,BIDIROE=0,??=0,SPISWAI=0,SPC0=0 */
	SPI1C2 = (uint8_t) 0x40U;           /* Configure the SPI port - control register 2 */ 
	/* SPI1C1: SPIE=1,SPE=1,SPTIE=1,MSTR=0,CPOL=0,CPHA=1,SSOE=0,LSBFE=1 */
	SPI1C1 = (uint8_t) 0xE5U;          /*  Configure the SPI port - control register 1 */
	spi_ext_irq = &ReceiveCmd;
}

void ReceiveCmd(void)
{
	(void) SPI1S;
	switch (SPI1D16 & 0xFF00)
	{
	case 0x1000:
		/* Start byte received */
		break;
	case 0x2000:
		/* Stop byte received */
		break;
	case 0x3100:
		/* Are you alive */
		spi_ext_irq = &iAmAlive;
		break;
	case 0x4100:
		/*Master sets the new speed */
		spi_ext_irq = &receiveRpm;
		break;
	case 0x5200:
		/* Send status */
		spi_ext_irq = &sendRunningState;
		break;
	case 0x6F00:
		/* return measurement */
		spi_ext_irq = &sendRunningState;
		break;
	case 0x7000:
		/* Start measurement by given previous config */
		break;
	case 0x8400:
		/* Start measurement by a new config */
		break;
	case 0x9200:
		spi_ext_irq = &setDrvConfig;
		break;
	case 0xA400:
		spi_ext_irq = &getDrvConfig;
		break;
	}
}

void receiveRpm(void)
{
	/* Set new speed */
	spi_ext_irq = &ReceiveCmd;
	(void) SPI1S;
	//serRpm(SPI1D16);
}

void sendRunningState(void)
{
	/* Dummy byte received, send running state */
	spi_ext_irq = &sendRpm;
	(void) SPI1S;
	//SPI1D16 = getRunningState(); 
}

void sendRpm(void)
{
	/* return current set speed */
	spi_ext_irq = &ReceiveCmd;
	(void) SPI1S;
	//SPI1D16 = getSpeed();	
}

void getDrvConfig(void)
{
	static char tmpaddr = 0;
	(void) SPI1S;
	SPI1D16 = drv8301_get_register(tmpaddr);
	tmpaddr++;
	if( tmpaddr == 4)
	{
		tmpaddr = 0;
		spi_ext_irq = &ReceiveCmd;		
	}
}

void setDrvConfig(void)
{
	static char tmpaddr = 2;
	(void) SPI1S;
	drv8301_set_config(tmpaddr, SPI1D16);
	tmpaddr++;
	if( tmpaddr == 4)
	{
		tmpaddr = 2;
		spi_ext_irq = &ReceiveCmd;		
	}	
}

void iAmAlive(void)
{
	(void) SPI1S;
	SPI1D16 = 0x5555; 
	spi_ext_irq = &ReceiveCmd;	
}
