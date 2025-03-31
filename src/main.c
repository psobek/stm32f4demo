/*
 * main.c
 *
 *  Created on: 15 lis 2015
 *      Author: psobek
 */

#include "main.h"

void init_clock(void)
{
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	ErrorStatus HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if (HSEStartUpStatus != SUCCESS)
		while (1)
			;
	// ensure that PLL is disabled first
	RCC_PLLCmd(DISABLE);
	RCC_PLLConfig(RCC_PLLSource_HSE, PLLM_DIV, PLLN_MUL, PLLQ_DIV, PLLP_DIV);
	RCC_PLLCmd(ENABLE);
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		;
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_ClockSecuritySystemCmd(ENABLE);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while (RCC_GetSYSCLKSource() != 0x08)
		;
}

void init(void)
{
	init_clock();
}

int main(void)
{
	init();
	while (1)
	{
	}
	return 0;
}
