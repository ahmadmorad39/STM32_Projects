/*
 * rtos_mutex.h
 *
 *  Created on: Mar 1, 2025
 *      Author: ahmad
 */

#ifndef INC_RTOS_MUTEX_H_
#define INC_RTOS_MUTEX_H_

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
 * @addtogroup rtos_mutex
 * @{
 */

/**
 * @defgroup rtos_mutex_exported_typedefs
 * @{
 */

/**
 * @brief      Mutex type
 * @note
 * @see
 */
typedef struct
{
  uint32_t mutexValue;            /**< Mutex value */
  RTOS_list_t waitingList;        /**< Waiting list of the mutex */
} RTOS_mutex_t;

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_exported_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_exported_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_exported_functions
 * @{
 */

void RTOS_mutexCreate(RTOS_mutex_t * pMutex, uint32_t initialValue);
void RTOS_SVC_mutexCreate(RTOS_mutex_t * pMutex, uint32_t initialValue);

uint32_t RTOS_mutexLock(RTOS_mutex_t * pMutex, uint32_t waitFlag);
uint32_t RTOS_SVC_mutexLock(RTOS_mutex_t * pMutex, uint32_t waitFlag);

void RTOS_mutexRelease(RTOS_mutex_t * pMutex);
void RTOS_SVC_mutexRelease(RTOS_mutex_t * pMutex);

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


#endif /* INC_RTOS_MUTEX_H_ */
