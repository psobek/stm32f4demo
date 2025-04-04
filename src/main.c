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
		//
	}
}

int main(void)
{
	init();

	SystemCoreClockUpdate();
	usartQueue = xQueueCreate(1024, 1);
	vSemaphoreCreateBinary(usartSemaphore);
	xTaskCreate(TaskBlink1, "Task1", 128, NULL, 1, NULL);
	xTaskCreate(TaskBlink2, "Task2", 128, NULL, 1, NULL);
	xTaskCreate(TaskBlink3, "Task3", 128, NULL, 1, NULL);
	xTaskCreate(TaskBlink4, "Task4", 128, NULL, 1, NULL);
	xTaskCreate(UsartAgentTask, "USARTAgent", 128, NULL, 3, NULL);
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
