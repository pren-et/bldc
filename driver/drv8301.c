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
uint16_t spi_read_write(uint16_t data) { return 0; }

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

drv8301_reg_t drv8301_read_register(drv8301_addr_t address) {
    /*! local variables */
    drv8301_reg_t reg;                      /*!< temporary register */
    reg.data_write.data = 0x00;             /*!< empty dummy data */
    reg.data_write.addr = address;          /*!< address of register */
    reg.data_write.rw   = DRV8301_RW_R;     /*!< read register */

    /*! read register */
    reg.raw = spi_read_write(reg.raw);

    /*! return register */
    return reg;
}

void drv8301_write_register(drv8301_reg_t reg) {
    if (reg.data_write.addr == DRV8301_ADDR_CONTROL1 || 
        reg.data_write.addr == DRV8301_ADDR_CONTROL2) { /*!< check if register is writable */
        reg.data_write.rw   = DRV8301_RW_W;                 /*!< write register */

        /*! write register */
        spi_read_write(reg.raw);
    }

    return;
}
