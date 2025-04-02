/*
 * th06.h
 *
 *  Created on: 1 apr 2025
 *      Author: psobek
 */

#ifndef TH06_H_
#define TH06_H_

#include <stdint.h>

#include "i2c.h"
#include "time.h"
#include "utils.h"

#define TH06_I2C_ADDRESS (0x40 << 1)
#define TH06_CONVERT_HUMIDITY_NO_HOLD 0xF5
#define TH06_CONVERT_TEMPERATURE_NO_HOLD 0xF3

void th06_cycle(void);
void th06_send_command(uint8_t command);
uint16_t th06_read_value(void);
uint16_t th06_read_temp(void);
uint16_t th06_read_humidity(void);
void th06_reset_comm(void);
#endif /* TH06_H_ */
