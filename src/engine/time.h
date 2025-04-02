/*
 * time.h
 *
 *  Created on: 2 apr 2025
 *      Author: psobek
 */

#ifndef TIME_H_
#define TIME_H_

#include <stdint.h>

void systick(void); // systick function should run in 1000Hz interrupt
void delay_ms(uint32_t milliseconds);
#endif /* TIME_H_ */