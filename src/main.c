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

void init_timers(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	// Timer1 release reset
	TIM_DeInit(TIM1);

	// Set timer period (1/f_TC1) sec
	TIM_TimeBaseInitStruct.TIM_Prescaler = TIM1_PRESC;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = TIM1_PERIOD;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);

	// Clear update interrupt bit
	TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
	// Enable update interrupt
	TIM_ITConfig(TIM1, TIM_FLAG_Update, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// Enable timer counting
	TIM_Cmd(TIM1, ENABLE);
}

void init_gpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_DeInit(GPIOD);
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void init_usart(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_DeInit(GPIOC);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	USART_DeInit(USART3);
	USART_InitTypeDef USART_InitStructure;
	USART_StructInit(&USART_InitStructure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = 1;
	USART_InitStructure.USART_WordLength = 8;
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);
}

void init(void)
{
	init_clock();
	init_gpio();
	init_timers();
	init_usart();
}

int main(void)
{
	init();

	debug("Reboot");
	debug("CPU Frequency:");
	debugint(CPU_FREQ);

	while (1)
	{
	}
	return 0;
}
