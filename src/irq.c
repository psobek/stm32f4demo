/*
 * irq.c
 *
 *  Created on: 15 lis 2015
 *      Author: psobek
 */

#include "irq.h"

static uint32_t counter = 0;
static uint8_t led_state = 0;
uint8_t oled_action_flag = 0;

void toggle_led()
{
    if (led_state == 1)
    {
        led_state = 0;
        GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    }
    else
    {
        led_state = 1;
        GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    }
}

void TIM1_Interrupt_Handler(void)
{
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    counter++;
    if (counter == TIM1_FREQ)
    {
        counter = 0;
        oled_action_flag = 1; // set oled action flag once per second
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