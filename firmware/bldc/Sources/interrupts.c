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

/* LED for load display of interrupt service routines */
#define LED_LOAD (1)

extern volatile void (*spi_ext_irq) (void);
uint16_t speed_meas_u;
uint16_t speed_meas_v;
uint16_t speed_meas_w;

interrupt void isr_RTC(void)        // RTC
{
    #if LED_LOAD
        led_load_on();
    #endif
    RTCSC_RTIF = 1;
    rtc_set_flag();
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_IIC(void)        // IIC
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_ACMP(void)       // ACMP
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_ADC(void)        // ADC Conversion
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_KBI(void)        // KBI Keyboard
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_SCI2T(void)      // SCI2 transmit
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_SCI2R(void)      // SCI2 receive
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_SCI2E(void)      // SCI2 error
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_SCI1T(void)      // SCI1 transmit
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_SCI1R(void)      // SCI1 receive
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_SCI1E(void)      // SCI1 error
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_TPM2O(void)      // TPM2 overflow
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_TPM2CH1(void)    // TPM2 channel 1
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_TPM2CH0(void)    // TPM2 channel 0
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_TPM1O(void)      // TPM1 overflow
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_TPM1CH5(void)    // TPM1 channel 5
{
    /* variable for measuring time between commutations */
    static uint16_t capture_v = 0;
    motor_status_t mot_status;
    uint8_t auto_comm;

    #if LED_LOAD
        led_load_on();
    #endif

    /* clear interrupt flag */
    if (TPM1C5SC_CH5F) {                /* clear channel interrupt flag */
        TPM1C5SC_CH5F = 0;
    }

    /* prepare next commutation */
    mot_status = motor_get_status();
    auto_comm = ((mot_status == MOTOR_STATUS_AUTO_FREE) | (mot_status == MOTOR_STATUS_AUTO_PID));
    TPM1C5SC_CH5IE = 0x00;              /* Disable interrupt on hall V */
    if (TPM1C5SC_ELS5A) {               /* rising edge on hall V */
        //TPM1C5SC_ELS5x = 0x02;              /* change trigger to falling edge */
        if (auto_comm) {                  /* check if forced commutation disabled */
            commutate_state(COMM_STATE_AUTO_2);
        }
        TPM1C4SC_ELS4x = 0x02;              /* Prepare interrupt for falling edge on hall U */
        TPM1C4SC_CH4IE = 0x01;
        if (TPM1C4SC_CH4F) {
            TPM1C4SC_CH4F = 0;
        }
    }
    else {                              /* falling edge on hall V */
        //TPM1C5SC_ELS5x = 0x01;              /* change trigger to rising edge */
        if (auto_comm) {                  /* check if forced commutation disabled */
            commutate_state(COMM_STATE_AUTO_5);
        }
        TPM1C4SC_ELS4x = 0x01;              /* Prepare interrupt for rising edge on hall U */
        TPM1C4SC_CH4IE = 0x01;
        if (TPM1C4SC_CH4F) {
            TPM1C4SC_CH4F = 0;
        }
    }

    /* measure time between commutations */
    speed_meas_v = TPM1C5V - capture_v;
    capture_v = TPM1C5V;
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_TPM1CH4(void)    // TPM1 channel 4
{
    /* variable for measuring time between commutations */
    static uint16_t capture_u = 0;
    motor_status_t mot_status;
    uint8_t auto_comm;

    #if LED_LOAD
        led_load_on();
    #endif

    /* clear interrupt flag */
    if (TPM1C4SC_CH4F) {                /* clear channel interrupt flag */
        TPM1C4SC_CH4F = 0;
    }

    /* prepare next commutation */
    mot_status = motor_get_status();
    auto_comm = ((mot_status == MOTOR_STATUS_AUTO_FREE) | (mot_status == MOTOR_STATUS_AUTO_PID));
    TPM1C4SC_CH4IE = 0x00;              /* Disable interrupt on hall U */
    if (TPM1C4SC_ELS4A) {               /* rising edge on hall U */
        //TPM1C4SC_ELS4x = 0x02;              /* change trigger to falling edge */
        if (auto_comm) {                  /* check if forced commutation disabled */
            commutate_state(COMM_STATE_AUTO_0);
        }
        TPM1C3SC_ELS3x = 0x02;              /* Prepare interrupt for falling edge on hall W */
        TPM1C3SC_CH3IE = 0x01;
        if (TPM1C3SC_CH3F) {
            TPM1C3SC_CH3F = 0;
        }
    }
    else {                              /* falling edge on hall U */
        //TPM1C4SC_ELS4x = 0x01;              /* change trigger to rising edge */
        if (auto_comm) {                  /* check if forced commutation disabled */
            commutate_state(COMM_STATE_AUTO_3);
        }
        TPM1C3SC_ELS3x = 0x01;              /* Prepare interrupt for rising edge on hall W */
        TPM1C3SC_CH3IE = 0x01;
        if (TPM1C3SC_CH3F) {
            TPM1C3SC_CH3F = 0;
        }
    }

    /* measure time between commutations */
    speed_meas_u = TPM1C4V - capture_u;
    capture_u = TPM1C4V;
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_TPM1CH3(void)    // TPM1 channel 3
{
    /* variable for measuring time between commutations */
    static uint16_t capture_w = 0;
    motor_status_t mot_status;
    uint8_t auto_comm;

    #if LED_LOAD
        led_load_on();
    #endif

    /* clear interrupt flag */
    if (TPM1C3SC_CH3F) {                /* clear channel interrupt flag */
        TPM1C3SC_CH3F = 0;
    }

    /* prepare next commutation */
    mot_status = motor_get_status();
    auto_comm = ((mot_status == MOTOR_STATUS_AUTO_FREE) | (mot_status == MOTOR_STATUS_AUTO_PID));
    TPM1C3SC_CH3IE = 0x00;              /* Disable interrupt on hall W */
    if (TPM1C3SC_ELS3A) {               /* rising edge on hall W */
        //TPM1C3SC_ELS3x = 0x02;              /* change trigger to falling edge */
        if (auto_comm) {                  /* check if forced commutation disabled */
            commutate_state(COMM_STATE_AUTO_4);
        }
        TPM1C5SC_ELS5x = 0x02;              /* Prepare interrupt for falling edge on hall V */
        TPM1C5SC_CH5IE = 0x01;
        if (TPM1C5SC_CH5F) {
            TPM1C5SC_CH5F = 0;
        }
    }
    else {                              /* falling edge on hall W */
        //TPM1C3SC_ELS3x = 0x01;              /* change trigger to rising edge */
        if (auto_comm) {                  /* check if forced commutation disabled */
            commutate_state(COMM_STATE_AUTO_1);
        }
        TPM1C5SC_ELS5x = 0x01;              /* Prepare interrupt for rising edge on hall V */
        TPM1C5SC_CH5IE = 0x01;
        if (TPM1C5SC_CH5F) {
            TPM1C5SC_CH5F = 0;
        }
    }

    /* measure time between commutations */
    speed_meas_w = TPM1C3V - capture_w;
    capture_w = TPM1C3V;
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_TPM1CH2(void)    // TPM1 channel 2
{
    #if LED_LOAD
        led_load_on();
    #endif
    if (TPM1C2SC_CH2F) {                /* clear channel interrupt flag */
        TPM1C2SC_CH2F = 0;
    }
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_TPM1CH1(void)    // TPM1 channel 1
{
    #if LED_LOAD
        led_load_on();
    #endif
    if (TPM1C1SC_CH1F) {                /* clear channel interrupt flag */
        TPM1C1SC_CH1F = 0;
    }
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_TPM1CH0(void)    // TPM1 channel 0
{
    #if LED_LOAD
        led_load_on();
    #endif
    if (TPM1C0SC_CH0F) {                    /* clear channel interrupt flag */
        TPM1C0SC_CH0F = 0;
    }
    TPM1C0V += motor_get_force_interval();  /* Prepare next interrupt */
    if (motor_get_status() == MOTOR_STATUS_FORCED){  /* check if forced commutation enabled */
        commutate_next();                       /* Commutate */
    }
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_USB(void)        // USB
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_SPI2(void)       // SPI2
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_SPI1(void)       // SPI1
{
    #if LED_LOAD
        led_load_on();
    #endif
    (*spi_ext_irq)();
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_MCGLOL(void)     // MCGLOL (Loss of Lock)
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_LowVoltage(void) // Low voltage detect
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_IRQ(void)        // IRQ
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

interrupt void isr_SWI(void)        // SWI
{
    #if LED_LOAD
        led_load_on();
    #endif
    #if LED_LOAD
        led_load_off();
    #endif
    return;
}

