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

/*! \fn rtc_flag_t rtc_get_flag(void)
 *  \brief Function to read rtc flag status.
 *
 *  \return flag
 */
void rtc_get_flag(void);

/*! \fn void rtc_set_flag(void)
 *  \brief Function to set rtc flag. 
 *
 *  \return void
 */
void rtc_set_flag(void);

/*! \fn rtc_clear_flag(void)
 *  \brief Function to clear rtc flag
 *
 *  \return void
 */
void rtc_clear_flag(void);

#endif /* RTC_H_ */
