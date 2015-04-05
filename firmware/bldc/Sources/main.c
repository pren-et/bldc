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

#include "platform.h"   /* include peripheral declarations */
#include "hardware.h"   /* include lowlevel hardware declarations */
#include "rtc.h"        /* include rtc declarations */
#include "spi_drv.h"    /* include spi declarations for the DRV communication */
#include "spi_ext.h"    /* include spi declarations for the external communication */
#include "drv8301.h"
#include "commutate.h"  /* commutation functions */
#include "motor.h"      /* motor control */
#include "led.h"        /* led control */
#include "pwm.h"        /* pwm control */

/* LED for load display in main task loop (interrupts not included) */
#define LED_LOAD (1)

#define TASK_PERIOD_LED     100     /* Period for LED task (1s) */
#define TASK_PERIOD_COMM    100     /* Period for Commutation task (100ms) */
#define TASK_INIT_PWM       10000   /* Init time for PWM task */
#define TASK_PERIOD_PWM     2000    /* Period for PWM task */

int i;
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
    EnableInterrupts;               // Interrupts aktivieren
}

/**
 * main program
 */
void main(void)
{
    uint16_t task_cnt_led;
    uint16_t task_cnt_comm;
    uint16_t task_cnt_pwm;
    init();
    task_cnt_led  = TASK_PERIOD_LED;
    task_cnt_comm = TASK_PERIOD_COMM;
    task_cnt_pwm  = TASK_INIT_PWM;
    force_interval = 5000;
    force_flag = 1;
    commutate_state(COMM_STATE_FORCED_0);

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
            if(task_cnt_comm == 0) {
                task_cnt_comm = TASK_PERIOD_COMM; /* Prepare scheduler for next period */
                if (force_interval > 10000) {
                    force_interval -= 500;
                }
                else if (force_interval > 5000) {
                    force_interval -= 200;
                }
                else if (force_interval > 2000) {
                    force_interval -= 100;
                }
                else if (force_interval > 1000) {
                    force_interval -= 50;
                }
                else if (force_interval > 500) {
                    if (force_interval == 600) {
                        //pwm_set_100(77);
                    }
                    force_interval -= 20;
                }
                //else if (force_interval > 300) {
                //    force_interval -= 10;
                //}
                else {
                    /* Final speed for forced commutation reached */
                    led_g_on();
                    //pwm_set_100(100);
                    force_flag = 0;         /* disable forced commutation, enable autocommutation */
                }
            }
            else {
                task_cnt_comm--;
            }

            /* Task to toggle PWM */
            if(task_cnt_pwm == 0) {
                task_cnt_pwm = TASK_PERIOD_PWM; /* Prepare scheduler for next period */
                if (pwm_get_100() >= 66) {
                    pwm_set_100(50);
                }
                else {
                    pwm_set_100(100);
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
