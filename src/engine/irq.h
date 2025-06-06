/*
 * irq.h
 *
 *  Created on: 15 lis 2015
 *      Author: psobek
 */

#ifndef IRQ_H_
#define IRQ_H_

#include <stdint.h>
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"

#include "appConfig.h"

void TIM1_Interrupt_Handler(void);

#endif /* IRQ_H_ */