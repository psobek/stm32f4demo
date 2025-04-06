/*
 * th06.c
 *
 *  Created on: 1 apr 2025
 *      Author: psobek
 */

#include "th06.h"

static uint8_t th06_error_flag = 0;

void th06_cycle(void)
{
    // measure RH
    th06_send_command(TH06_CONVERT_HUMIDITY_NO_HOLD);
    // delay_ms(25);
    uint32_t h = th06_read_humidity();
    debug("Humidity:");
    debugint(h);
    // measure T
    th06_send_command(TH06_CONVERT_TEMPERATURE_NO_HOLD);
    // delay_ms(25);
    uint32_t t = th06_read_temp();
    debug("Temperature:");
    debugint(t);

    if (th06_error_flag)
        th06_reset_comm();
}

void th06_send_command(uint8_t command)
{
    uint8_t buf[1];
    buf[0] = command;
    uint8_t res = 0;
    res = i2c_write_bytes(TH06_I2C_ADDRESS, buf, sizeof(buf));
    if (res != 0)
    {
        th06_error_flag = 1;
        debug("Error reading value from I2C");
    }
}

uint16_t th06_read_value(void)
{
    uint8_t buf[2];
    uint8_t res = 0;
    res = i2c_read_bytes(TH06_I2C_ADDRESS, buf, sizeof(buf));
    if (res != 0)
    {
        th06_error_flag = 1;
        debug("Error reading value from I2C");
        return 0;
    }
    return ((uint16_t)buf[0] << 8 | buf[1]);
}

uint16_t th06_read_temp(void)
{
    uint16_t val = th06_read_value();
    uint32_t result = (17572 * val) / 65536 - 4685;
    return (uint16_t)result;
}

uint16_t th06_read_humidity(void)
{
    uint32_t val = th06_read_value();
    uint32_t result = ((125 * val) / 65536) - 6;
    return (uint16_t)result;
}

void th06_reset_comm(void)
{
    uint32_t flags = ((uint32_t)I2C1->SR1) << 16 | I2C1->SR2;
    debughex(flags);
    I2C_ClearFlag(I2C1, 0x20FF);
    I2C_GenerateSTART(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);
    // I2C_AcknowledgeConfig(I2C1, DISABLE);
    flags = ((uint32_t)I2C1->SR1) << 16 | I2C1->SR2;
    debughex(flags);
    I2C_GenerateSTOP(I2C1, DISABLE);
    // I2C_ClearFlag(I2C1, I2C_FLAG);
}