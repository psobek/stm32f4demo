/*
 * irq.c
 *
 *  Created on: 15 lis 2015
 *      Author: psobek
 */

#include "time.h"
#include "irq.h"

void TIM1_Interrupt_Handler(void)
{
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);

    systick();
}