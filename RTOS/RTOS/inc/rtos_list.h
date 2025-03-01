/*
 * rtos_list.h
 *
 *  Created on: Feb 22, 2025
 *      Author: ahmad
 */

#ifndef INC_RTOS_LIST_H_
#define INC_RTOS_LIST_H_

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
 * @addtogroup rtos_list
 * @{
 */

/**
 * @defgroup rtos_list_exported_typedefs
 * @{
 */

/**
 * @brief      Linked list item type
 * @note
 * @see
 */
struct listItem_t
{
  uint32_t itemValue;            /**< Item value used for sorting in non ready lists */
  struct listItem_t * pNext;     /**< Pointer to the next list item */
  struct listItem_t * pPrev;     /**< Pointer to the previous list item */
  void * pThread;                /**< Pointer to the thread of the item */
  void * pList;                  /**< Pointer to the list in which the item it */
};
typedef struct listItem_t RTOS_listItem_t;

/**
 * @brief      Linked list item type
 * @note
 * @see
 */
typedef struct
{
  uint32_t itemValue;          /**< Item value used for sorting in non ready lists */
  RTOS_listItem_t * pNext;     /**< Pointer to the next list item */
  RTOS_listItem_t * pPrev;     /**< Pointer to the previous list item */
} RTOS_listEnd_t;


/**
 * @brief      Linked list type
 * @note
 * @see
 */
typedef struct
{
  uint32_t numOfItems;           /**< Number of threads items in the list */
  RTOS_listItem_t * pIndex;        /**< Pointer to the current item */
  RTOS_listEnd_t listEnd;          /**< List end */
} RTOS_list_t;

/**
 * @}
 */

/**
 * @defgroup rtos_list_exported_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_list_exported_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_list_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_list_exported_functions
 * @{
 */

void RTOS_listInit(RTOS_list_t * pList);
void RTOS_listInsertEnd(RTOS_list_t * pList, RTOS_listItem_t * pNewItem);
void RTOS_listInsert(RTOS_list_t * pList, RTOS_listItem_t * pNewItem);
void RTOS_listRemove(RTOS_listItem_t * pRemovedItem);

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


#endif /* INC_RTOS_LIST_H_ */
