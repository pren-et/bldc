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
#include "pwm.h"



void ReceiveCmd(void);
void receiveRpmHigh(void);
void receiveRpmLow(void);
void setVoltageHigh(void);
void setVoltageLow(void);
void setCurrent(void);
void sendErrorCode(void);
void sendRpmHigh(void);
void sendRpmLow(void);
void getVoltage(void);
void getCurrent(void);
void setPwm(void);
void DataTransmitted(void);

volatile void (*spi_ext_irq) (void) = &ReceiveCmd;


void spi_ext_init(void)
{
    spi_ext_irq = &ReceiveCmd;
    #pragma MESSAGE DISABLE C4002        /* Disable warning C4002 "Result not used" */
    (void)SPI1S;                         /* Read the status register */
    (void)SPI1D16;                       /* Read the data register */
    /* SPI1C2: SPMIE=0,SPIMODE=0,??=0,MODFEN=0,BIDIROE=0,??=0,SPISWAI=0,SPC0=0 */
    SPI1C2 = (uint8_t) 0x00U;           /* Configure the SPI port - control register 2 */
    /* SPI1C1: SPIE=1,SPE=0,SPTIE=0,MSTR=0,CPOL=0,CPHA=1,SSOE=0,LSBFE=1 */
    SPI1C1 = (uint8_t) 0x85U;          /*  Configure the SPI port - control register 1 */
    SPI1DL = CMD_DUMMY;
    SPI1C1_SPE = 1U;                    /* Enable device */
}

/* main interrupt function */
void ReceiveCmd(void)
{
    while(!SPI1S_SPRF);                 /* Warten bis ein Byte empfangen wurde */
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
    	spi_ext_irq = &setVoltageHigh;
        SPI1DL = CMD_DUMMY;
        break;
    case CMD_SET_CURRENT:
        /* set current */
    	spi_ext_irq = &setCurrent;
        SPI1DL = CMD_DUMMY;
        break;
    case CMD_GET_STATUS:
        /* return status */
        spi_ext_irq = &sendErrorCode;
        SPI1DL = (char)motor_get_mode();
        break;
    case CMD_ARE_YOU_ALIVE:
    	/* Are you alive received */
        while(!SPI1S_SPTEF);
        SPI1DL = I_AM_ALIVE;
        spi_ext_irq = &DataTransmitted;
        break;
    case CMD_SET_PWM:
        spi_ext_irq = &setPwm;
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
    /* Set the received speed-high-Byte */
    spi_ext_irq = &receiveRpmLow;
    while(!SPI1S_SPRF);                 /* Warten bis ein Byte empfangen wurde */
    pid_set_rpm_high(SPI1DL);
}

void receiveRpmLow(void)
{
    /* Set the received speed-low-Byte */
    spi_ext_irq = &ReceiveCmd;
    while(!SPI1S_SPRF);                 /* Warten bis ein Byte empfangen wurde */
    pid_set_rpm_low(SPI1DL);
}

void setVoltageHigh(void)
{
    /* Set the received voltage-high-Byte to the DRV */
    spi_ext_irq = &setVoltageLow;
    while(!SPI1S_SPTEF);
    setVoltage_to_DRV_high(SPI1DL);
}

void setVoltageLow(void)
{
    /* Set the received voltage-low-Byte to the DRV */
    spi_ext_irq = &ReceiveCmd;
    while(!SPI1S_SPTEF);
    setVoltage_to_DRV_low(SPI1DL);
}

void setCurrent(void)
{
    /* Set the received current to the DRV */
    spi_ext_irq = &ReceiveCmd;
    while(!SPI1S_SPTEF);
    setCurrent_to_DRV(SPI1DL);
}

void sendErrorCode(void)
{
    /* Send the error-code */
    spi_ext_irq = &sendRpmHigh;
    while(!SPI1S_SPTEF);
    SPI1DL = getErrors_form_DRV();
}

void sendRpmHigh(void)
{
    /* Send the high-byte of the rpm-value */
    spi_ext_irq = &sendRpmLow;
    while(!SPI1S_SPTEF);
    SPI1DL =pid_get_rpm_high();
}

void sendRpmLow(void)
{
    /* Send the low-byte of the rpm-value */
    spi_ext_irq = &DataTransmitted;
    while(!SPI1S_SPTEF);
    SPI1DL = pid_get_rpm_low();
}

void setPwm(void)
{
    /* Set the received value of pwm */
    spi_ext_irq = &ReceiveCmd;
    while(!SPI1S_SPRF);
   	pwm_set_100(SPI1DL);
}

void DataTransmitted(void)
{
    /* Dummy-function needed because the host will clock 
     * again and we doesn't have to send something */
    spi_ext_irq = &ReceiveCmd;
    while(!SPI1S_SPTEF);
    SPI1DL = CMD_DUMMY;
}
