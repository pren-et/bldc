/*!
 *  ____  ____  _____ _   _       _____ _____
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |
 * |  __/|  _ <| |___| |\  |_____| |___  | |
 * |_|   |_| \_\_____|_| \_|     |_____| |_|
 *
 * \file  sound.c
 * \brief Motor control
 * \author pren-et
 *
 */

#include "sound.h"

static const uint16_t midi_decode[] = {
    /*
    Cnt_value   MIDI Frequency [Hz] */
        0, /*     0  rest */
    21646, /*     1  8.662 */
    20431, /*     2  9.177 */
    19285, /*     3  9.723 */
    18202, /*     4  10.30 */
    17181, /*     5  10.91 */
    16216, /*     6  11.56 */
    15306, /*     7  12.25 */
    14447, /*     8  12.98 */
    13636, /*     9  13.75 */
    12871, /*    10  14.57 */
    12149, /*    11  15.43 */
    11467, /*    12  16.35 */
    10823, /*    13  17.32 */
    10216, /*    14  18.35 */
     9642, /*    15  19.45 */
     9101, /*    16  20.60 */
     8590, /*    17  21.83 */
     8108, /*    18  23.12 */
     7653, /*    19  24.50 */
     7224, /*    20  25.96 */
     6818, /*    21  27.50 */
     6436, /*    22  29.14 */
     6074, /*    23  30.87 */
     5733, /*    24  32.70 */
     5412, /*    25  34.65 */
     5108, /*    26  36.71 */
     4821, /*    27  38.89 */
     4551, /*    28  41.20 */
     4295, /*    29  43.65 */
     4054, /*    30  46.25 */
     3827, /*    31  49.00 */
     3612, /*    32  51.91 */
     3409, /*    33  55.00 */
     3218, /*    34  58.27 */
     3037, /*    35  61.74 */
     2867, /*    36  65.41 */
     2706, /*    37  69.30 */
     2554, /*    38  73.42 */
     2411, /*    39  77.78 */
     2275, /*    40  82.41 */
     2148, /*    41  87.31 */
     2027, /*    42  92.50 */
     1913, /*    43  98.00 */
     1806, /*    44  103.8 */
     1705, /*    45  110.0 */
     1609, /*    46  116.5 */
     1519, /*    47  123.5 */
     1433, /*    48  130.8 */
     1353, /*    49  138.6 */
     1277, /*    50  146.8 */
     1205, /*    51  155.6 */
     1138, /*    52  164.8 */
     1074, /*    53  174.6 */
     1014, /*    54  185.0 */
      957, /*    55  196.0 */
      903, /*    56  207.7 */
      852, /*    57  220.0 */
      804, /*    58  233.1 */
      759, /*    59  246.9 */
      717, /*    60  261.6 */
      676, /*    61  277.2 */
      638, /*    62  293.7 */
      603, /*    63  311.1 */
      569, /*    64  329.6 */
      537, /*    65  349.2 */
      507, /*    66  370.0 */
      478, /*    67  392.0 */
      451, /*    68  415.3 */
      426, /*    69  440.0 */
      402, /*    70  466.2 */
      380, /*    71  494.8 */
      358, /*    72  523.3 */
      338, /*    73  554.4 */
      319, /*    74  587.3 */
      301, /*    75  622.3 */
      284, /*    76  659.3 */
      268, /*    77  698.5 */
      253, /*    78  740.0 */
      239, /*    79  784.0 */
      226, /*    80  830.6 */
      213, /*    81  880.0 */
      201, /*    82  932.3 */
      190, /*    83  987.8 */
      179, /*    84   1047 */
      169, /*    85   1109 */
      160, /*    86   1175 */
      151, /*    87   1245 */
      142, /*    88   1319 */
      134, /*    89   1397 */
      127, /*    90   1480 */
      120, /*    91   1568 */
      113, /*    92   1661 */
      107, /*    93   1760 */
      101, /*    94   1865 */
       95, /*    95   1976 */
       90, /*    96   2093 */
       85, /*    97   2217 */
       80, /*    98   2349 */
       75, /*    99   2489 */
       71, /*   100   2637 */
       67, /*   101   2794 */
       63, /*   102   2960 */
       60, /*   103   3136 */
       56, /*   104   3322 */
       53, /*   105   3520 */
       50, /*   106   3729 */
       47, /*   107   3951 */
       45, /*   108   4186 */
       42, /*   109   4435 */
       40, /*   110   4698 */
       38, /*   111   4978 */
       36, /*   112   5274 */
       34, /*   113   5588 */
       32, /*   114   5920 */
       30, /*   115   6272 */
       28, /*   116   6645 */
       27, /*   117   7040 */
       25, /*   118   7459 */
       24, /*   119   7902 */
       22, /*   120   8372 */
       21, /*   121   8870 */
       20, /*   122   9397 */
       19, /*   123   9956 */
       18, /*   124  10548 */
};

static const sound_t *melody_ptr;

static const sound_t melody_a_team[] = {
        /*****************
        ** A-Team theme **
        *****************/
        /*
        pitch, time */
        {  0,  SOUND_NOTE_8_F},
        //----------------------------------------------------------------------
        { 78,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 73,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 78,  SOUND_NOTE_8_F},
        { 78,  SOUND_NOTE_2_S},
        { 78,  SOUND_NOTE_2_R},
        //......................................................................
        { 71,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 73,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 66,  SOUND_NOTE_8_F},
        { 66,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        {  0,  SOUND_NOTE_8_F},
        { 70,  SOUND_NOTE_16_S},
        {  0,  SOUND_NOTE_16_R},
        { 73,  SOUND_NOTE_16_S},
        {  0,  SOUND_NOTE_16_R},
        //......................................................................
        { 78,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 73,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 80,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 78,  SOUND_NOTE_8_F},
        { 78,  SOUND_NOTE_2_S},
        {  0,  SOUND_NOTE_2_R},
        //......................................................................
        { 76,  SOUND_NOTE_8_L},
        {  0,  SOUND_NOTE_16_F},
        { 75,  SOUND_NOTE_16_S},
        {  0,  SOUND_NOTE_16_R},
        { 73,  SOUND_NOTE_16_S},
        {  0,  SOUND_NOTE_16_R},
        { 71,  SOUND_NOTE_16_F},
        { 71,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 73,  SOUND_NOTE_2_S},
        {  0,  SOUND_NOTE_2_R},
        //......................................................................
        //======================================================================
        //......................................................................
        // End of melody -> do not change!
        {  0,    0},
};

static const sound_t melody_axel_f[] = {
        /********************************
        ** Harold Faltermeyer - Axel F **
        ********************************/
        /*
        pitch, time */
        {  0,  SOUND_NOTE_8_F},
        //----------------------------------------------------------------------
        { 65,  SOUND_NOTE_8_F},
        {  0,  SOUND_NOTE_8_F},
        { 68,  SOUND_NOTE_8_L},
        {  0,  SOUND_NOTE_8_R},
        { 65,  SOUND_NOTE_16_F},
        //......................................................................
        { 65,  SOUND_NOTE_16_S},
        {  0,  SOUND_NOTE_16_R},
        // probably rest here to separate tones
        { 65,  SOUND_NOTE_16_S},
        {  0,  SOUND_NOTE_16_R},
        { 70,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 65,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 63,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        //----------------------------------------------------------------------
        { 65,  SOUND_NOTE_8_F},
        {  0,  SOUND_NOTE_8_F},
        { 72,  SOUND_NOTE_8_L},
        {  0,  SOUND_NOTE_8_R},
        { 65,  SOUND_NOTE_16_F},
        //......................................................................
        { 65,  SOUND_NOTE_16_S},
        {  0,  SOUND_NOTE_16_R},
        // probably rest here to separate tones
        { 65,  SOUND_NOTE_16_S},
        {  0,  SOUND_NOTE_16_R},
        { 73,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 68,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        //----------------------------------------------------------------------
        { 65,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 77,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 65,  SOUND_NOTE_16_S},
        {  0,  SOUND_NOTE_16_R},
        { 63,  SOUND_NOTE_16_F},
        //......................................................................
        { 63,  SOUND_NOTE_16_S},
        {  0,  SOUND_NOTE_16_R},
        // probably rest here to separate tones
        { 63,  SOUND_NOTE_16_S},
        {  0,  SOUND_NOTE_16_R},
        { 60,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 67,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 65,  SOUND_NOTE_8_F},
        //----------------------------------------------------------------------
        { 65,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        //......................................................................
        {  0,  SOUND_NOTE_4_F},
        //......................................................................
        //======================================================================
        //......................................................................
        // End of melody -> do not change!
        {  0,    0},
};

static const sound_t melody_tetris[] = {
        /*****************
        ** Tetris theme **
        *****************/
        /*
        pitch, time */
        {  0,  SOUND_NOTE_8_F},
        //----------------------------------------------------------------------
        { 76,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 71,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 74,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 71,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        //......................................................................
        { 69,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 69,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 76,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 74,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        //......................................................................
        { 71,  SOUND_NOTE_4_L},
        {  0,  SOUND_NOTE_8_F},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 74,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 76,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        //......................................................................
        { 72,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 69,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 69,  SOUND_NOTE_2_S},
        {  0,  SOUND_NOTE_2_R},
        //----------------------------------------------------------------------
        {  0,  SOUND_NOTE_8_F},
        { 74,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 77,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 81,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 79,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 77,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        //......................................................................
        { 76,  SOUND_NOTE_4_L},
        {  0,  SOUND_NOTE_8_F},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 76,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 74,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        //......................................................................
        { 71,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 71,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 74,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 76,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        //......................................................................
        { 72,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 69,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 69,  SOUND_NOTE_2_S},
        {  0,  SOUND_NOTE_2_R},
        //----------------------------------------------------------------------
        { 76,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 71,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 74,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 71,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        //......................................................................
        { 69,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 69,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 76,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 74,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        //......................................................................
        { 71,  SOUND_NOTE_4_L},
        {  0,  SOUND_NOTE_8_F},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 74,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 76,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        //......................................................................
        { 72,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 69,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 69,  SOUND_NOTE_2_S},
        {  0,  SOUND_NOTE_2_R},
        //----------------------------------------------------------------------
        {  0,  SOUND_NOTE_8_F},
        { 74,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 77,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 81,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 79,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 77,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        //......................................................................
        { 76,  SOUND_NOTE_4_L},
        {  0,  SOUND_NOTE_8_F},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 76,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 74,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        //......................................................................
        { 71,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 71,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 72,  SOUND_NOTE_8_S},
        {  0,  SOUND_NOTE_8_R},
        { 74,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 76,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        //......................................................................
        { 72,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 69,  SOUND_NOTE_4_S},
        {  0,  SOUND_NOTE_4_R},
        { 69,  SOUND_NOTE_2_S},
        {  0,  SOUND_NOTE_2_R},
        //......................................................................
        //======================================================================
        //......................................................................
        // End of melody -> do not change!
        {  0,    0},
};

uint16_t sound_interval;
uint16_t tone_cnt;
uint8_t  sound_playing;

void sound_init(void) {
	set_sound(1);
    tone_cnt        = 0;
    sound_interval  = midi2timer(melody_ptr[tone_cnt].pitch);
    sound_playing   = 0;
};

void sound_start(void) {
    tone_cnt        = 0;
    sound_interval  = midi2timer(melody_ptr[tone_cnt].pitch);
    sound_playing   = 1;
};

uint16_t midi2timer(uint8_t midi) {
    if (midi < sizeof(midi_decode)) {
        return midi_decode[midi];
    }
    return 0;
}

uint16_t sound_get_time(void) {
    if (tone_cnt < sizeof(*melody_ptr)/sizeof(sound_t)) {
        return melody_ptr[tone_cnt].time;
    }
    else {
        return 100;
    }
}

uint16_t sound_get_interval(void) {
    return sound_interval;
}

uint8_t sound_finished(void) {
    if (sound_playing) {
        return 0;
    }
    else {
        return 1;
    }
}

void sound_task(void) {
    if (sound_playing) {
        if (tone_cnt < sizeof(*melody_ptr)/sizeof(sound_t)) {
            tone_cnt++;
            sound_interval = midi2timer(melody_ptr[tone_cnt].pitch);
        }
        else {
            sound_interval = 0;
            sound_playing = 0;
            motor_set_mode(MOTOR_MODE_BRAKE);
        }
    }
    else {
        sound_interval = 0;
    }
    return;
}

void set_sound(uint8_t sound_track)
{
	switch(sound_track)
	{
	case 1:
		melody_ptr = melody_axel_f;
		break;
	case 2:
		melody_ptr = melody_tetris;
		break;
	case 3:
		melody_ptr = melody_a_team;
		break;
	}
}
