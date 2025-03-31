#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>

#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"

void pchar(char c);
void debughex(uint32_t data);
void debugint(uint32_t data);
void debug(char *debugstring);

#endif /* UTILS_H_ */
