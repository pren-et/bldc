/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file drv8301.h
 * \brief Driver for three phase pre-driver DRV8301 from Texas Instruments
 * \author pren-et
 * 
 */

#ifndef DRV8301_H
#define DRV8301_H

#include "platform.h"
#include "hardware.h"

/******************************************************************************
Test compiler dependencies
******************************************************************************/
/*! \union test_bitfield_t
 *  \brief Type for testing the implementation of bitfields in the current compiler
 */
typedef union {
    struct {
        uint8_t low     : 4;    /*!< Low nibble */
        uint8_t high    : 4;    /*!< High nibble */
    } bitfield;             /*!< Nibbles */
    uint8_t     byte;       /*!< Byte */
} test_bitfield_t;

/******************************************************************************
Registers
******************************************************************************/

#define DRV8301_REG_LEN     2   /*!< Register length */
#define DRV8301_REG_COUNT   4   /*!< Number of Registers */

/*! \enum drv8301_reg_rw_t
 *  \brief Possible access levels for registers.
 */
typedef enum {
    DRV8301_REG_RW_W,  /*!< always writable */
    DRV8301_REG_RW_R   /*!< readable only */
} drv8301_reg_rw_t;

/*! \enum drv8301_addr_t
 *  \brief register address
 */
typedef enum {
    DRV8301_ADDR_STATUS1,   /*!< Status 1 */
    DRV8301_ADDR_STATUS2,   /*!< Status 2 */
    DRV8301_ADDR_CONTROL1,  /*!< Control 1 */
    DRV8301_ADDR_CONTROL2,  /*!< Control 2 */
} drv8301_addr_t;

/*! \enum drv8301_rw_t
 *  \brief register read / write
 */
typedef enum {
    DRV8301_RW_W,           /*!< Write */
    DRV8301_RW_R            /*!< Read */
} drv8301_rw_t;

/*! \enum drv8301_frame_err_t
 *  \brief register frame error
 */
typedef enum {
    DRV8301_FRAME_ERR_NONE, /*!< No frame error */
    DRV8301_FRAME_ERR_ERR   /*!< Frame error in previous command */
} drv8301_frame_err_t;

/*! \name status1
 * @{
 */
#define DRV8301_REG_STATUS1_ADDR            0x00
#define DRV8301_REG_STATUS1_RW              DRV8301_REG_RW_R
#define DRV8301_REG_STATUS1_DEFAULT         0x0000
#define DRV8301_REG_STATUS1_FETLC_OC_MASK   (1 <<  0)
#define DRV8301_REG_STATUS1_FETHC_OC_MASK   (1 <<  1)
#define DRV8301_REG_STATUS1_FETLB_OC_MASK   (1 <<  2)
#define DRV8301_REG_STATUS1_FETHB_OC_MASK   (1 <<  3)
#define DRV8301_REG_STATUS1_FETLA_OC_MASK   (1 <<  4)
#define DRV8301_REG_STATUS1_FETHA_OC_MASK   (1 <<  5)
#define DRV8301_REG_STATUS1_OTW_MASK        (1 <<  6)
#define DRV8301_REG_STATUS1_OTSD_MASK       (1 <<  7)
#define DRV8301_REG_STATUS1_PVDD_UV_MASK    (1 <<  8)
#define DRV8301_REG_STATUS1_GVDD_UV_MASK    (1 <<  9)
#define DRV8301_REG_STATUS1_FAULT_MASK      (1 << 10)
/*! @} */
/*! \union drv8301_reg_status1_t
 *  \brief Register STATUS1
 */
typedef union {
    uint16_t    raw;                        /*!< raw data access */
    uint8_t     array[DRV8301_REG_LEN];     /*!< array access */
    struct {
        uint16_t                fetlc_oc        :  1;   /*!< overcurrent event on lower fet c */
        uint16_t                fethc_oc        :  1;   /*!< overcurrent event on higher fet c */
        uint16_t                fetlb_oc        :  1;   /*!< overcurrent event on lower fet b */
        uint16_t                fethb_oc        :  1;   /*!< overcurrent event on higher fet b */
        uint16_t                fetla_oc        :  1;   /*!< overcurrent event on lower fet a */
        uint16_t                fetha_oc        :  1;   /*!< overcurrent event on higher fet a */
        uint16_t                otw             :  1;   /*!< overtemperature warning */
        uint16_t                otsd            :  1;   /*!< overtemperature shutdown */
        uint16_t                pvdd_uv         :  1;   /*!< undervoltage event on power supply voltage */
        uint16_t                gvdd_uv         :  1;   /*!< undervoltage event on gate supply voltage */
        uint16_t                fault           :  1;   /*!< fault event */
        drv8301_addr_t          addr            :  4;   /*!< address */
        drv8301_frame_err_t     frame_err       :  1;   /*!< frame error */
    } reg_read;                             /*!< raw data access for reading */
    struct {
        uint16_t                fetlc_oc        :  1;   /*!< overcurrent event on lower fet c */
        uint16_t                fethc_oc        :  1;   /*!< overcurrent event on higher fet c */
        uint16_t                fetlb_oc        :  1;   /*!< overcurrent event on lower fet b */
        uint16_t                fethb_oc        :  1;   /*!< overcurrent event on higher fet b */
        uint16_t                fetla_oc        :  1;   /*!< overcurrent event on lower fet a */
        uint16_t                fetha_oc        :  1;   /*!< overcurrent event on higher fet a */
        uint16_t                otw             :  1;   /*!< overtemperature warning */
        uint16_t                otsd            :  1;   /*!< overtemperature shutdown */
        uint16_t                pvdd_uv         :  1;   /*!< undervoltage event on power supply voltage */
        uint16_t                gvdd_uv         :  1;   /*!< undervoltage event on gate supply voltage */
        uint16_t                fault           :  1;   /*!< fault event */
        drv8301_addr_t          addr            :  4;   /*!< address */
        drv8301_rw_t            rw              :  1;   /*!< read / write */
    } reg_write;                            /*!< raw data access for writing */
} drv8301_reg_status1_t;

/*! \name status2
 * @{
 */
#define DRV8301_REG_STATUS2_ADDR            0x01
#define DRV8301_REG_STATUS2_RW              DRV8301_REG_RW_R
#define DRV8301_REG_STATUS2_DEFAULT         0x0800
#define DRV8301_REG_STATUS2_ID              0x00
#define DRV8301_REG_STATUS2_ID_MASK         0x0F
#define DRV8301_REG_STATUS2_GVDD_OV_MASK    (1 << 7)
/*! @} */
/*! \union drv8301_reg_status2_t
 *  \brief Register STATUS2
 */
typedef union {
    uint16_t    raw;                        /*!< raw data access */
    uint8_t     array[DRV8301_REG_LEN];     /*!< array access */
    struct {
        uint16_t                dev_id          :  4;   /*!< device id */
        uint16_t                unused1         :  3;   /*!< unused bits */
        uint16_t                gvdd_ov         :  1;   /*!< overvoltage event on gate power supply */
        uint16_t                unused2         :  3;   /*!< unused bits */
        drv8301_addr_t          addr            :  4;   /*!< address */
        drv8301_frame_err_t     frame_err       :  1;   /*!< frame error */
    } reg_read;                             /*!< raw data access for reading */
    struct {
        uint16_t                dev_id          :  4;   /*!< device id */
        uint16_t                unused1         :  3;   /*!< unused bits */
        uint16_t                gvdd_ov         :  1;   /*!< overvoltage event on gate power supply */
        uint16_t                unused2         :  3;   /*!< unused bits */
        drv8301_addr_t          addr            :  4;   /*!< address */
        drv8301_rw_t            rw              :  1;   /*!< read / write */
    } reg_write;                            /*!< raw data access for writing */
} drv8301_reg_status2_t;

/*! \name control1
 * @{
 */
#define DRV8301_REG_CONTROL1_ADDR           0x02
#define DRV8301_REG_CONTROL1_RW             DRV8301_REG_RW_W
#define DRV8301_REG_CONTROL1_DEFAULT        0x1400
/*! @} */
/*! \enum drv8301_gate_current_t
 *  \brief Settings for gate current
 */
typedef enum {
    DRV8301_GATE_CURRENT_1_7A,  /*!< gate current 1.7A */
    DRV8301_GATE_CURRENT_0_7A,  /*!< gate current 0.7A */
    DRV8301_GATE_CURRENT_0_25A  /*!< gate current 0.25A */
} drv8301_gate_current_t;
/*! \enum drv8301_gate_reset_t
 *  \brief Gate reset
 */
typedef enum {
    DRV8301_GATE_RESET_NORMAL,  /*!< normal mode */
    DRV8301_GATE_RESET_RESET    /*!< reset all latched faults on gate driver */
} drv8301_gate_reset_t;
/*! \enum drv8301_pwm_mode_t
 *  \brief PWM mode
 */
typedef enum {
    DRV8301_PWM_MODE_SIX,       /*!< six independent inputs */
    DRV8301_PWM_MODE_THREE      /*!< three independent inputs */
} drv8301_pwm_mode_t;
/*! \enum drv8301_oc_mode_t
 *  \brief Overcurrent protection mode
 */
typedef enum {
    DRV8301_OC_MODE_CURR_LIM,   /*!< Current limiting */
    DRV8301_OC_MODE_SHUTDOWN,   /*!< shut down */
    DRV8301_OC_MODE_REPORT,     /*!< only report overcurrent */
    DRV8301_OC_MODE_DISABLE     /*!< disable overcurrent protection */
} drv8301_oc_mode_t;
/*! \enum drv8301_oc_adj_set_t
 *  \brief Overcurrent threshold
 */
typedef enum {
    DRV8301_OC_ADJ_SET_0_060V,  /*!< Overcurrent threshold at 0.060V */
    DRV8301_OC_ADJ_SET_0_068V,  /*!< Overcurrent threshold at 0.068V */
    DRV8301_OC_ADJ_SET_0_076V,  /*!< Overcurrent threshold at 0.076V */
    DRV8301_OC_ADJ_SET_0_086V,  /*!< Overcurrent threshold at 0.086V */
    DRV8301_OC_ADJ_SET_0_097V,  /*!< Overcurrent threshold at 0.097V */
    DRV8301_OC_ADJ_SET_0_109V,  /*!< Overcurrent threshold at 0.109V */
    DRV8301_OC_ADJ_SET_0_123V,  /*!< Overcurrent threshold at 0.123V */
    DRV8301_OC_ADJ_SET_0_138V,  /*!< Overcurrent threshold at 0.138V */
    DRV8301_OC_ADJ_SET_0_155V,  /*!< Overcurrent threshold at 0.155V */
    DRV8301_OC_ADJ_SET_0_175V,  /*!< Overcurrent threshold at 0.175V */
    DRV8301_OC_ADJ_SET_0_197V,  /*!< Overcurrent threshold at 0.197V */
    DRV8301_OC_ADJ_SET_0_222V,  /*!< Overcurrent threshold at 0.222V */
    DRV8301_OC_ADJ_SET_0_250V,  /*!< Overcurrent threshold at 0.250V */
    DRV8301_OC_ADJ_SET_0_282V,  /*!< Overcurrent threshold at 0.282V */
    DRV8301_OC_ADJ_SET_0_317V,  /*!< Overcurrent threshold at 0.317V */
    DRV8301_OC_ADJ_SET_0_358V,  /*!< Overcurrent threshold at 0.358V */
    DRV8301_OC_ADJ_SET_0_403V,  /*!< Overcurrent threshold at 0.403V */
    DRV8301_OC_ADJ_SET_0_454V,  /*!< Overcurrent threshold at 0.454V */
    DRV8301_OC_ADJ_SET_0_511V,  /*!< Overcurrent threshold at 0.511V */
    DRV8301_OC_ADJ_SET_0_576V,  /*!< Overcurrent threshold at 0.576V */
    DRV8301_OC_ADJ_SET_0_648V,  /*!< Overcurrent threshold at 0.648V */
    DRV8301_OC_ADJ_SET_0_730V,  /*!< Overcurrent threshold at 0.730V */
    DRV8301_OC_ADJ_SET_0_822V,  /*!< Overcurrent threshold at 0.822V */
    DRV8301_OC_ADJ_SET_0_926V,  /*!< Overcurrent threshold at 0.926V */
    DRV8301_OC_ADJ_SET_1_046V,  /*!< Overcurrent threshold at 1.046V */
    DRV8301_OC_ADJ_SET_1_175V,  /*!< Overcurrent threshold at 1.175V */
    DRV8301_OC_ADJ_SET_1_324V,  /*!< Overcurrent threshold at 1.324V */
    DRV8301_OC_ADJ_SET_1_491V,  /*!< Overcurrent threshold at 1.491V */
    DRV8301_OC_ADJ_SET_1_679V,  /*!< Overcurrent threshold at 1.679V */
    DRV8301_OC_ADJ_SET_1_892V,  /*!< Overcurrent threshold at 1.892V */
    DRV8301_OC_ADJ_SET_2_131V,  /*!< Overcurrent threshold at 2.131V */
    DRV8301_OC_ADJ_SET_2_400V   /*!< Overcurrent threshold at 2.400V */
} drv8301_oc_adj_set_t;
/*! \union drv8301_reg_control1_t
 *  \brief Register CONTROL1
 */
typedef union {
    uint16_t    raw;                        /*!< raw data access */
    uint8_t     array[DRV8301_REG_LEN];     /*!< array access */
    struct {
        drv8301_gate_current_t  gate_current    :  2;   /*!< gate current */
        drv8301_gate_reset_t    gate_reset      :  1;   /*!< gate reset */
        drv8301_pwm_mode_t      pwm_mode        :  1;   /*!< pwm mode */
        drv8301_oc_mode_t       oc_mode         :  2;   /*!< overcurrent mode (gate driver) */
        drv8301_oc_adj_set_t    oc_adj_set      :  5;   /*!< overcurrent trigger adjustment */
        drv8301_addr_t          addr            :  4;   /*!< address */
        drv8301_frame_err_t     frame_err       :  1;   /*!< frame error */
    } reg_read;                             /*!< raw data access for reading */
    struct {
        drv8301_gate_current_t  gate_current    :  2;   /*!< gate current */
        drv8301_gate_reset_t    gate_reset      :  1;   /*!< gate reset */
        drv8301_pwm_mode_t      pwm_mode        :  1;   /*!< pwm mode */
        drv8301_oc_mode_t       oc_mode         :  2;   /*!< overcurrent mode (gate driver) */
        drv8301_oc_adj_set_t    oc_adj_set      :  5;   /*!< overcurrent trigger adjustment */
        drv8301_addr_t          addr            :  4;   /*!< address */
        drv8301_rw_t            rw              :  1;   /*!< read / write */
    } reg_write;                            /*!< raw data access for writing */
} drv8301_reg_control1_t;

/*! \name control2
 * @{
 */
#define DRV8301_REG_CONTROL2_ADDR       0x03
#define DRV8301_REG_CONTROL2_RW         DRV8301_REG_RW_W
#define DRV8301_REG_CONTROL2_DEFAULT    0x1800
/*! @} */
/*! \enum drv8301_octw_set_t
 *  \brief Overcurrent / Overtemperature reports on OCTW pin
 */
typedef enum {
    DRV8301_OCTW_SET_OT_OC,     /*!< Report Overtemperature and Overcurrent */
    DRV8301_OCTW_SET_OT,        /*!< Report Overtemperature only */
    DRV8301_OCTW_SET_OC,        /*!< Report Overcurrent only */
    DRV8301_OCTW_SET_OC_2,      /*!< Report Overcurrent only */
} drv8301_octw_set_t;
/*! \enum drv8301_gain_t
 *  \brief Shunt amplifier gain selection
 */
typedef enum {
    DRV8301_GAIN_10,            /*!< Gain of shunt amplifier 10 */
    DRV8301_GAIN_20,            /*!< Gain of shunt amplifier 20 */
    DRV8301_GAIN_40,            /*!< Gain of shunt amplifier 40 */
    DRV8301_GAIN_80             /*!< Gain of shunt amplifier 80 */
} drv8301_gain_t;
/*! \enum drv8301_dc_cal_ch1_t
 *  \brief Calibration of shunt amplifier 1
 */
typedef enum {
    DRV8301_DC_CAL_CH1_OFF,     /*!< Normal operation of shunt amplifier 1 */
    DRV8301_DC_CAL_CH1_ON       /*!< Calibration of shunt amplifier 1 */
} drv8301_dc_cal_ch1_t;
/*! \enum drv8301_dc_cal_ch2_t
 *  \brief Calibration of shunt amplifier 2
 */
typedef enum {
    DRV8301_DC_CAL_CH2_OFF,     /*!< Normal operation of shunt amplifier 2 */
    DRV8301_DC_CAL_CH2_ON       /*!< Calibration of shunt amplifier 2 */
} drv8301_dc_cal_ch2_t;
/*! \enum drv8301_oc_toff_t
 *  \brief Off time behaviour during overcurrent event
 */
typedef enum {
    DRV8301_OC_TOFF_NORMAL,     /*!< Normal CBC operation */
    DRV8301_OC_TOFF_OFF_TIME,   /*!< Off time control during overcurrent */
} drv8301_oc_toff_t;
/*! \union drv8301_reg_control2_t
 *  \brief Register CONTROL2
 */
typedef union {
    uint16_t    raw;                        /*!< raw data access */
    uint8_t     array[DRV8301_REG_LEN];     /*!< array access */
    struct {
        drv8301_octw_set_t      octw_set        :  2;   /*!< report behaviour on overtemperature and overcurrent events */
        drv8301_gain_t          gain            :  2;   /*!< shunt amplifier gain */
        drv8301_dc_cal_ch1_t    dc_cal_ch1      :  1;   /*!< calibration of shunt amplifier 1 */
        drv8301_dc_cal_ch2_t    dc_cal_ch2      :  1;   /*!< calibration of shunt amplifier 2 */
        drv8301_oc_toff_t       oc_toff         :  1;   /*!<  */
        uint16_t                unused          :  4;   /*!< unused bits */
        drv8301_addr_t          addr            :  4;   /*!< address */
        drv8301_frame_err_t     frame_err       :  1;   /*!< frame error */
    } reg_read;                             /*!< raw data access for reading */
    struct {
        drv8301_octw_set_t      octw_set        :  2;   /*!< report behaviour on overtemperature and overcurrent events */
        drv8301_gain_t          gain            :  2;   /*!< shunt amplifier gain */
        drv8301_dc_cal_ch1_t    dc_cal_ch1      :  1;   /*!< calibration of shunt amplifier 1 */
        drv8301_dc_cal_ch2_t    dc_cal_ch2      :  1;   /*!< calibration of shunt amplifier 2 */
        drv8301_oc_toff_t       oc_toff         :  1;   /*!<  */
        uint16_t                unused          :  4;   /*!< unused bits */
        drv8301_addr_t          addr            :  4;   /*!< address */
        drv8301_rw_t            rw              :  1;   /*!< read / write */
    } reg_write;                            /*!< raw data access for writing */
} drv8301_reg_control2_t;

/*! \union drv8301_reg_t
 *  \brief generic Datatype for all registers
 */
typedef union {
    uint16_t    raw;                        /*!< raw data access */
    uint8_t     array[DRV8301_REG_LEN];     /*!< array access */
    struct {
        uint16_t                data            : 11;   /*!< unused bits */
        drv8301_addr_t          addr            :  4;   /*!< address */
        drv8301_frame_err_t     frame_err       :  1;   /*!< frame error */
    } data_read;                            /*!< raw data access for reading */
    struct {
        uint16_t                data            : 11;   /*!< unused bits */
        drv8301_addr_t          addr            :  4;   /*!< address */
        drv8301_rw_t            rw              :  1;   /*!< read / write */
    } data_write;                           /*!< raw data access for writing */
    drv8301_reg_status1_t       status1;    /*!< register status1 */
    drv8301_reg_status2_t       status2;    /*!< register status1 */
    drv8301_reg_control1_t      control1;   /*!< register status1 */
    drv8301_reg_control2_t      control2;   /*!< register status1 */
} drv8301_reg_t;

/******************************************************************************
Functions
******************************************************************************/
/*! \fn void drv8301_init(void)
 *  \brief Initialisation function for DRV8301
 *  
 *  \return void
 */
void drv8301_init(void);

/*! \fn void drv8301_disable(void)
 *  \brief Disable the DRV8301 and the SPI-Interface.
 *  
 *  \return void
 */
void drv8301_disable(void);

/*! \fn drv8301_reg_t drv8301_read_register(drv8301_addr_t address)
 *  \brief Read a register from the DRV8301
 *  This function sends dummy data to read a register. 
 *  
 *  \param  address     Address of register to be read
 *  \return register
 */
drv8301_reg_t drv8301_read_register(drv8301_addr_t address);

/*! \fn void drv8301_write_register(drv8301_reg_t reg)
 *  \brief Read a register from the DRV8301
 *  This function first checks if the chosen register is writable. 
 *  Then if so, writes the register. 
 *  
 *  \param  reg         Register to be written
 *  \return void
 */
void drv8301_write_register(drv8301_reg_t reg);

/*! \fn void drv8301_set_gate_current(uint16_t current_mA)
 *  \brief Set the gate current
 *  
 *  \param  current_mA  gate current in mA
 *  \return void
 */
void drv8301_set_gate_current(uint16_t current_mA);

/*! \fn void drv8301_set_oc_adj_set(uint16_t voltage_mV)
 *  \brief Set the overcurrent adjustment register
 *  
 *  \param  voltage_mV  Overcurrent threshold value in mV
 *  \return void
 */
void drv8301_set_oc_adj_set(uint16_t voltage_mV);

/*! \fn void handleDrv(void)
 *  \brief This function is for the internal use only. 
 *  It has to be called periodical in main
 *  
 *  \return void
 */
void handleDrv(void);

/*! \fn uint16_t drv8301_get_register(drv8301_addr_t address)
 *  \brief Read a register from the DRV8301
 *  This function sends dummy data to read a register. 
 *  This function gives the value immediately.
 *  
 *  \param  address     Address of register to be read
 *  \return register
 */
uint16_t drv8301_get_register(drv8301_addr_t address);

/*! \fn void drv8301_set_config(drv8301_addr_t addr, uint16_t value)
 *  \brief This function is used to config the DRV by the host
 *  
 *  \param  addr     Address of register to be write
 *  \param  value    Register to be written
 *  \return register
 */
void drv8301_set_config(drv8301_addr_t addr, uint16_t value);
#endif /* DRV8301_H */
