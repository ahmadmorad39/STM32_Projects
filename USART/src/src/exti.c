/*
 * exti.c
 *
 *  Created on: Feb 18, 2025
 *      Author: ahmad
 */
/* Includes */
#include "inc/exti.h"


/**
 * @brief   Push button EXITI initialization function
 * @note    On-board push button connected to PA0,
 * 			so it can use only EXTI0
 */
void EXTI_Init_PB()
{
	/* Enable SYSCFG clock*/
	RCC->APB2ENR |= RCC_APB2LPENR_SYSCFGLPEN;

	/* Map PA0 to EXT0*/
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;

	/* Enable rising edge trigger */
	EXTI->FTSR &= ~(EXTI_FTSR_TR0);

	/* Enable interrupt line*/
	EXTI->IMR |= EXTI_IMR_MR0;

	/* Enable event line */
	EXTI->IMR |= EXTI_EMR_MR0;



}
