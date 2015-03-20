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

#define TASK_LED_PERIOD     1000    /* Period for LED task (1s) */

void init()
{
	hardware_lowlevel_init();
    PTDD &= ~(LED_0);
    rtc_init_flag();
    EnableInterrupts;               // Interrupts aktivieren
}

/**
 * main program
 */
void main(void)
{
    uint16 task_cnt_led;
    init();
    task_cnt_led = TASK_LED_PERIOD;

    for(;;)
    {
        if(rtc_get_clear_flag() != RTC_NONE) {
            /* Task to toggle LED0 */
            if(task_cnt_led == 0) {
                task_cnt_led = TASK_LED_PERIOD; /* Prepare scheduler for next period */
                PTDD ^= LED_0;                  /* Toggle LED0 */
            }
            else {
                task_cnt_led--;
            }
            /* Other tasks come here */
        }
        __RESET_WATCHDOG();  /* feeds the dog */
    }

  /* please make sure that you never leave main */
}
