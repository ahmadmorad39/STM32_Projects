/*
 * rtos_semaphore.c
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
 * @defgroup rtos_semaphore
 * @brief
 * @{
 */

/**
 * @defgroup rtos_semaphore_private_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_private_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_private_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_private_variables
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_private_function_prototypes
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_private_functions
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_exported_functions
 * @{
 */

/**
 * @brief   Semaphore create
 * @note
 * @param   RTOS_semaphore_t *
 * @retval  None
 */
void RTOS_semaphoreCreate(RTOS_semaphore_t * pSemaphore, uint32_t initialValue)
{
  /* Check input parameters */
  ASSERT(NULL != pSemaphore);

  /* Initialize semaphore waiting list */
  RTOS_listInit(&pSemaphore->waitingList);

  /* Initialize semaphore value */
  pSemaphore->semaphoreValue = initialValue;
}

/**
 * @brief   Semaphore take
 * @note
 * @param   RTOS_semaphore_t *, uint32_t
 * @retval  uint32_t
 */
uint32_t RTOS_semaphoreTake(RTOS_semaphore_t * pSemaphore, uint32_t waitFlag)
{
  /* Check input parameters */
  ASSERT(NULL != pSemaphore);
  ASSERT((0 == waitFlag) || (1 == waitFlag));

  /* Semaphore take return status */
  uint32_t returnStatus = 0;

  /* Pointer to the current running thread */
  RTOS_thread_t * pRunningThread;

  /* Temp variable to store the semaphore value */
  uint32_t semaphoreValueTemp = 0;

  /* Variable to terminate the while loop */
  uint32_t terminate = 0;

  /* Try to decrement the semaphore */
  while(1 != terminate)
  {
    /* Read the semaphore counter value */
    semaphoreValueTemp = __LDREXW(&pSemaphore->semaphoreValue);

    /* Check semaphore counter value, note in ARMv7-M exceptions automatically
     * clear the exclusive state in the local monitor,
     * no need to use CLREX instruction */
    if(0 < semaphoreValueTemp)
    {
      /* Semaphore is not fully taken, take one by decrement */
      if(0 == __STREXW((semaphoreValueTemp - 1), &pSemaphore->semaphoreValue))
      {
        /* Required before accessing protected resource */
        __DMB();

        /* Semaphore is taken, return OK */
        returnStatus = 1;

        /* Store succeeded, terminate the loop */
        terminate = 1;
      }
      else
      {
        /* Problem during decrementing, try again */
      }
    }
    else
    {
      /* Semaphore is not available, terminate the loop */
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
    RTOS_listInsert(&pSemaphore->waitingList, &pRunningThread->item);

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
 * @brief   Semaphore give
 * @note
 * @param   RTOS_semaphore_t *
 * @retval  None
 */
void RTOS_semaphoreGive(RTOS_semaphore_t * pSemaphore)
{
  /* Check input parameters */
  ASSERT(NULL != pSemaphore);

  /* Pointer to the unblocked thread */
  RTOS_thread_t * pThread;

  /* Temp variable used to read the semaphore counter value */
  uint32_t semaphoreValueTemp = 0;

  /* Variable to terminate the while loop */
  uint32_t terminate = 0;

  /* Try incrementing the semaphore counter */
  while(1 != terminate)
  {
    /* Get the semaphore value */
    semaphoreValueTemp = __LDREXW(&pSemaphore->semaphoreValue);

    /* Increment temp variable */
    semaphoreValueTemp++;

    /* Try to store the incremented semaphore value */
    if(0 == __STREXW(semaphoreValueTemp, &pSemaphore->semaphoreValue))
    {
      /* Store succeeded, terminate the loop */
      terminate = 1;

      /* Required before releasing protected resource */
      __DMB();
    }
    else
    {
      /* Store failed, try again */
    }
  }

  /* Get highest priority waiting thread, the one next from the end */
  if(0 < pSemaphore->waitingList.numOfItems)
  {
    pThread = pSemaphore->waitingList.listEnd.pNext->pThread;

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
