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

typedef union {
    struct {
        uint8_t high;   /*!< High byte */
        uint8_t low;    /*!< Low byte */
    } bytefield;        /*!< Nibbles */
    uint16_t value;     /*!< Byte */
} voltage_t;

static voltage_t voltage_host;
static uint8_t current_host;
static uint8_t error_drv;


void drv8301_init(void) {
    /* test orientation of bitfields */
    test_bitfield_t test_bitfield;      /* testvariable */
    test_bitfield.byte = 0x00;
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
    voltage_host.value = 0;
    current_host = 0;
    error_drv = 0x00;
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
    reg.raw = 0x00;
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

    return;
}

void drv8301_set_gate_current(uint16_t current_mA) {
    /* local variables */
    drv8301_reg_t reg;                              /* temporary register */
    reg.raw = 0x00;
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

    return;
}

void drv8301_set_oc_adj_set(uint16_t voltage_mV) {
    /* local variables */
    drv8301_reg_t reg;                              /* temporary register */
    reg.raw = 0x00;
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

    return;
}

void setVoltage_to_DRV_high(uint8_t voltage)
{
	voltage_host.bytefield.high = voltage;
}

void setVoltage_to_DRV_low(uint8_t voltage)
{
	voltage_host.bytefield.low = voltage;
}

void setCurrent_to_DRV(uint8_t current)
{
	current_host = current;
}

uint8_t getErrors_form_DRV(void)
{
	return error_drv;
}

void update_ErrorCode(void)
{
	drv8301_reg_t reg1, reg2;
	reg1 = drv8301_read_register(DRV8301_ADDR_STATUS1);
	if( reg1.raw & 0x003F)
		error_drv |= 0x01;
	else
		error_drv &= ~0x01;
	
	if( reg1.status1.reg_read.otw )
		error_drv |= 0x02;
	else
		error_drv &= ~0x02;
	
	if( reg1.status1.reg_read.otsd )
		error_drv |= 0x04;
	else
		error_drv &= ~0x04;
	
	if( reg1.status1.reg_read.pvdd_uv )
		error_drv |= 0x08;
	else
		error_drv &= ~0x08;
	
	if( reg1.status1.reg_read.gvdd_uv )
		error_drv |= 0x10;
	else
		error_drv &= ~0x10;
	
	reg2 = drv8301_read_register(DRV8301_ADDR_STATUS2);
	
	if( reg2.status2.reg_read.gvdd_ov )
		error_drv |= 0x20;
	else
		error_drv &= ~0x20;
	
}

void handleDrv(void)
{
	if( voltage_host.value != 0)
	{
		drv8301_set_oc_adj_set(voltage_host.value);
		voltage_host.value = 0;
	}
	if( current_host != 0)
	{
		drv8301_set_gate_current((uint16_t)current_host * 10);
		current_host = 0;
	}
}
