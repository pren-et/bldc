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
#include "pid.h"
#include "hardware.h"


volatile void (*spi_ext_irq) (void);

void ReceiveCmd(void);
void receiveRpmHigh(void);
void receiveRpmLow(void);
void setVoltage(void);
void setCurrent(void);
void sendErrorCode(void);
void sendRpmHigh(void);
void sendRpmLow(void);
void getVoltage(void);
void getCurrent(void);
void DataTransmitted(void);


void spi_ext_init(void)
{
    spi_ext_irq = &ReceiveCmd;
    #pragma MESSAGE DISABLE C4002        /* Disable warning C4002 "Result not used" */
    (void)SPI1S;                         /* Read the status register */
    (void)SPI1D16;                       /* Read the data register */
    /* SPI1C2: SPMIE=0,SPIMODE=0,??=0,MODFEN=0,BIDIROE=0,??=0,SPISWAI=0,SPC0=0 */
    SPI1C2 = (uint8_t) 0x00U;           /* Configure the SPI port - control register 2 */
    /* SPI1C1: SPIE=1,SPE=1,SPTIE=1,MSTR=0,CPOL=0,CPHA=1,SSOE=0,LSBFE=1 */
    SPI1C1 = (uint8_t) 0x85U;          /*  Configure the SPI port - control register 1 */

    SPI1C1_SPE = 1U;                    /* Enable device */
    SPI1DL = CMD_DUMMY;
}

/* main interrupt function */
void ReceiveCmd(void)
{
    (void) SPI1S;
    switch (SPI1DL)
    {
    case CMD_START:
        /* Start byte received */
    	motor_set_mode(MOTOR_MODE_RUN_FREE);
        SPI1DL = CMD_DUMMY;
        break;
    case CMD_STOP:
        /* Stop byte received */
    	motor_set_mode(MOTOR_MODE_BRAKE);
        SPI1DL = CMD_DUMMY;
        break;
    case CMD_SET_RPM:
        /* set RPM */
        spi_ext_irq = &receiveRpmHigh;
        SPI1DL = CMD_DUMMY;
        break;
    case CMD_SET_VOLATGE:
        /* set voltage */
    	spi_ext_irq = &setVoltage;
        SPI1DL = CMD_DUMMY;
        break;
    case CMD_SET_CURRENT:
        /* set current */
    	spi_ext_irq = &sendRpmHigh;
        SPI1DL = CMD_DUMMY;
        break;
    case CMD_GET_STATUS:
        /* return status */
        spi_ext_irq = &sendErrorCode;
        SPI1DL = (char)motor_get_mode();
        break;
    case CMD_ARE_YOU_ALIVE:
    	/* Are you alive received */
        spi_ext_irq = &DataTransmitted;
        SPI1DL = I_AM_ALIVE;
        break;
    case CMD_MEASUREMENT_PARAM:
    	/* Start measurement with parameter */
        break;
    case CMD_MEASUREMENT:
    	/* Start measurement (step-answer) */
    	motor_set_mode(MOTOR_MODE_RUN_FREE);
        SPI1DL = CMD_DUMMY;
        break;
    case CMD_GET_MEASUREMENT:
    	/* get measurement */
        break;
    }
}

void receiveRpmHigh(void)
{
    /* Set new speed */
    spi_ext_irq = &receiveRpmLow;
    (void) SPI1S;
    set_prm_high(SPI1DL);
}

void receiveRpmLow(void)
{
    /* Set new speed */
    spi_ext_irq = &ReceiveCmd;
    (void) SPI1S;
    set_prm_low(SPI1DL);
}

void setVoltage(void)
{
    spi_ext_irq = &ReceiveCmd;
    (void) SPI1S;
    setVoltage_to_DRV(SPI1DL);
}

void setCurrent(void)
{
    spi_ext_irq = &ReceiveCmd;
    (void) SPI1S;
    setCurrent_to_DRV(SPI1DL);
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
    SPI1DL = get_prm_High();
}

void sendRpmLow(void)
{
    /* return current set speed */
    spi_ext_irq = &DataTransmitted;
    (void) SPI1S;
    SPI1DL = get_prm_low();
}

void DataTransmitted(void)
{
    spi_ext_irq = &ReceiveCmd;
    (void) SPI1S;
    SPI1DL = CMD_DUMMY;
}
