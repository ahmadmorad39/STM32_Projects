/*
 * irq.c
 *
 *  Created on: Feb 18, 2025
 *      Author: ahmad
 */

/* Includes */
#include "inc/irq.h"


void IRQ_Init(void)
{
	/* Set priority group 3
	 * bits[3:0] are the sub-priority
	 * bits[7:4] are the pre-emt priority
	 */
	NVIC_SetPriorityGrouping(3);

	/* Set priority levels*/
	NVIC_SetPriority(GREEN_LED_OFF_IRQ, 1);
	NVIC_SetPriority(RED_LED_OFF_IRQ, 2);

	NVIC_SetPriority(GREEN_LED_ON_IRQ, 3);
	NVIC_SetPriority(RED_LED_ON_IRQ, 4);

	/* Enable interrupts at NVIC */
	NVIC_EnableIRQ(GREEN_LED_OFF_IRQ);
	NVIC_EnableIRQ(RED_LED_OFF_IRQ);

	NVIC_EnableIRQ(GREEN_LED_ON_IRQ);
	NVIC_EnableIRQ(RED_LED_ON_IRQ);
}

void NVIC_Init1(void)
{
	/* Set priority group 3
	 * bits[3:0] are the sub-priority
	 * bits[7:4] are the pre-emt priority
	 */
	NVIC_SetPriorityGrouping(3);

	/* Set priority levels*/
	NVIC_SetPriority(SysTick_IRQn, 0);
	NVIC_SetPriority(EXTI0_IRQn, 1);
	NVIC_SetPriority(DMA2_Stream0_IRQn, 2);

	/* Enable interrupts at NVIC */
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}

