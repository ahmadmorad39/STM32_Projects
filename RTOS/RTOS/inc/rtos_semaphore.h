/*
 * rtos_semaphore.h
 *
 *  Created on: Mar 1, 2025
 *      Author: ahmad
 */

#ifndef INC_RTOS_SEMAPHORE_H_
#define INC_RTOS_SEMAPHORE_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */

/**
 * @addtogroup stm32_examples
 * @{
 */

/**
 * @addtogroup rtos_semaphore
 * @{
 */

/**
 * @defgroup rtos_semaphore_exported_typedefs
 * @{
 */

/**
 * @brief      Semaphore type
 * @note
 * @see
 */
typedef struct
{
  uint32_t semaphoreValue;        /**< Semaphore counter value */
  RTOS_list_t waitingList;        /**< Waiting list of the semaphore */
} RTOS_semaphore_t;

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_exported_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_exported_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_exported_functions
 * @{
 */

void RTOS_semaphoreCreate(RTOS_semaphore_t * pSemaphore, uint32_t initialValue);
void RTOS_SVC_semaphoreCreate(RTOS_semaphore_t * pSemaphore, uint32_t initialValue);

uint32_t RTOS_semaphoreTake(RTOS_semaphore_t * pSemaphore, uint32_t waitFlag);
uint32_t RTOS_SVC_semaphoreTake(RTOS_semaphore_t * pSemaphore, uint32_t waitFlag);

void RTOS_semaphoreGive(RTOS_semaphore_t * pSemaphore);
void RTOS_SVC_semaphoreGive(RTOS_semaphore_t * pSemaphore);

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


#endif /* INC_RTOS_SEMAPHORE_H_ */
