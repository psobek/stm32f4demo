/*
 * main.c
 *
 *  Created on: 15 lis 2015
 *      Author: psobek
 */

#include "main.h"

QueueHandle_t usartQueue;
SemaphoreHandle_t usartSemaphore = NULL;

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

void UsartAgentTask(void *pvParameters)
{
	while (1)
	{
		char c[1];
		// take one item from queue and put it to USART.
		if (xSemaphoreTake(usartSemaphore, (TickType_t)10) == pdTRUE)
		{
			if (xQueueReceive(usartQueue, c, (TickType_t)10) == pdPASS)
			{
				// if data is to be sent, we should put the char into the USART DR
				// and let TXE IRQ to give the semaphore
				USART_SendData(USART3, *c);
			}
			else
			{
				// if no data is to be sent, let's give the semaphore,
				// in order to execute the check again
				xSemaphoreGive(usartSemaphore);
			}
		}
	}
}

void HeavyTask(void *pvParameters)
{
	while (1)
	{
		int y = 1;
		for (int i = 0; i < 10000; i++)
		{
			y *= (i + 1) / 5;
		}
		// debugint(y);
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}

void StatsTask(void *pvParameters)
{
	char buffer[500];
	while (1)
	{
		// print stats roughly every 5 seconds
		vTaskDelay(5000 / portTICK_PERIOD_MS);
		vTaskGetRunTimeStatistics(buffer, sizeof(buffer));
		debug(buffer);
	}
}

int main(void)
{
	init();

	SystemCoreClockUpdate();
	usartQueue = xQueueCreate(1024, 1);
	vSemaphoreCreateBinary(usartSemaphore);
	xTaskCreate(TaskBlink1, "LED1", 128, NULL, 3, NULL);
	xTaskCreate(TaskBlink2, "LED2", 128, NULL, 3, NULL);
	xTaskCreate(TaskBlink3, "LED3", 128, NULL, 3, NULL);
	xTaskCreate(TaskBlink4, "LED4", 128, NULL, 3, NULL);
	xTaskCreate(UsartAgentTask, "USARTAgent", 128, NULL, 3, NULL);
	xTaskCreate(StatsTask, "Stats", 1128, NULL, 4, NULL);
	xTaskCreate(HeavyTask, "Heavy", 128, NULL, 2, NULL);
	debug("Reboot");
	debug("CPU Frequency:");
	debugint(SystemCoreClock);
	//    main loop
	while (1)
	{
		vTaskStartScheduler();
	}
	return 0;
}
