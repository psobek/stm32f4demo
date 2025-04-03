/*
 * main.c
 *
 *  Created on: 15 lis 2015
 *      Author: psobek
 */

#include "main.h"

void TaskBlink1(void *pvParameters)
{
	while (1)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void TaskBlink2(void *pvParameters)
{
	while (1)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		vTaskDelay(500 / portTICK_PERIOD_MS);
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}

void TaskBlink3(void *pvParameters)
{
	while (1)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		vTaskDelay(250 / portTICK_PERIOD_MS);
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		vTaskDelay(250 / portTICK_PERIOD_MS);
	}
}

void TaskBlink4(void *pvParameters)
{
	while (1)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		vTaskDelay(125 / portTICK_PERIOD_MS);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		vTaskDelay(125 / portTICK_PERIOD_MS);
	}
}

int main(void)
{
	init();
	debug("Reboot");
	debug("CPU Frequency:");
	SystemCoreClockUpdate();
	debugint(SystemCoreClock);
	xTaskCreate(TaskBlink1, "Task1", 128, NULL, 1, NULL);
	xTaskCreate(TaskBlink2, "Task2", 128, NULL, 2, NULL);
	xTaskCreate(TaskBlink3, "Task3", 128, NULL, 3, NULL);
	xTaskCreate(TaskBlink4, "Task4", 128, NULL, 4, NULL);
	while (1)
	{
		vTaskStartScheduler();
	}
	return 0;
}
