/*
 * utils.c
 *
 *  Created on: 31 mar 2025
 *      Author: psobek
 */

#include "utils.h"

void led_on(void)
{
    GPIOD->ODR |= GPIO_Pin_15;
}

void led_off(void)
{
    GPIOD->ODR &= ~GPIO_Pin_15;
}

void pchar(char c)
{
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
    {
    }
    led_on();
    USART_SendData(USART3, c);
    led_off();
}

void debughex(uint32_t data)
{
    char buf[100];
    snprintf(buf, sizeof(buf), "0x%08lX", data);
    debug(buf);
}

void debugint(uint32_t data)
{
    char buf[100];
    snprintf(buf, sizeof(buf), "%ld", data);
    debug(buf);
}

void debug(char *debugstring)
{
    while (*debugstring != '\0')
    {
        pchar(*debugstring++);
    }
    pchar('\r');
    pchar('\n');
}
