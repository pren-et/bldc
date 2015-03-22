/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file  interrupts.c
 * \brief Interrupt handling
 * \author pren-et
 * 
 */

#include "interrupts.h"
#include "rtc.h"

interrupt void isr_RTC(void)        // RTC
{
    RTCSC_RTIF = 1;
    rtc_set_flag();
    return;
}

interrupt void isr_IIC(void)        // IIC
{
    return;
}

interrupt void isr_ACMP(void)       // ACMP
{
    return;
}

interrupt void isr_ADC(void)        // ADC Conversion
{
    return;
}

interrupt void isr_KBI(void)        // KBI Keyboard
{
    return;
}

interrupt void isr_SCI2T(void)      // SCI2 transmit
{
    return;
}

interrupt void isr_SCI2R(void)      // SCI2 receive
{
    return;
}

interrupt void isr_SCI2E(void)      // SCI2 error
{
    return;
}

interrupt void isr_SCI1T(void)      // SCI1 transmit
{
    return;
}

interrupt void isr_SCI1R(void)      // SCI1 receive
{
    return;
}

interrupt void isr_SCI1E(void)      // SCI1 error
{
    return;
}

interrupt void isr_TPM2O(void)      // TPM2 overflow
{
    return;
}

interrupt void isr_TPM2CH1(void)    // TPM2 channel 1
{
    return;
}

interrupt void isr_TPM2CH0(void)    // TPM2 channel 0
{
    return;
}

interrupt void isr_TPM1O(void)      // TPM1 overflow
{
    return;
}

interrupt void isr_TPM1CH5(void)    // TPM1 channel 5
{
    return;
}

interrupt void isr_TPM1CH4(void)    // TPM1 channel 4
{
    return;
}

interrupt void isr_TPM1CH3(void)    // TPM1 channel 3
{
    return;
}

interrupt void isr_TPM1CH2(void)    // TPM1 channel 2
{
    return;
}

interrupt void isr_TPM1CH1(void)    // TPM1 channel 1
{
    return;
}

interrupt void isr_TPM1CH0(void)    // TPM1 channel 0
{
    return;
}

interrupt void isr_USB(void)        // USB
{
    return;
}

interrupt void isr_SPI2(void)       // SPI2
{
    return;
}

interrupt void isr_SPI1(void)       // SPI1
{
    return;
}

interrupt void isr_MCGLOL(void)     // MCGLOL (Loss of Lock)
{
    return;
}

interrupt void isr_LowVoltage(void) // Low voltage detect
{
    return;
}

interrupt void isr_IRQ(void)        // IRQ
{
    return;
}

interrupt void isr_SWI(void)        // SWI
{
    return;
}

