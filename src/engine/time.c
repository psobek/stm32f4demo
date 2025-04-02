/*
 * time.c
 *
 *  Created on: 2 apr 2025
 *      Author: psobek
 */

#include "time.h"

static uint32_t mod1000 = 0;
static uint64_t uptime_sec = 0;

void systick(void)
{
    mod1000++;
    if (mod1000 == 1000)
    {
        uptime_sec++;
        mod1000 = 0;
    }
}

void delay_ms(uint32_t milliseconds)
{
    uint64_t ms_start = uptime_sec * 1000 + mod1000;
    uint64_t ms_end = ms_start + milliseconds;

    while (uptime_sec * 1000 + mod1000 < ms_end)
    {
    }
}