/* ###################################################################
**     Filename    : Events.h
**     Project     : ProcessorExpert
**     Processor   : MC9S08JM60CLHE
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2015-03-20, 16:21, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "SM1.h"
#include "SS1.h"


void SS1_OnRxChar(void);
/*
** ===================================================================
**     Event       :  SS1_OnRxChar (module Events)
**
**     Component   :  SS1 [SynchroSlave]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**         
**         [ Version specific information for Freescale HCS08 and RS08
**         and HCS12 and HCS12X and ColdFireV1 derivatives ] 
**         The <Bidirectional mode> property setting doesn't affect
**         this event.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SS1_OnTxChar(void);
/*
** ===================================================================
**     Event       :  SS1_OnTxChar (module Events)
**
**     Component   :  SS1 [SynchroSlave]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SS1_OnTxEmptyChar(void);
/*
** ===================================================================
**     Event       :  SS1_OnTxEmptyChar (module Events)
**
**     Component   :  SS1 [SynchroSlave]
**     Description :
**         The event is called when an Empty character is sent
**         automaticaly if no user data is in buffer (see <Empty
**         character> property for details about empty character).
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**         [ Version specific information for Freescale HCS08 and
**         ColdFireV1 derivatives ] 
**         This event is also called after initialization and after
**         calling Enable method.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SS1_OnError(void);
/*
** ===================================================================
**     Event       :  SS1_OnError (module Events)
**
**     Component   :  SS1 [SynchroSlave]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SM1_OnRxChar(void);
/*
** ===================================================================
**     Event       :  SM1_OnRxChar (module Events)
**
**     Component   :  SM1 [SynchroMaster]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**         
**         [ Version specific information for Freescale HCS08 and RS08
**         and HCS12 and HCS12X and ColdFireV1 derivatives ] 
**         The <Bidirectional mode> property setting doesn't affect
**         this event. For more information please see <Bidirectional
**         mode behavior> paragraph.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SM1_OnTxChar(void);
/*
** ===================================================================
**     Event       :  SM1_OnTxChar (module Events)
**
**     Component   :  SM1 [SynchroMaster]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SM1_OnError(void);
/*
** ===================================================================
**     Event       :  SM1_OnError (module Events)
**
**     Component   :  SM1 [SynchroMaster]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.2 [05.07]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
