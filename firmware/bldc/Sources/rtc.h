/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file  rtc.h
 * \brief 
 * \author pren-et
 * 
 */
#ifndef RTC_H_
#define RTC_H_

#include "platform.h"
#include "hardware.h"

/** \enum  rtc_flag_t
 *  \brief Flag being set in RTC ISR and read and cleared from main loop. 
 */
typedef enum {
    RTC_NONE = 0,       /*!< No action needed */
    RTC_PENDING = 1,    /*!< Action pending */
} rtc_flag_t;

/*! \fn void rtc_init_flag(void)
 *  \brief Function to initialize rtc flag.
 *
 *  \return void
 */
void rtc_init_flag(void);

/*! \fn rtc_flag_t rtc_get_flag(void)
 *  \brief Function to read rtc flag status.
 *
 *  \return flag
 */
rtc_flag_t rtc_get_flag(void);

/*! \fn void rtc_set_flag(void)
 *  \brief Function to set rtc flag. 
 *
 *  \return void
 */
void rtc_set_flag(void);

/*! \fn void rtc_clear_flag(void)
 *  \brief Function to clear rtc flag
 *
 *  \return void
 */
void rtc_clear_flag(void);

/*! \fn rtc_flag_t rtc_get_clear_flag(void)
 *  \brief Function to read and clear rtc flag
 *
 *  \return flag
 */
rtc_flag_t rtc_get_clear_flag(void);

#endif /* RTC_H_ */
