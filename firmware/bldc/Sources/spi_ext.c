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
#include "motor.h"
#include "hardware.h"


void (*spi_ext_irq) (void);

void ReceiveCmd(void);
void receiveRpmHigh(void);
void receiveRpmLow(void);
void setVoltage(void);
void setCurrent(void);
void sendRunningState(void);
void sendErrorCode(void);
void sendRpmHigh(void);
void sendRpmLow(void);
void getVoltage(void);
void getCurrent(void);
void sendIamAlive(void);


void spi_ext_init(void)
{
    #pragma MESSAGE DISABLE C4002        /* Disable warning C4002 "Result not used" */
    (void)SPI1S;                         /* Read the status register */
    (void)SPI1D16;                       /* Read the data register */
    /* SPI1C2: SPMIE=0,SPIMODE=0,??=0,MODFEN=0,BIDIROE=0,??=0,SPISWAI=0,SPC0=0 */
    SPI1C2 = (uint8_t) 0x00U;           /* Configure the SPI port - control register 2 */
    /* SPI1C1: SPIE=1,SPE=1,SPTIE=1,MSTR=0,CPOL=0,CPHA=1,SSOE=0,LSBFE=1 */
    SPI1C1 = (uint8_t) 0xE5U;          /*  Configure the SPI port - control register 1 */
    spi_ext_irq = &ReceiveCmd;
}

/* main interrupt function */
void ReceiveCmd(void)
{
    (void) SPI1S;
    switch (SPI1DL & 0xFF)
    {
    case 0x10:
        /* Start byte received */
    	motor_set_mode(MOTOR_MODE_RUN_FREE);
        break;
    case 0x20:
        /* Stop byte received */
    	motor_set_mode(MOTOR_MODE_BRAKE);
        break;
    case 0x32:
        /* set RPM */
        spi_ext_irq = &receiveRpmHigh;
        break;
    case 0x41:
        /* set voltage */
    	spi_ext_irq = &setVoltage;
        break;
    case 0x51:
        /* set current */
    	spi_ext_irq = &sendRpmHigh;
        break;
    case 0x64:
        /* return status */
        spi_ext_irq = &sendRunningState;
        break;
    case 0x71:
    	/* Are you alive received */
        spi_ext_irq = &sendIamAlive;
        break;
    case 0xC0:
    	/* Start measurement with parameter */
        break;
    case 0xD0:
    	/* Start measurement (step-answer) */
    	motor_set_mode(MOTOR_MODE_RUN_FREE);
        break;
    case 0xE0:
    	/* get measurement */
        break;
    }
}

void receiveRpmHigh(void)
{
    /* Set new speed */
    spi_ext_irq = &receiveRpmLow;
    (void) SPI1S;
    //serRpm(SPI1DL);
}

void receiveRpmLow(void)
{
    /* Set new speed */
    spi_ext_irq = &ReceiveCmd;
    (void) SPI1S;
    //serRpm(SPI1DL);
}

void setVoltage(void)
{
    (void) SPI1S;
    setVoltage_to_DRV(SPI1DL);
    spi_ext_irq = &ReceiveCmd;
}

void setCurrent(void)
{
    (void) SPI1S;
    setCurrent_to_DRV(SPI1DL);
    spi_ext_irq = &ReceiveCmd;
}

void sendRunningState(void)
{
    /* Dummy byte received, send running state */
    spi_ext_irq = &sendErrorCode;
    (void) SPI1S;
    SPI1DL = (char)motor_get_mode();
}

void sendErrorCode(void)
{
    /* Dummy byte received, send running state */
    spi_ext_irq = &sendRpmHigh;
    (void) SPI1S;
    SPI1DL = getErrors_form_DRV();
}

void sendRpmHigh(void)
{
    /* return current set speed */
    spi_ext_irq = &sendRpmLow;
    (void) SPI1S;
    //SPI1DL = getSpeed();
}

void sendRpmLow(void)
{
    /* return current set speed */
    spi_ext_irq = &ReceiveCmd;
    (void) SPI1S;
    //SPI1DL = getSpeed();
}

void sendIamAlive(void)
{
    /* return I am alive */
    spi_ext_irq = &ReceiveCmd;
    (void) SPI1S;
    SPI1DL = 0x55;
}
