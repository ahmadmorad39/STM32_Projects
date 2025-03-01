/*
 * memcpy.h
 *
 *  Created on: Feb 18, 2025
 *      Author: ahmad
 */

#ifndef INC_MEMCPY_H_
#define INC_MEMCPY_H_

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/**
 * @brief  On-board LEDs
 */
typedef enum
{
	RETURN_STATUS_OK,
	RETURN_STATUS_NOT_OK
} ReturnStatus_Type;

ReturnStatus_Type memcpy32(const uint32_t *src, uint32_t *dst, const uint32_t size);

#endif /* INC_MEMCPY_H_ */
