/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file drv8301.c
 * \brief Driver for three phase pre-driver DRV8301 from Texas Instruments
 * \author pren-et
 * 
 */

#include "drv8301.h"
#include "spi_drv.h"

typedef enum {
	NOTHING_NECESSARY,
    WRITING_NECESSARY,
    READING_NECESSARY
} drv8301_action_necessary;

drv8301_action_necessary action_necesary;
drv8301_reg_t shaddowReg[DRV8301_REG_COUNT];


/* Definition of necessary functions provided by a SPI module later */
/*! \fn uint16_t spi_drv_read_write(uint16_t data)
 *  \todo Define in SPI Module
 */

void drv8301_init(void) {
    /* test orientation of bitfields */
    test_bitfield_t test_bitfield;      /* testvariable */
    test_bitfield.bitfield.low = 0x01;  /* write testvalue to lower nibble */
    if (test_bitfield.byte != 0x01) {   /* test if lower nibble has been written */
        while (1) {                     /* loop to stop executing if wrong order */
            /* Hey Programmer */
            /* It seems that your compiler uses a */
            /* different order for bitfields than mine. */
            /* If you still want to use this library, */
            /* change ,if possible, the order of bitfields in */
            /* your compiler or in this library! */
        }
    }
    action_necesary = READING_NECESSARY;
    PTBD |= EN_GATE;
    return;
}

void drv8301_disable(void)
{
    PTBD &= ~EN_GATE;
}

drv8301_reg_t drv8301_read_register(drv8301_addr_t address) {
    /* local variables */
    drv8301_reg_t reg;                      /* temporary register */
    reg.data_write.data = 0x00;             /* empty dummy data */
    reg.data_write.addr = address;          /* address of register */
    reg.data_write.rw   = DRV8301_RW_R;     /* read register */

    /* read register */
    (void) spi_drv_read_write(reg.raw);
    reg.raw = spi_drv_read_write(reg.raw);

    /* return register */
    return reg;
}

void drv8301_write_register(drv8301_reg_t reg) {
    if (reg.data_write.addr == DRV8301_ADDR_CONTROL1 || 
        reg.data_write.addr == DRV8301_ADDR_CONTROL2) { /* check if register is writable */
        reg.data_write.rw   = DRV8301_RW_W;                 /* write register */

        /* write register */
        (void)spi_drv_read_write(reg.raw);
    }
    action_necesary = READING_NECESSARY;

    return;
}

void drv8301_set_gate_current(uint16_t current_mA) {
    /* local variables */
    drv8301_reg_t reg;                              /* temporary register */
    reg.data_write.data = 0x00;                     /* empty dummy data */
    reg.data_write.addr = DRV8301_ADDR_CONTROL1;    /* address of status1 register */
    reg.data_write.rw   = DRV8301_RW_R;             /* read register */

    /* read register */
    (void) spi_drv_read_write(reg.raw);
    reg.raw = spi_drv_read_write(reg.raw);

    /* set gate current */
    if (current_mA <= 250) {        /* 0.25A */
        reg.control1.reg_write.gate_current = DRV8301_GATE_CURRENT_0_25A;
    }
    else if (current_mA <= 700) {   /* 0.7A */
        reg.control1.reg_write.gate_current = DRV8301_GATE_CURRENT_0_7A;
    }
    else {                          /* 1.7A */
        reg.control1.reg_write.gate_current = DRV8301_GATE_CURRENT_1_7A;
    }

    /* write register back */
    reg.data_write.rw   = DRV8301_RW_W;             /* write register */
    (void)spi_drv_read_write(reg.raw);

    action_necesary = READING_NECESSARY;
    return;
}

void drv8301_set_oc_adj_set(uint16_t voltage_mV) {
    /* local variables */
    drv8301_reg_t reg;                              /* temporary register */
    reg.data_write.data = 0x00;                     /* empty dummy data */
    reg.data_write.addr = DRV8301_ADDR_CONTROL1;    /* address of status1 register */
    reg.data_write.rw   = DRV8301_RW_R;             /* read register */

    /* read register */
    (void)spi_drv_read_write(reg.raw);
    reg.raw = spi_drv_read_write(reg.raw);

    /* set overcurrent threshold value */
    if (voltage_mV <=   60) {       /* 0.060V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_060V;
    }
    else if (voltage_mV <=   68) {  /* 0.068V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_068V;
    }
    else if (voltage_mV <=   76) {  /* 0.076V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_076V;
    }
    else if (voltage_mV <=   86) {  /* 0.086V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_086V;
    }
    else if (voltage_mV <=   97) {  /* 0.097V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_097V;
    }
    else if (voltage_mV <=  109) {  /* 0.109V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_109V;
    }
    else if (voltage_mV <=  123) {  /* 0.123V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_123V;
    }
    else if (voltage_mV <=  138) {  /* 0.138V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_138V;
    }
    else if (voltage_mV <=  155) {  /* 0.155V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_155V;
    }
    else if (voltage_mV <=  175) {  /* 0.175V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_175V;
    }
    else if (voltage_mV <=  197) {  /* 0.197V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_197V;
    }
    else if (voltage_mV <=  222) {  /* 0.222V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_222V;
    }
    else if (voltage_mV <=  250) {  /* 0.250V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_250V;
    }
    else if (voltage_mV <=  282) {  /* 0.282V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_282V;
    }
    else if (voltage_mV <=  317) {  /* 0.317V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_317V;
    }
    else if (voltage_mV <=  358) {  /* 0.358V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_358V;
    }
    else if (voltage_mV <=  403) {  /* 0.403V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_403V;
    }
    else if (voltage_mV <=  454) {  /* 0.454V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_454V;
    }
    else if (voltage_mV <=  511) {  /* 0.511V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_511V;
    }
    else if (voltage_mV <=  576) {  /* 0.576V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_576V;
    }
    else if (voltage_mV <=  648) {  /* 0.648V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_648V;
    }
    else if (voltage_mV <=  730) {  /* 0.730V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_730V;
    }
    else if (voltage_mV <=  822) {  /* 0.822V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_822V;
    }
    else if (voltage_mV <=  926) {  /* 0.926V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_0_926V;
    }
    else if (voltage_mV <= 1046) {  /* 1.046V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_1_046V;
    }
    else if (voltage_mV <= 1175) {  /* 1.175V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_1_175V;
    }
    else if (voltage_mV <= 1324) {  /* 1.324V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_1_324V;
    }
    else if (voltage_mV <= 1491) {  /* 1.491V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_1_491V;
    }
    else if (voltage_mV <= 1679) {  /* 1.679V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_1_679V;
    }
    else if (voltage_mV <= 1892) {  /* 1.892V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_1_892V;
    }
    else if (voltage_mV <= 2131) {  /* 2.131V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_2_131V;
    }
    else {                          /* 2.400V */
        reg.control1.reg_write.oc_adj_set = DRV8301_OC_ADJ_SET_2_400V;
    }

    /* write register back */
    reg.data_write.rw   = DRV8301_RW_W;             /* write register */
    (void)spi_drv_read_write(reg.raw);

    action_necesary = READING_NECESSARY;
    return;
}

void handleDrv(void)
{
	if( action_necesary == NOTHING_NECESSARY )       /* no action necessary */
		return;
	else
	{	
		uint8_t i;
		drv8301_reg_t reg; 	
		if( action_necesary == READING_NECESSARY )
		{
			for( i=0 ; i<DRV8301_REG_COUNT ; i++)
			{
				reg.data_write.data = 0x00;                  /* empty dummy data */
				reg.data_write.addr = i;  /* address of register */
				reg.data_write.rw   = DRV8301_RW_R;          /* read register */
				(void) spi_drv_read_write(reg.raw);
				shaddowReg[i].raw = spi_drv_read_write(reg.raw);	
			}
		}
		else if( action_necesary == WRITING_NECESSARY )
		{
			for( i=2 ; i<DRV8301_REG_COUNT ; i++)
			{
				reg = shaddowReg[i];	
				reg.data_write.addr = i;
				reg.data_write.rw = DRV8301_RW_W;
				(void) spi_drv_read_write(reg.raw);
			}
		}
		action_necesary = NOTHING_NECESSARY;
	}
}

uint16_t drv8301_get_register(drv8301_addr_t address) 
{
	return shaddowReg[address].raw;
}

void drv8301_set_config(drv8301_addr_t addr, uint16_t value)
{
	shaddowReg[addr].raw = value;
	action_necesary = WRITING_NECESSARY;
}
