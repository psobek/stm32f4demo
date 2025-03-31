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
