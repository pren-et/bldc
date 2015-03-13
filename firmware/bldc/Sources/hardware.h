/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file   hardware.h
 * \brief  Lowlevel hardware declaration
 * \author pren-et
 * 
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "platform.h"

#define CLOCK           24000000    // Bus clock frequency in Hz

/*
PINS:
Comment-Abbreviations:
I: Input, O: Output (PTxDD)
L: Low, H: High (PTxD)
R: Pullup Resistor active (PTxPE)
S: Slew rate control enabled (PTxSE)
D: High drive strength enabled (PTxDS)
*/

//--- Bit definitions ---
#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80


//### I/O Ports ##
//--- PortA ---
#define FET_L_W         BIT0    ///< |OL|   Lowside FET of Phase W
#define FET_H_W         BIT1    ///< |OL|   Highside FET of Phase W
#define FET_L_V         BIT2    ///< |OL|   Lowside FET of Phase V
#define FET_H_V         BIT3    ///< |OL|   Highside FET of Phase V
#define FET_L_U         BIT4    ///< |OL|   Lowside FET of Phase U
#define FET_H_U         BIT5    ///< |OL|   Highside FET of Phase U

#define PTADD_INIT      (FET_L_W | FET_H_W | FET_L_V | FET_H_V | FET_L_U | FET_H_U)
#define PTAD_INIT       (0)
#define PTAPE_INIT      (0)
#define PTASE_INIT      (0)
#define PTADS_INIT      (0)

//--- PortB ---
#define SPI_INT_MISO    BIT0    ///< |IR|   MISO on internal SPI bus
#define SPI_INT_MOSI    BIT1    ///< |IR|   MOSI on internal SPI bus
#define SPI_INT_SCK     BIT2    ///< |IR|   SCK on internal SPI bus
#define SPI_INT_CS      BIT3    ///< |OH|   CS on internal SPI bus
#define FAULT           BIT4    ///< |I|    Fault report indicator
#define OCTW            BIT5    ///< |I|    Overcurrent and/or overtemperature warning indicator
#define EN_GATE         BIT6    ///< |OL|   Gate enable
#define PTB_7           BIT7    ///< |IR|   unused

#define PTBDD_INIT      (SPI_INT_CS | EN_GATE)
#define PTBD_INIT       (SPI_INT_CS)
#define PTBPE_INIT      (SPI_INT_MISO | SPI_INT_MOSI | SPI_INT_SCK | SPI_INT_CS | PTB_7)
#define PTBSE_INIT      (0)
#define PTBDS_INIT      (0)

//--- PortC ---
#define PTC_0           BIT0    ///< |IR|   unused
#define PTC_1           BIT1    ///< |IR|   unused
#define PTC_2           BIT2    ///< |IR|   unused
#define PTC_3           BIT3    ///< |IR|   unused
#define PTC_4           BIT4    ///< |IR|   unused
#define PTC_5           BIT5    ///< |IR|   unused
#define PTC_6           BIT6    ///< |IR|   unused
#define PTC_7           BIT7    ///< |IR|   unused

#define PTCDD_INIT      (0)
#define PTCD_INIT       (0)
#define PTCPE_INIT      (PTC_0 | PTC_1 | PTC_2 | PTC_3 | PTC_4 | PTC_5 | PTC_6 | PTC_7)
#define PTCSE_INIT      (0)
#define PTCDS_INIT      (0)

//--- PortD ---
#define PTD_0           BIT0    ///< |IR|   unused
#define PTD_1           BIT1    ///< |IR|   unused
#define PWRGD           BIT2    ///< |IR|   Power good
#define PTD_3           BIT3    ///< |IR|   unused
#define LED_0           BIT4    ///< |OH|   LED 0
#define LED_1           BIT5    ///< |OH|   LED 1
#define LED_2           BIT6    ///< |OH|   LED 2
#define PTD_7           BIT7    ///< |IR|   unused

#define PTDDD_INIT      (LED_0 | LED_1 | LED_2)
#define PTDD_INIT       (LED_0 | LED_1 | LED_2)
#define PTDPE_INIT      (PTD_0 | PTD_1 | PWRGD | PTD_3 | PTD_7)
#define PTDSE_INIT      (0)
#define PTDDS_INIT      (LED_0 | LED_1 | LED_2)

//--- PortE ---
#define PTE_0           BIT0    ///< |IR|   unused
#define PTE_1           BIT1    ///< |IR|   unused
#define PTE_2           BIT2    ///< |IR|   unused
#define PTE_3           BIT3    ///< |IR|   unused
#define SPI_EXT_MISO    BIT4    ///< |IR|   MISO on external SPI bus
#define SPI_EXT_MOSI    BIT5    ///< |IR|   MOSI on external SPI bus
#define SPI_EXT_SCK     BIT6    ///< |IR|   SCK on external SPI bus
#define SPI_EXT_CS      BIT7    ///< |IR|   CS on external SPI bus

#define PTEDD_INIT      (0)
#define PTED_INIT       (0)
#define PTEPE_INIT      (PTE_0 | PTE_1 | PTE_2 | PTE_3 | SPI_EXT_MISO | SPI_EXT_MOSI | SPI_EXT_SCK | SPI_EXT_CS)
#define PTESE_INIT      (0)
#define PTEDS_INIT      (0)

//--- PortF ---
#define PTF_0           BIT0    ///< |IR|   unused
#define PTF_1           BIT1    ///< |IR|   unused
#define PTF_2           BIT2    ///< |IR|   unused
#define PTF_3           BIT3    ///< |IR|   unused
#define PWM             BIT4    ///< |OL|   PWM
#define PWM_INV         BIT5    ///< |OL|   Inverted PWM
#define PTF_6           BIT6    ///< |IR|   unused
#define PTF_7           BIT7    ///< |IR|   unused

#define PTFDD_INIT      (PWM | PWM_INV)
#define PTFD_INIT       (0)
#define PTFPE_INIT      (PTF_0 | PTF_1 | PTF_2 | PTF_3 | PTF_6 | PTF_7)
#define PTFSE_INIT      (0)
#define PTFDS_INIT      (0)

//--- PortG ---
#define IRQ             BIT0    ///< |OL|   Interrupt request
#define HALL_U          BIT1    ///< |IR|   Hall feedback for phase U
#define HALL_V          BIT2    ///< |IR|   Hall feedback for phase V
#define HALL_W          BIT3    ///< |IR|   Hall feedback for phase W
#define PTG_4           BIT4    ///< |IR|   unused
#define PTG_5           BIT5    ///< |IR|   unused

#define PTGDD_INIT      (IRQ)
#define PTGD_INIT       (0)
#define PTGPE_INIT      (HALL_U | HALL_V | HALL_W | PTG_4 | PTG_5)
#define PTGSE_INIT      (0)
#define PTGDS_INIT      (0)


//### Timer 1 ###
//--- Initialisation for generating the buzzer frequency directly from timer ---
// bus rate clock, prescaler 4
#define TPM1SC_INIT     (0)
// Initial value for a frequency of 1 kHz on Buzzer
#define TPM1MOD_INIT    (0)

//--- Initialisation for driving the buzzer with PWM ---
// bus rate clock, no prescaler
//#define TPM1SC_INIT     (TPM1SC_CLKSA_MASK)
// Modulo for a sampling rate 48 kHz
//#define TPM1MOD_INIT    (CLOCK/BUZZER_SAMPLE)
// Not in use
#define TPM1C0SC_INIT   (0)
// Not in use
#define TPM1C1SC_INIT   (0)
// Not in use
#define TPM1C2SC_INIT   (0)
// Not in use
#define TPM1C3SC_INIT   (0)
// Not in use
#define TPM1C4SC_INIT   (0)
// Buzzer not yet configured
#define TPM1C5SC_INIT   (0)
// Not in use
#define TPM1C0V_INIT    (0)
// Not in use
#define TPM1C1V_INIT    (0)
// Not in use
#define TPM1C2V_INIT    (0)
// Not in use
#define TPM1C3V_INIT    (0)
// Not in use
#define TPM1C4V_INIT    (0)
// Buzzer not yet configured
#define TPM1C5V_INIT    (0)


//### Timer 2 ###
// bus rate clock, no prescaler
#define TPM2SC_INIT     (0)
// Motor control with 10 bit resolution and a frequency of 23.4 kHz
#define TPM2MOD_INIT    (0)
// Edge aligned PWM for both motors
#define TPM2C0SC_INIT   (0)
#define TPM2C1SC_INIT   (0)
// Stop motors at startup
#define TPM2C0V_INIT    (0)
#define TPM2C1V_INIT    (0)

/** \fn void hardware_lowlevel_init(void)
 *  \brief Initialisation for low level hardware
 *
 *  \return void
 */
void hardware_lowlevel_init(void);

#endif /* HARDWARE_H_ */
