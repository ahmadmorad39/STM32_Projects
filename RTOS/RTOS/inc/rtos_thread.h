/*
 * rtos_thread.h
 *
 *  Created on: Feb 22, 2025
 *      Author: ahmad
 */

#ifndef INC_RTOS_THREAD_H_
#define INC_RTOS_THREAD_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */

/**
 * @addtogroup rtos
 * @{
 */

/**
 * @addtogroup rtos_thread
 * @{
 */

/**
 * @defgroup rtos_thread_exported_typedefs
 * @{
 */

/**
 * @brief      Thread type
 * @note
 * @see
 */
typedef struct thread_t
{
  uint32_t pStackPointer;        /**< Stack pointer */
  uint32_t priority;             /**< Thread priority */
  uint32_t threadID;             /**< Used for trace */
  RTOS_listItem_t item;          /**< List item of this thread */
} RTOS_thread_t;

/**
 * @brief      Thread stack type
 * @note
 * @see
 */
typedef struct
{
  uint64_t stack[THREAD_STACK_SIZE];  /**< Thread stack */
} RTOS_stack_t;

/**
 * @}
 */

/**
 * @defgroup rtos_thread_exported_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_thread_exported_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_thread_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_thread_exported_functions
 * @{
 */

void RTOS_threadCreate(RTOS_thread_t * pThread, RTOS_stack_t * pStack,
    uint32_t priority, void * pFunction);
void RTOS_SVC_threadCreate(RTOS_thread_t * pThread, RTOS_stack_t * pStack,
    uint32_t priority, void * pFunction);

void RTOS_threadInitLists(void);
RTOS_thread_t * RTOS_threadGetRunning(void);
void RTOS_threadSwitchRunning(void);
void RTOS_threadAddToReadyList(RTOS_thread_t * pThread);

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


#endif /* INC_RTOS_THREAD_H_ */
