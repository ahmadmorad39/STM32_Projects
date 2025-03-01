/*
 * SysTick.h
 *
 *  Created on: Feb 18, 2025
 *      Author: ahmad
 */

#ifndef INC_SYSTICK_H_
#define INC_SYSTICK_H_

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

void SysTick_Delay(uint32_t wait_time_ms);
void SysTick_Init(void);

#endif /* INC_SYSTICK_H_ */
