/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         Global definitions for the whole project.
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          13.09.2013
 *
 * \b Language:   Ansi-C \n\n
 * \b Target:     MC Car \n
 *
 * $Id: platform.h 485 2013-09-22 06:02:55Z zajost $
 *--------------------------------------------------------------------
 */
#ifndef PLATFORM_H
#define PLATFORM_H

/* Include the derivative-specific header file */
#include <mc9s08jm60.h>
#include <hidef.h> /* for EnableInterrupts macro */
#include "errors.h"

#define BUSCLOCK              24000000  // Hz

#define BLUETOOTH_NAME        "MC-Car xyz"


#define DEBUG_LED             0

#if (DEBUG_LED == 1)
#define DebugLed1On()                   (PTDD_PTDD2=1) // Led rear
#define DebugLed1Off()                  (PTDD_PTDD2=0) // Led rear
#define DebugLed2On()                   (PTFD_PTFD1=0) // Led front left red
#define DebugLed2Off()                  (PTFD_PTFD1=1) // Led front left red
#else
#define DebugLed1On()
#define DebugLed1Off() 
#define DebugLed2On()
#define DebugLed2Off()
#endif

// switch on led for debug purposes
#define OnEnterIfrFrontISR()            DebugLed1On()
#define OnEnterIfrRearISR()             DebugLed1On()
#define OnEnterMotorBoosterISR()        DebugLed1On()
#define OnEnterSci1RxD()                DebugLed1On()
#define OnEnterSci1TxD()                DebugLed1On()
#define OnEnterSci2RxD()                DebugLed1On()
#define OnEnterSci2TxD()                DebugLed1On()
#define OnEnterSoundISRduration()       DebugLed1On()
#define OnEnterSoundISRfreq()           DebugLed1On()
#define OnEnterLedISR()                 DebugLed1On()

// switch off led for debug purposes
#define OnExitIfrFrontISR()             DebugLed1Off()
#define OnExitIfrRearISR()              DebugLed1Off()
#define OnExitMotorBoosterISR()         DebugLed1Off()
#define OnExitSci1RxD()                 DebugLed1Off()
#define OnExitSci1TxD()                 DebugLed1Off()
#define OnExitSci2RxD()                 DebugLed1Off()
#define OnExitSci2TxD()                 DebugLed1Off()
#define OnExitSoundISRduration()        DebugLed1Off()
#define OnExitSoundISRfreq()            DebugLed1Off()
#define OnExitLedISR()                  DebugLed1Off()


#define _Stop asm ( stop; )
  /*!< Macro to enter stop modes, STOPE bit in SOPT1 register must be set prior to executing this macro */

#define _Wait asm ( wait; )
  /*!< Macro to enter wait mode */

typedef struct {
    unsigned int  stackFree;                    /* Number of free bytes on the stack                            */
    unsigned int  stackUsed;                    /* Number of bytes used on the stack                            */
} tStackData;

void ClearStack(void);
tStackData CheckStackSize(void);


// Use Project Properties => HCS08 Compiler => Type Sizes to adapt to target
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned int uint16;
typedef signed int int16;
typedef unsigned long uint32;
typedef signed long int32;
typedef char bool;

#define TRUE                1
#define FALSE               0

#endif /* PLATFORM_H_ */
