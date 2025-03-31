/*
 * appConfig.h
 *
 *  Created on: 15 lis 2015
 *      Author: psobek
 */

#ifndef CONF_APPCONFIG_H_
#define CONF_APPCONFIG_H_

#define APPCONFIG_CLK_SRC PLL

#if (APPCONFIG_CLK_SRC == PLL)
// define params for RCC_PLLConfig:
// RCC_PLLConfig(RCC_PLLSource_HSE, PLLM_DIV, PLLN_MUL, PLLQ_DIV, PLLP_DIV);
#define PLLM_DIV (4)  // 8MHz/4   = 2 MHz
#define PLLN_MUL (72) // 2MHz*72  = 144 MHz
#define PLLP_DIV (2)  // 144MHz/2 = 72 MHz - main clock
#define PLLQ_DIV (3)  // 144MHz/3 = 48 MHz - USB/SDIO Clock
#define PLL_FREQ (((HSE_VALUE / PLLM_DIV) * PLLN_MUL) / PLLP_DIV)
#define CPU_FREQ (PLL_FREQ)
#elif (APPCONFIG_CLK_SRC == HSI)
#define CPU_FREQ (HSI_VALUE)
#elif (APPCONFIG_CLK_SRC == HSE)
#define CPU_FREQ (HSI_VALUE)
#endif

#define TIM1_RESOLUTION (100000)
#define TIM1_FREQ (1000)
#define TIM1_PERIOD ((TIM1_RESOLUTION / TIM1_FREQ) - 1)
#define TIM1_PRESC (CPU_FREQ / TIM1_RESOLUTION)

#endif /* CONF_APPCONFIG_H_ */
