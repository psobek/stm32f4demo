/*
 * time.c
 *
 *  Created on: 2 apr 2025
 *      Author: psobek
 */

#include "time.h"

static uint32_t modTimer1 = 0;
static uint64_t uptime_sec = 0;
static uint32_t hf_ticks = 0;

void systick(void)
{
    modTimer1++;
    hf_ticks++;
    if (modTimer1 == TIM1_FREQ)
    {
        uptime_sec++;
        modTimer1 = 0;
    }
}

uint32_t get_hf_ticks(void)
{
    return hf_ticks;
}
