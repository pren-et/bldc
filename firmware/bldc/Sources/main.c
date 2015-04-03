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
#include "spi_drv.h"        /* include spi declarations */
#include "drv8301.h"
#include "commutate.h"  /* commutation functions */
#include "motor.h"      /* motor control */

#define TASK_PERIOD_LED     100     /* Period for LED task (1s) */
#define TASK_PERIOD_DRV     1000    /* Period for LED task (1s) */
#define TASK_PERIOD_COMM    100     /* Period for Commutation task (100ms) */

int i;
extern uint16_t force_interval;
extern uint8_t force_flag;

void init(void)
{
    hardware_lowlevel_init();
    rtc_init_flag();
    spi_drv_init();
    //spi_ext_init();
    drv8301_init();
    commutate_init();
    EnableInterrupts;               // Interrupts aktivieren
}

/**
 * main program
 */
void main(void)
{
    uint16_t task_cnt_led;
    uint16_t task_cnt_drv;
    uint16_t task_cnt_comm;
    init();
    task_cnt_led  = TASK_PERIOD_LED;
    task_cnt_drv  = TASK_PERIOD_DRV;
    task_cnt_comm = TASK_PERIOD_COMM;
    force_interval = 5000;
    force_flag = 1;
    commutate_state(COMM_STATE_FORCED_0);

    for(;;)
    {
        handleDrv();
        if(rtc_get_clear_flag() != RTC_NONE) {
            /* Switch LED on to measure workload */
            PTDD &= ~(LED_Y);  /* LED1 on */

            /* Task to toggle LED0 */
            if(task_cnt_led == 0) {
                task_cnt_led = TASK_PERIOD_LED; /* Prepare scheduler for next period */
                PTDD ^= LED_R; /* Toggle LED0 */
            }
            else {
                task_cnt_led--;
            }

            /* Task to initialize DRV8301 */
            if( task_cnt_drv == 0 ) {
                //drv8301_reg_t test, test_2;
                //test_2 = drv8301_set_gate_current(200);
                //test = drv8301_read_register(DRV8301_ADDR_CONTROL1);

                drv8301_reg_t reg,test;
                volatile unsigned int castTest;
                DisableInterrupts;
                reg.data_write.data = test.data_write.data = 0x00;
                reg.data_write.addr = test.data_write.addr = DRV8301_ADDR_CONTROL1;
                reg.data_write.rw   = DRV8301_RW_W;
                reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_250V;
                (void)spi_drv_read_write(reg.raw);


                test.data_write.rw   = DRV8301_RW_R;
                castTest = spi_drv_read_write(test.raw);

                if(test.control1.reg_read.oc_adj_set == DRV8301_OC_ADJ_SET_0_250V)
                    PTDD &= ~LED_G;
                EnableInterrupts;

                //test = drv8301_read_register(DRV8301_ADDR_CONTROL1);
                //test.data_write.addr = DRV8301_ADDR_CONTROL1;
                //test.data_write.rw = DRV8301_REG_RW_R;
                //test.data_write.data = 0U;
                //test.raw = spi_drv_read_write(test.raw);
                //if(test_2.raw == test.raw) {
                    //PTDD &= ~LED_G;
                //}

                task_cnt_drv = TASK_PERIOD_DRV; /* Prepare scheduler for next period */
            }
            else {
                task_cnt_drv--;
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
                        TPM2C0V = 767;
                    }
                    force_interval -= 20;
                }
                else if (force_interval > 300) {
                    force_interval -= 10;
                }
                //else if (force_interval > 200) {
                //    if (force_interval == 300) {
                //        TPM2C0V = 1023;
                //    }
                //    force_interval -= 5;
                //}
                //else if (force_interval > 187) {
                //    force_interval -= 2;
                //}
                //else if (force_interval > 94) {
                //    force_interval -= 1;
                //}
                else {
                    /* Final speed for forced commutation reached */
                    PTDD &= ~(LED_G);       /* turn green LED on */
                    TPM2C0V = 1023;         /* set PWM to 100% */
                    force_flag = 0;         /* disable forced commutation, enable autocommutation */
                }
            }
            else {
                task_cnt_comm--;
            }

            /* Other tasks come here */
            PTDD |= LED_Y;  /* LED1 off */
        }
        __RESET_WATCHDOG();  /* feeds the dog */
    }

  /* please make sure that you never leave main */
}
