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
#include "pid.h"        /* pid */

/* LED for load display in main task loop (interrupts not included) */
#define LED_LOAD (1)

#define TASK_INIT_LED       1000    /* Init time for LED task (1s) */
#define TASK_PERIOD_LED     400    /* Period for LED task (1s) */
#define TASK_INIT_MOTOR     100     /* Init time for motor task (100ms) */
#define TASK_PERIOD_MOTOR   100     /* Period for motor task (100ms) */
#define TASK_INIT_PWM       1000   /* Init time for PWM task (1s) */
#define TASK_PERIOD_PWM     1000    /* Period for PWM task (1s) */
#define TASK_DRV            200    /* Period for PWM task (200ms) */
// for TASK_PID see pid.h

void init(void)
{
    hardware_lowlevel_init();
    rtc_init_flag();
    spi_drv_init();
    spi_ext_init();
    drv8301_init();
    pid_init();
    commutate_init();
    motor_init();
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
    uint16_t task_drv;
    uint16_t task_pid;
    init();
    task_cnt_led    = TASK_INIT_LED;
    task_cnt_motor  = TASK_INIT_MOTOR;
    task_cnt_pwm    = TASK_INIT_PWM;
    task_drv	    = TASK_DRV;
    task_pid	    = TASK_PID;

    for(;;)
    {
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
            
            /* Task to handle the DRV-Chip */
            if(task_drv == 0) {
            	task_drv = TASK_DRV; /* Prepare scheduler for next period */
                handleDrv();
            }
            else {
            	task_drv--;
            }
            
            /* Task to handle the PID */
            if(task_pid == 0) {
            	task_pid = TASK_PID; /* Prepare scheduler for next period */
            	pid_task();
            }
            else {
            	task_pid--;
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
            	static uint8_t motor_pid_flag = 0;
                task_cnt_pwm = TASK_PERIOD_PWM; /* Prepare scheduler for next period */
                if (motor_pid_flag == 1) {
                                	motor_set_mode(MOTOR_MODE_RUN_PID);
                                	motor_pid_flag = 2;
                }
                if (motor_pid_flag == 0) {
                    if (motor_get_status() == MOTOR_STATUS_AUTO_FREE) {
                        motor_pid_flag = 1;
                    }
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
