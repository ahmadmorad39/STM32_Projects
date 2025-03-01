/*
 * irq.h
 *
 *  Created on: Feb 18, 2025
 *      Author: ahmad
 */

#ifndef INC_IRQ_H_
#define INC_IRQ_H_

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

enum MyIRQs_e
{
	GREEN_LED_ON_IRQ = EXTI0_IRQn,
	GREEN_LED_OFF_IRQ = EXTI1_IRQn,
	RED_LED_ON_IRQ = EXTI2_IRQn,
	RED_LED_OFF_IRQ = EXTI3_IRQn
}MyIRQs;

void IRQ_Init(void);
void NVIC_Init1(void);


#endif /* INC_IRQ_H_ */
