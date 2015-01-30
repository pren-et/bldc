/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file drv8301.c
 * \brief Driver for three phase pre-driver drv8301 from Texas Instruments
 * \author pren-et
 * 
 */

#include "drv8301.h"

/* Definition of necessary functions provided by a SPI module later */
void spi_write(uint8_t *data) { return; }
void spi_read(uint8_t *data) { return; }

void drv8301_init(void) {
    /*! test orientation of bitfields */
    test_bitfield_t test_bitfield;      /*!< testvariable */
    test_bitfield.bitfield.low = 0x01;  /*!< write testvalue to lower nibble */
    if (test_bitfield.byte != 0x01) {   /*!< test if lower nibble has been written */
        while (1) {                     /*!< loop to stop executing if wrong order */
            /* Hey Programmer */
            /* It seems that your compiler uses a */
            /* different order for bitfields than mine. */
            /* If you still want to use this library, */
            /* change ,if possible, the order of bitfields in */
            /* your compiler or in this library! */
        }
    }
    
    return;
}

void drv8301_send_cmd(uint8_t cmd, uint8_t read, uint8_t *data) {
    /*! local variables */
    uint8_t i;          /*!< variable to count number of sent bits */
    spi_write(&cmd);    /*!< send command */
    if (read) {         /*!< check if reading data is needed */
        for (i = 0; i < (DRV8301_REG_LEN - 1); i++) {
            spi_read(data++);   /*!< read data */
        }
    } else {
        for (i = 0; i < (DRV8301_REG_LEN - 1); i++) {
            spi_write(data++);  /*!< write data */
        }
    }
}
