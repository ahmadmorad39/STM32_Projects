/*
 * dma.h
 *
 *  Created on: Feb 18, 2025
 *      Author: ahmad
 */

#ifndef INC_DMA_H_
#define INC_DMA_H_

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

void DMA2_Stream0_Init();
void DMA2_Stream0_Set_Address(const uint32_t *src,const uint32_t *dst,const uint32_t size);
void DMA2_Stream0_Enable();

#endif /* INC_DMA_H_ */
