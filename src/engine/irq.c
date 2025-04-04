/*
 * irq.c
 *
 *  Created on: 15 lis 2015
 *      Author: psobek
 */

#include "time.h"
#include "irq.h"

extern SemaphoreHandle_t usartSemaphore;

void TIM1_Interrupt_Handler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    systick();
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void USART3_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    // Does not need to check what is the source of interrupt cause
    // only TC interrupt enabled
    USART_ClearFlag(USART3, USART_FLAG_TC);
    // give the usart3 semaphore to allow the agent to write to USART3 again
    if (usartSemaphore != NULL)
    {
        xSemaphoreGiveFromISR(usartSemaphore, &xHigherPriorityTaskWoken);
    }
    // yield from ISR, whenever it is required to
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}