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

#define SPD_A_TEAM      (1300) // for A-Team
#define SPD_AXEL_F      (1600) // for Axel F
#define SPD_TETRIS      (1100) // for Tetris

/* Full tones */
#define SOUND_NOTE_1_F(speed)      (speed / 1)
#define SOUND_NOTE_2_F(speed)      (speed / 2)
#define SOUND_NOTE_4_F(speed)      (speed / 4)
#define SOUND_NOTE_8_F(speed)      (speed / 8)
#define SOUND_NOTE_16_F(speed)     (speed / 16)
#define SOUND_NOTE_32_F(speed)     (speed / 32)
#define SOUND_NOTE_64_F(speed)     (speed / 64)

/* Long tones (dotted) */
#define SOUND_NOTE_1_L(speed)      (speed * 3 / 2 / 1)
#define SOUND_NOTE_2_L(speed)      (speed * 3 / 2 / 2)
#define SOUND_NOTE_4_L(speed)      (speed * 3 / 2 / 4)
#define SOUND_NOTE_8_L(speed)      (speed * 3 / 2 / 8)
#define SOUND_NOTE_16_L(speed)     (speed * 3 / 2 / 16)
#define SOUND_NOTE_32_L(speed)     (speed * 3 / 2 / 32)
#define SOUND_NOTE_64_L(speed)     (speed * 3 / 2 / 64)

/* Very Long tones (double dotted) */
#define SOUND_NOTE_1_LL(speed)     (speed * 7 / 4 / 1)
#define SOUND_NOTE_2_LL(speed)     (speed * 7 / 4 / 2)
#define SOUND_NOTE_4_LL(speed)     (speed * 7 / 4 / 4)
#define SOUND_NOTE_8_LL(speed)     (speed * 7 / 4 / 8)
#define SOUND_NOTE_16_LL(speed)    (speed * 7 / 4 / 16)
#define SOUND_NOTE_32_LL(speed)    (speed * 7 / 4 / 32)
#define SOUND_NOTE_64_LL(speed)    (speed * 7 / 4 / 64)

/* Short tones */
#define SOUND_NOTE_1_S(speed)      (speed * 3 / 4 / 1)
#define SOUND_NOTE_2_S(speed)      (speed * 3 / 4 / 2)
#define SOUND_NOTE_4_S(speed)      (speed * 3 / 4 / 4)
#define SOUND_NOTE_8_S(speed)      (speed * 3 / 4 / 8)
#define SOUND_NOTE_16_S(speed)     (speed * 3 / 4 / 16)
#define SOUND_NOTE_32_S(speed)     (speed * 3 / 4 / 32)
#define SOUND_NOTE_64_S(speed)     (speed * 3 / 4 / 64)

/* Rests corresponding to short tones */
#define SOUND_NOTE_1_R(speed)      (speed * 1 / 4 / 1)
#define SOUND_NOTE_2_R(speed)      (speed * 1 / 4 / 2)
#define SOUND_NOTE_4_R(speed)      (speed * 1 / 4 / 4)
#define SOUND_NOTE_8_R(speed)      (speed * 1 / 4 / 8)
#define SOUND_NOTE_16_R(speed)     (speed * 1 / 4 / 16)
#define SOUND_NOTE_32_R(speed)     (speed * 1 / 4 / 32)
#define SOUND_NOTE_64_R(speed)     (speed * 1 / 4 / 64)

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
