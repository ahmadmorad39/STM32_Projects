/*
 * rtos_mutex.c
 *
 *  Created on: Mar 1, 2025
 *      Author: ahmad
 */


/* Includes */
#include "rtos.h"

/**
 * @addtogroup stm32_examples
 * @{
 */

/**
 * @defgroup rtos_mutex
 * @brief
 * @{
 */

/**
 * @defgroup rtos_mutex_private_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_private_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_private_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_private_variables
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_private_function_prototypes
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_private_functions
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_exported_functions
 * @{
 */

/**
 * @brief   Mutex create
 * @note
 * @param   RTOS_mutex_t *
 * @retval  None
 */
void RTOS_mutexCreate(RTOS_mutex_t * pMutex, uint32_t initialValue)
{
  /* Check input parameters */
  ASSERT(NULL != pMutex);
  ASSERT((initialValue == 0) || (initialValue == 1));

  /* Initialize mutex waiting list */
  RTOS_listInit(&pMutex->waitingList);

  /* Initialize mutex value */
  pMutex->mutexValue = initialValue;
}

/**
 * @brief   Mutex lock
 * @note
 * @param   RTOS_mutex_t *, uint32_t
 * @retval  uint32_t
 */
uint32_t RTOS_mutexLock(RTOS_mutex_t * pMutex, uint32_t waitFlag)
{
  /* Check input parameters */
  ASSERT(NULL != pMutex);
  ASSERT((0 == waitFlag) || (1 == waitFlag));

  /* Mutex lock return status */
  uint32_t returnStatus = 0;

  /* Pointer to the current running thread */
  RTOS_thread_t * pRunningThread;

  /* Variable to terminate the while loop */
  uint32_t terminate = 0;

  /* Try to lock the mutex */
  while(1 != terminate)
  {
    /* Check mutex value, note in ARMv7-M exceptions automatically clear the
     * exclusive state in the local monitor, no need to use CLREX instruction */
    if(1 == __LDREXW(&pMutex->mutexValue))
    {
      /* Mutex is free, locked it */
      if(0 == __STREXW(0, &pMutex->mutexValue))
      {
        /* Required before accessing protected resource */
        __DMB();

        /* Mutex is locked */
        returnStatus = 1;

        /* Mutex lock succeeded, terminate the loop */
        terminate = 1;
      }
      else
      {
        /* Mutex can not be locked, do nothing */
      }
    }
    else
    {
      /* Mutex is locked, terminate the loop */
      terminate = 1;
    }
  }

  /* Check waiting flag and return status */
  if((1 == waitFlag) && (1 != returnStatus))
  {
    /* Get current running thread */
    pRunningThread = RTOS_threadGetRunning();

    /* Remove current thread from ready list */
    RTOS_listRemove(&pRunningThread->item);

    /* Put current thread into the waiting list */
    RTOS_listInsert(&pMutex->waitingList, &pRunningThread->item);

    /* Trigger context switch, set PendSV to pending */
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

    /* Return to SVC as indication of context switch */
    returnStatus = 2;
  }
  else
  {
    /* No blocking required, do nothing */
  }

  /* Return */
  return returnStatus;
}

/**
 * @brief   Mutex release
 * @note
 * @param   RTOS_mutex_t *
 * @retval  None
 */
void RTOS_mutexRelease(RTOS_mutex_t * pMutex)
{
  /* Check input parameters */
  ASSERT(NULL != pMutex);

  /* Pointer to the unblocked thread */
  RTOS_thread_t * pThread;

  /* Required before releasing protected resource */
  __DMB();

  /* Release the mutex */
  pMutex->mutexValue = 1;

  /* Get highest priority waiting thread, the one next from the end */
  if(0 < pMutex->waitingList.numOfItems)
  {
    pThread = pMutex->waitingList.listEnd.pNext->pThread;

    /* Check returned thread */
    ASSERT(NULL != pThread);

    /* Remove the returned thread item from the waiting list */
    RTOS_listRemove(&pThread->item);

    /* Add the returned thread into ready list */
    RTOS_threadAddToReadyList(pThread);
  }
  else
  {
    /* No threads are waiting, do nothing */
  }
}

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
