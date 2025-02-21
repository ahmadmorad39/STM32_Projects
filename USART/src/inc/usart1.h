/*
 * usart1.h
 *
 *  Created on: Feb 21, 2025
 *      Author: ahmad
 */

#ifndef INC_USART1_H_
#define INC_USART1_H_

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f429i_discovery.h"

void USART1_IRQ_Callback(void);
void USART1_Process(void);
void USART1_Enable(void);
void USART1_Init(void);
void USART1_GPIO_Config(void);


#endif /* INC_USART1_H_ */
