/*
 * @file    gpio.c
 * @author  Ahmad Murad
 * @date    Feb 18, 2025
 *
 *@brief   some examples on how to use STM32 GPIOs
 *
 */




/* Includes */
#include "inc/gpio.h"

/**
 * @brief   on-board LEDs initialization function
 * @note    EVAL_GREEN_LED -> PG13
 */
void GPIO_Init_LED(Led_Type led)
{
	/* Check LED type, please */
	switch (led)
	{
		case EVAL_GREEN_LED:

			/* Enable port G clock */
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;

			/* Select output mode */
			GPIOG->MODER |= GPIO_MODER_MODER13_0;

			/* select output type push-pull */
			GPIOG->OTYPER &= ~(GPIO_OTYPER_OT_13);

			/* Select output speed very high */
			GPIOG->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR13_0 | GPIO_OSPEEDER_OSPEEDR13_1);

			/* Enable SYSCFG clock */
			RCC->APB2ENR |= RCC_APB2LPENR_SYSCFGLPEN;

			/* Enable compensation cell */
			SYSCFG->CMPCR |= SYSCFG_CMPCR_CMP_PD;

			/* Wait till compensation cell is ready */
			while((SYSCFG->CMPCR & SYSCFG_CMPCR_READY) != SYSCFG_CMPCR_READY);

			/* Select no pull */
			GPIOG->PUPDR &= ~(GPIO_PUPDR_PUPDR13);

			break;
		default:
			break;
	}
}


void GPIO_TurnON_LED(Led_Type led)
{
	switch (led)
	{
		case EVAL_GREEN_LED:
			GPIOG->BSRRL = GPIO_BSRR_BS_13;
			break;
		case EVAL_GREEN_LED_BITBAND:
			GREEN_LED_BITBAND = 1;
			break;
		default:
			break;
	}
}


void GPIO_TurnOFF_LED(Led_Type led)
{
	switch (led)
	{
		case EVAL_GREEN_LED:
			GPIOG->BSRRH = GPIO_BSRR_BS_13;
			break;
		case EVAL_GREEN_LED_BITBAND:
			GREEN_LED_BITBAND = 0;
			break;
		default:
			break;
	}
}
