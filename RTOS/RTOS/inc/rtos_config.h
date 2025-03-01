/*
 * rtos_config.h
 *
 *  Created on: Feb 22, 2025
 *      Author: ahmad
 */

#ifndef INC_RTOS_CONFIG_H_
#define INC_RTOS_CONFIG_H_

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
 * @addtogroup rtos_config
 * @{
 */

/**
 * @defgroup rtos_config_exported_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_defines
 * @{
 */

/**
 * @brief   Stack size for each thread in double words. e.g 1024 means 8Kbytes.
 */
#define THREAD_STACK_SIZE                 ((uint32_t) 1024u)

/**
 * @brief   Thread maximum priority,
 *          threads can have priority from 0 to (THREAD_MAX_PRIORITY-1)
 */
#define THREAD_PRIORITY_LEVELS               ((uint32_t) 16u)

/**
 * @brief   CPU clock frequency in hertz
 */
#define SYSTEM_CORE_CLOCK_HZ                 ((uint32_t) 180000000u)

/**
 * @brief   System tick frequency in hertz
 */
#define SYS_TICK_RATE_HZ                     ((uint32_t) 1000u)


/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_macros
 * @{
 */

/**
 * @brief   Assert macro
 */
#define ASSERT(x) if((x) == 0) {__disable_irq(); while(1); }

/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_functions
 * @{
 */

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

#endif /* INC_RTOS_CONFIG_H_ */
