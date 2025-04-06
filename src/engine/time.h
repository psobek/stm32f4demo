/*
 * time.h
 *
 *  Created on: 2 apr 2025
 *      Author: psobek
 */

#ifndef TIME_H_
#define TIME_H_

#include <stdint.h>

#include "appConfig.h"

void systick(void); // systick function should run in 1000Hz interrupt
uint32_t get_hf_ticks(void);

#endif /* TIME_H_ */