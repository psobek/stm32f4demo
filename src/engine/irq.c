/*
 * irq.c
 *
 *  Created on: 15 lis 2015
 *      Author: psobek
 */

#include "time.h"
#include "irq.h"

static uint32_t counter = 0;
static uint8_t led_state = 0;

void toggle_led()
{
    if (led_state == 1)
    {
        led_state = 0;
        GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
    }
    else
    {
        led_state = 1;
        GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
    }
}

void TIM1_Interrupt_Handler(void)
{
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);

    systick();
    counter++;
    if (counter == TIM1_FREQ)
    {
        counter = 0;
    }

    if (counter == 0)
    {
        toggle_led();
    }
    if (counter == 10)
    {
        toggle_led();
    }
}