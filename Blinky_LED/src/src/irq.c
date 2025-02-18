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
