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

/* Full tones */
//#define SOUND_NOTE_1_F      (1600) // for Axel F
//#define SOUND_NOTE_1_F      (1100) // for Tetris
#define SOUND_NOTE_1_F      (1300) // for A-Team
#define SOUND_NOTE_2_F      (SOUND_NOTE_1_F / 2)
#define SOUND_NOTE_4_F      (SOUND_NOTE_1_F / 4)
#define SOUND_NOTE_8_F      (SOUND_NOTE_1_F / 8)
#define SOUND_NOTE_16_F     (SOUND_NOTE_1_F / 16)
#define SOUND_NOTE_32_F     (SOUND_NOTE_1_F / 32)
#define SOUND_NOTE_64_F     (SOUND_NOTE_1_F / 64)

/* Long tones (dotted) */
#define SOUND_NOTE_1_L      (SOUND_NOTE_1_F * 3 / 2)
#define SOUND_NOTE_2_L      (SOUND_NOTE_1_L / 2)
#define SOUND_NOTE_4_L      (SOUND_NOTE_1_L / 4)
#define SOUND_NOTE_8_L      (SOUND_NOTE_1_L / 8)
#define SOUND_NOTE_16_L     (SOUND_NOTE_1_L / 16)
#define SOUND_NOTE_32_L     (SOUND_NOTE_1_L / 32)
#define SOUND_NOTE_64_L     (SOUND_NOTE_1_L / 64)

/* Very Long tones (double dotted) */
#define SOUND_NOTE_1_LL     (SOUND_NOTE_1_F * 7 / 4)
#define SOUND_NOTE_2_LL     (SOUND_NOTE_1_LL / 2)
#define SOUND_NOTE_4_LL     (SOUND_NOTE_1_LL / 4)
#define SOUND_NOTE_8_LL     (SOUND_NOTE_1_LL / 8)
#define SOUND_NOTE_16_LL    (SOUND_NOTE_1_LL / 16)
#define SOUND_NOTE_32_LL    (SOUND_NOTE_1_LL / 32)
#define SOUND_NOTE_64_LL    (SOUND_NOTE_1_LL / 64)

/* Short tones */
#define SOUND_NOTE_1_S      (SOUND_NOTE_1_F * 3 / 4)
#define SOUND_NOTE_2_S      (SOUND_NOTE_1_S / 2)
#define SOUND_NOTE_4_S      (SOUND_NOTE_1_S / 4)
#define SOUND_NOTE_8_S      (SOUND_NOTE_1_S / 8)
#define SOUND_NOTE_16_S     (SOUND_NOTE_1_S / 16)
#define SOUND_NOTE_32_S     (SOUND_NOTE_1_S / 32)
#define SOUND_NOTE_64_S     (SOUND_NOTE_1_S / 64)

/* Rests corresponding to short tones */
#define SOUND_NOTE_1_R      (SOUND_NOTE_1_F - SOUND_NOTE_1_S)
#define SOUND_NOTE_2_R      (SOUND_NOTE_1_R / 2)
#define SOUND_NOTE_4_R      (SOUND_NOTE_1_R / 4)
#define SOUND_NOTE_8_R      (SOUND_NOTE_1_R / 8)
#define SOUND_NOTE_16_R     (SOUND_NOTE_1_R / 16)
#define SOUND_NOTE_32_R     (SOUND_NOTE_1_R / 32)
#define SOUND_NOTE_64_R     (SOUND_NOTE_1_R / 64)

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

/*! \fn void set_sound(void)
 *  \brief task to choose a sound track
 *
 *  \return void
 */
void set_sound(uint8_t sound_track);

#endif /* SOUND_H_ */
