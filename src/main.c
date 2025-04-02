/*
 * main.c
 *
 *  Created on: 15 lis 2015
 *      Author: psobek
 */

#include "main.h"

int main(void)
{
	init();

	debug("Reboot");
	debug("CPU Frequency:");
	debugint(CPU_FREQ);

	while (1)
	{
		th06_cycle();
		delay_ms(5000);
	}
	return 0;
}
