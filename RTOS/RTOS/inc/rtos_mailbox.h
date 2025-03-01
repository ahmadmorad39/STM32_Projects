/*
 * rtos_mailbox.h
 *
 *  Created on: Mar 1, 2025
 *      Author: ahmad
 */

#ifndef INC_RTOS_MAILBOX_H_
#define INC_RTOS_MAILBOX_H_

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
 * @addtogroup rtos_mailbox
 * @{
 */

/**
 * @defgroup rtos_mailbox_exported_typedefs
 * @{
 */

/**
 * @brief      Mailbox type
 * @note
 * @see
 */
typedef struct
{
  int8_t * pStart;          /**< Start location */
  int8_t * pEnd;            /**< Last location */
  int8_t * pReadIndex;      /**< Read location */
  int8_t * pWriteIndex;     /**< Write location */
  uint32_t bufferLength;    /**< Length of the mailbox buffer */
  uint32_t messageSize;     /**< Mailbox message size in bytes */
  uint32_t messagesNum;     /**< Current number of messages inside the buffer */
  RTOS_list_t waitingList;  /**< Waiting list */
} RTOS_mailbox_t;

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_exported_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_exported_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_exported_functions
 * @{
 */

void RTOS_mailboxCreate(RTOS_mailbox_t * pMailbox, void * pBuffer,
    uint32_t bufferLength, uint32_t messageSize);
void RTOS_SVC_mailboxCreate(RTOS_mailbox_t * pMailbox, void * pBuffer,
    uint32_t bufferLength, uint32_t messageSize);

uint32_t RTOS_mailboxWrite(RTOS_mailbox_t * pMailbox, uint32_t waitFlag,
    const void * const pMessage);
uint32_t RTOS_SVC_mailboxWrite(RTOS_mailbox_t * pMailbox, uint32_t waitFlag,
    const void * const pMessage);

uint32_t RTOS_mailboxRead(RTOS_mailbox_t * pMailbox, uint32_t waitFlag,
    void * const pMessage);
uint32_t RTOS_SVC_mailboxRead(RTOS_mailbox_t * pMailbox, uint32_t waitFlag,
    void * const pMessage);

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


#endif /* INC_RTOS_MAILBOX_H_ */
