/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file  rtc.c
 * \brief
 * \author pren-et
 *
 */

#include "rtc.h"

rtc_flag_t flag;

void rtc_init_flag(void) {
    flag = RTC_NONE;
}

rtc_flag_t rtc_get_flag(void) {
    return flag;
}

void rtc_set_flag(void) {
    flag = RTC_PENDING;
}

void rtc_clear_flag(void) {
    flag = RTC_NONE;
}

rtc_flag_t rtc_get_clear_flag(void) {
    rtc_flag_t tempflag;
    DisableInterrupts;
    tempflag = flag;
    flag = RTC_NONE;
    EnableInterrupts;
    return tempflag;
}
