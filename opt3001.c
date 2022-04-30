/*
 * opt3001.c
 *
 *  Created on: Mar 14, 2021
 *      Author: younghyunkim
 */

#include "opt3001.h"
#include "math.h"

/******************************************************************************
 * Initialize the opt3001 ambient light sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/

void opt3001_init(void)
{
    // Initialize OPT3001
    // i2c_write_16(OPT3001_SLAVE_ADDRESS, 0, 0x06);
    i2c_write_16(OPT3001_SLAVE_ADDRESS, CONFIG_REG, 0xC410);
}

/******************************************************************************
 * Returns the current ambient light in lux
 *  ******************************************************************************/
float opt3001_read_lux(void)
{
    // Read the Result register of OPT3001 and convert into Lux, then return.
    enum light { DARK,
        MEDIUM,
        BRIGHT };
    uint16_t res = i2c_read_16(OPT3001_SLAVE_ADDRESS, RESULT_REG);
    return .01 * ((res & 0xFFF) << (res >> 12));
}
