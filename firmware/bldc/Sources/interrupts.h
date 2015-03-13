/*
 * interrupts.h
 *
 *  Created on: Mar 15, 2014
 *      Author: daniw
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "platform.h"
#include "hardware.h"

interrupt void isr_RTC(void);        // RTC
interrupt void isr_IIC(void);        // IIC
interrupt void isr_ACMP(void);       // ACMP
interrupt void isr_ADC(void);        // ADC Conversion
interrupt void isr_KBI(void);        // KBI Keyboard
interrupt void isr_SCI2T(void);      // SCI2 transmit
interrupt void isr_SCI2R(void);      // SCI2 receive
interrupt void isr_SCI2E(void);      // SCI2 error
interrupt void isr_SCI1T(void);      // SCI1 transmit
interrupt void isr_SCI1R(void);      // SCI1 receive
interrupt void isr_SCI1E(void);      // SCI1 error
interrupt void isr_TPM2O(void);      // TPM2 overflow
interrupt void isr_TPM2CH1(void);    // TPM2 channel 1
interrupt void isr_TPM2CH0(void);    // TPM2 channel 0
interrupt void isr_TPM1O(void);      // TPM1 overflow
interrupt void isr_TPM1CH5(void);    // TPM1 channel 5
interrupt void isr_TPM1CH4(void);    // TPM1 channel 4
interrupt void isr_TPM1CH3(void);    // TPM1 channel 3
interrupt void isr_TPM1CH2(void);    // TPM1 channel 2
interrupt void isr_TPM1CH1(void);    // TPM1 channel 1
interrupt void isr_TPM1CH0(void);    // TPM1 channel 0
interrupt void isr_USB(void);        // USB
interrupt void isr_SPI2(void);       // SPI2
interrupt void isr_SPI1(void);       // SPI1
interrupt void isr_MCGLOL(void);     // MCGLOL (Loss of Lock)
interrupt void isr_LowVoltage(void); // Low voltage detect
interrupt void isr_IRQ(void);        // IRQ
interrupt void isr_SWI(void);        // SWI

#endif /* INTERRUPTS_H_ */
