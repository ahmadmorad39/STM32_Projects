/*
 * rtos.h
 *
 *  Created on: Feb 22, 2025
 *      Author: ahmad
 */

#ifndef INC_RTOS_H_
#define INC_RTOS_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <stddef.h>
#include <string.h>
#include "stm32f4xx.h"
#include "inc/itm.h"
#include "rtos_config.h"
#include "rtos_list.h"
#include "rtos_thread.h"
#include "rtos_mutex.h"
#include "rtos_semaphore.h"
#include "rtos_mailbox.h"

/**
 * @addtogroup stm32_examples
 * @{
 */

/**
 * @addtogroup rtos
 * @{
 */

/**
 * @defgroup rtos_exported_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_exported_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_exported_macros
 * @{
 */

/**
 * @brief   Memory word access
 */
#define MEM32_ADDRESS(ADDRESS) (*((volatile unsigned long *)(ADDRESS)))

/**
 * @}
 */

/**
 * @defgroup rtos_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_exported_functions
 * @{
 */

void RTOS_init(void);
void RTOS_schedulerStart(void);
void RTOS_SVC_schedulerStart(void);
void RTOS_SVC_Handler_main(uint32_t * svc_args);
void RTOS_SysTick_Handler(void);

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif


#endif /* INC_RTOS_H_ */
