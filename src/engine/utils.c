/*
 * utils.c
 *
 *  Created on: 31 mar 2025
 *      Author: psobek
 */

#include "utils.h"

extern QueueHandle_t usartQueue;

void pchar(char c)
{
    // GPIO_SetBits(GPIOD, GPIO_Pin_15);
    if (xQueueSendToBack(usartQueue, (void *)&c, (TickType_t)10) != pdPASS)
    {
    }
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
