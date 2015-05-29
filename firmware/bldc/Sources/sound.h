/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file  sound.h
 * \brief Motor control
 * \author pren-et
 *
 */
#ifndef SOUND_H_
#define SOUND_H_

#include "platform.h"
#include "hardware.h"
#include "team.h"
#include "motor.h"

/*! \struct sound_t
 *  \brief Type for storing sound
 */
typedef struct {
    uint8_t     pitch;
    uint16_t    time;
} sound_t;

/*! \fn void sound_init(void)
 *  \brief initializes sound module
 *
 *  \return void
 */
void sound_init(void);

/*! \fn void sound_start(void)
 *  \brief starts sound module
 *
 *  \return void
 */
void sound_start(void);

/*! \fn uint16_t sound_get_time(void)
 *  \brief returns time of current tone
 *
 *  \return time of current tone
 */
uint16_t sound_get_time(void);

/*! \fn uint16_t sound_get_interval(void)
 *  \brief returns interval of current tone
 *
 *  \return interval of current tone
 */
uint16_t sound_get_interval(void);

/*! \fn uint16_t midi2timer(uint8_t midi)
 *  \brief convert midi number to value written to timer module
 *
 *  \param  midi midi number
 *  \return value to write to timer module
 */
uint16_t midi2timer(uint8_t midi);


/*! \fn uint8_t sound_finished(void)
 *  \brief return if sound has reached end
 *
 *  \return time for given tone in milliseconds
 */
uint8_t sound_finished(void);

/*! \fn void sound_task(void)
 *  \brief task for sound control
 *
 *  \return void
 */
void sound_task(void);

#endif /* SOUND_H_ */
