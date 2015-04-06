/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file   main.c
 * \brief  Controller for BLDC Motors
 * \author pren-et
 *
 */

#include "platform.h"   /* peripheral declarations */
#include "hardware.h"   /* lowlevel hardware declarations */
#include "rtc.h"        /* rtc declarations */
#include "spi_drv.h"    /* spi declarations for the DRV communication */
#include "spi_ext.h"    /* spi declarations for the external communication */
#include "drv8301.h"    /* interface to DRV8301 */
#include "commutate.h"  /* commutation functions */
#include "motor.h"      /* motor control */
#include "led.h"        /* led control */
#include "pwm.h"        /* pwm control */

/* LED for load display in main task loop (interrupts not included) */
#define LED_LOAD (1)

#define TASK_INIT_LED       1000    /* Init time for LED task (1s) */
#define TASK_PERIOD_LED     400    /* Period for LED task (1s) */
#define TASK_INIT_MOTOR     100     /* Init time for motor task (100ms) */
#define TASK_PERIOD_MOTOR   100     /* Period for motor task (100ms) */
#define TASK_INIT_PWM       10000   /* Init time for PWM task (10s) */
#define TASK_PERIOD_PWM     2000    /* Period for PWM task (2s) */

extern uint16_t force_interval;
extern uint8_t force_flag;

void init(void)
{
    hardware_lowlevel_init();
    rtc_init_flag();
    spi_drv_init();
    spi_ext_init();
    drv8301_init();
    motor_init();
    commutate_init();
    EnableInterrupts;               // enable Interrupts
}

/**
 * main program
 */
void main(void)
{
    uint16_t task_cnt_led;
    uint16_t task_cnt_motor;
    uint16_t task_cnt_pwm;
    init();
    task_cnt_led    = TASK_INIT_LED;
    task_cnt_motor  = TASK_INIT_MOTOR;
    task_cnt_pwm    = TASK_INIT_PWM;
    force_interval  = 5000;

    for(;;)
    {
        handleDrv();
        if(rtc_get_clear_flag() != RTC_NONE) {
            /* Switch load measurement LED on */
            //led_y_on();
            #if LED_LOAD
                led_load_on();
            #endif

            /* Task to toggle LED0 */
            if(task_cnt_led == 0) {
                task_cnt_led = TASK_PERIOD_LED; /* Prepare scheduler for next period */
                led_r_toggle();
            }
            else {
                task_cnt_led--;
            }

            /* Task to control commutation frequency */
            if(task_cnt_motor == 0) {
                task_cnt_motor = TASK_PERIOD_MOTOR; /* Prepare scheduler for next period */
                motor_task();   /* Perform motor task */
            }
            else {
                task_cnt_motor--;
            }

            /* Task to toggle PWM */
            if(task_cnt_pwm == 0) {
                task_cnt_pwm = TASK_PERIOD_PWM; /* Prepare scheduler for next period */
                if (pwm_get_100() >= 66) {
                    pwm_set_100(50);
                }
                else {
                    pwm_set_100(66);
                }
            }
            else {
                task_cnt_pwm--;
            }

            /* Other tasks come here */

            /* Switch load measurement led off */
            //led_y_off();
            #if LED_LOAD
                led_load_off();
            #endif
        }
        __RESET_WATCHDOG();  /* feeds the dog */
    }

  /* please make sure that you never leave main */
}
