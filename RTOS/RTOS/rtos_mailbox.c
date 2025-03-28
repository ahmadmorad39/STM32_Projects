/*
 * rtos_mailbox.c
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
 * @defgroup rtos_mailbox
 * @brief
 * @{
 */

/**
 * @defgroup rtos_mailbox_private_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_private_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_private_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_private_variables
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_private_function_prototypes
 * @{
 */

static void checkWaitingThreads(RTOS_mailbox_t * pMailbox);
static void blockCurrentThread(RTOS_mailbox_t * pMailbox);

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_private_functions
 * @{
 */

/**
 * @brief   Check if threads are waiting for a new data
 * @note
 * @param   RTOS_mailbox_t *
 * @retval  None
 */
static void checkWaitingThreads(RTOS_mailbox_t * pMailbox)
{
  /* Check input parameters */
  ASSERT(NULL != pMailbox);

  /* Pointer to the unblocked thread */
  RTOS_thread_t * pThread;

  /* Check if threads are waiting for the data */
  if(0 < pMailbox->waitingList.numOfItems)
  {
    /* Get first one */
    pThread = pMailbox->waitingList.listEnd.pNext->pThread;

    /* Check returned thread */
    ASSERT(NULL != pThread);

    /* Remove the returned thread item from the waiting list */
    RTOS_listRemove(&pThread->item);

    /* Add the returned thread into ready list */
    RTOS_threadAddToReadyList(pThread);
  }
  else
  {
    /* List is empty */
  }
}

/**
 * @brief   Block current thread when buffer is full or empty
 * @note
 * @param   RTOS_mailbox_t *
 * @retval  None
 */
static void blockCurrentThread(RTOS_mailbox_t * pMailbox)
{
  /* Pointer to the current running thread */
  RTOS_thread_t * pRunningThread;

  /* Get current running thread */
  pRunningThread = RTOS_threadGetRunning();

  /* Remove current thread from ready list */
  RTOS_listRemove(&pRunningThread->item);

  /* Put current thread into the waiting list */
  RTOS_listInsert(&pMailbox->waitingList, &pRunningThread->item);

  /* Trigger context switch, set PendSV to pending */
  SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_exported_functions
 * @{
 */

/**
 * @brief   Mailbox create
 * @note
 * @param   RTOS_mailbox_t *, void *, uint32_t, uint32_t
 * @retval  None
 */
void RTOS_mailboxCreate(RTOS_mailbox_t * pMailbox, void * pBuffer,
    uint32_t bufferLength, uint32_t messageSize)
{
  /* Check input parameters */
  ASSERT(NULL != pMailbox);
  ASSERT(NULL != pBuffer);
  ASSERT(0 != bufferLength);
  ASSERT((1 == messageSize) || (2 == messageSize) || (4 == messageSize));

  /* Set mailbox buffer start and end */
  pMailbox->pStart = (int8_t *) pBuffer;
  pMailbox->pEnd = pMailbox->pStart + (bufferLength * messageSize);

  /* Initialize read and write indices */
  pMailbox->pReadIndex = pMailbox->pStart;
  pMailbox->pWriteIndex = pMailbox->pStart;

  /* Set buffer length and message size */
  pMailbox->bufferLength = bufferLength;
  pMailbox->messageSize = messageSize;

  /* Initialize current number of messages */
  pMailbox->messagesNum = 0;

  /* Initialize mailbox waiting list */
  RTOS_listInit(&pMailbox->waitingList);
}

/**
 * @brief   Mailbox write
 * @note
 * @param   RTOS_mailbox_t *, uint32_t, const void * const
 * @retval  uint32_t
 */
uint32_t RTOS_mailboxWrite(RTOS_mailbox_t * pMailbox, uint32_t waitFlag,
    const void * const pMessage)
{
  /* Check input parameters */
  ASSERT(NULL != pMailbox);
  ASSERT((0 == waitFlag) || (1 == waitFlag));
  ASSERT(NULL != pMessage);

  /* Return status */
  uint32_t returnStatus = 0;

  /* Check if there is a free place to write */
  if(pMailbox->bufferLength > pMailbox->messagesNum)
  {
    /* Buffer is not full, copy data */
    memcpy((void *) pMailbox->pWriteIndex, pMessage, pMailbox->messageSize);

    /* Increment write index to point to the next message */
    pMailbox->pWriteIndex += pMailbox->messageSize;

    /* Check if the buffer is written until the end */
    if(pMailbox->pWriteIndex >= pMailbox->pEnd)
    {
      /* Start over */
      pMailbox->pWriteIndex = pMailbox->pStart;
    }
    else
    {
      /* Do nothing, end is still not reached */
    }

    /* Increment current number of messages in the buffer */
    pMailbox->messagesNum++;

    /* Check waiting threads */
    checkWaitingThreads(pMailbox);

    /* New message is added to the buffer, return OK */
    returnStatus = 1;
  }
  else
  {
    /* Do nothing, Buffer is full */
  }

  /* Check waiting flag and return status */
  if((1 == waitFlag) && (1 != returnStatus))
  {
    /* Block current thread */
    blockCurrentThread(pMailbox);

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
 * @brief   Mailbox read
 * @note
 * @param   RTOS_mailbox_t *, uint32_t, void * const
 * @retval  uint32_t
 */
uint32_t RTOS_mailboxRead(RTOS_mailbox_t * pMailbox, uint32_t waitFlag,
    void * const pMessage)
{
  /* Check input parameters */
  ASSERT(NULL != pMailbox);
  ASSERT((0 == waitFlag) || (1 == waitFlag));
  ASSERT(NULL != pMessage);

  /* Return status */
  uint32_t returnStatus = 0;

  /* Check if there are messages in the buffer */
  if(0 < pMailbox->messagesNum)
  {
    /* Buffer is not empty, copy data */
    memcpy(pMessage, (void *) pMailbox->pReadIndex, pMailbox->messageSize);

    /* Increment Read index to point to the next message */
    pMailbox->pReadIndex += pMailbox->messageSize;

    /* Check if the buffer is read until the end */
    if(pMailbox->pReadIndex >= pMailbox->pEnd)
    {
      /* Start over */
      pMailbox->pReadIndex = pMailbox->pStart;
    }
    else
    {
      /* Do nothing, end is still not reached */
    }

    /* Decrement current number of messages in the buffer */
    pMailbox->messagesNum--;

    /* Check waiting threads */
    checkWaitingThreads(pMailbox);

    /* New message is removed from the buffer, return OK */
    returnStatus = 1;
  }
  else
  {
    /* Do nothing, Buffer is empty */
  }

  /* Check waiting flag and return status */
  if((1 == waitFlag) && (1 != returnStatus))
  {
    /* Block current thread */
    blockCurrentThread(pMailbox);

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
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
