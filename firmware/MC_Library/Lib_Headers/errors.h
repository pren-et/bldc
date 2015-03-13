/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         MC-Car errorcodes
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          13.09.2013
 *
 * \b Language:   Ansi-C \n\n
 * \b Target:     MC Car \n
 *
 * $Id: errors.h 479 2013-09-13 13:50:51Z zajost $
 *--------------------------------------------------------------------
 */
#ifndef ERRORS_H
#define ERRORS_H


typedef enum 
{
  EC_SUCCESS = 0,
  
  EC_I2C_NO_ANSWER = 1,     // No answer from the i2c device during address calling
  EC_I2C_NAK = 2,           // i2c device answered but NAK received during the transmission
  
  
  EC_INVALID_CMD,           // Command Line parser
  EC_BLUETOOTH = 3,
  
  EC_UNKNOWN_ERROR = 255,
  
  
  EC_NOT_IMPLEMENTED = 99
  
} tError;


#endif /* ERRORS_H */
