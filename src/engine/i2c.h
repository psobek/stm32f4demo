/*
 * i2c.h
 *
 *  Created on: 1 apr 2025
 *      Author: psobek
 */

#ifndef I2C_H_
#define I2C_H_

#define I2C_LONG_TIMEOUT 0x300

#include <stdint.h>
#include "stm32f4xx_i2c.h"

uint8_t i2c_write_bytes(uint8_t i2c_address, uint8_t *buf, int buflen);
uint8_t i2c_read_bytes(uint8_t i2c_address, uint8_t *buf, int buflen);

#endif /* I2C_H_ */