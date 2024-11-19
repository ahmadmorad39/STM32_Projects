/*
 * gpio.h
 *
 *  Created on: Nov 19, 2024
 *  Author    : ahmad
 *
 * @brief   Some examples on how to use STM32 GPIOs
 *
 * @note    Example: calculate the bit band address of the green LED
 *                   connected to PG13
 *
 *          General equation:
 *          bit_word_addr = bit_band_base + (byte_offset * 32) + (bit_number * 4)
 *
 *          peripheral_base_address = 0x40000000 (Fixed for all ARM Cortex-M4)
 *          bit_band_base           = 0x42000000 (Fixed for all ARM Cortex-M4)
 *          port_G_address          = 0x40021800 (From STM32F4 datasheet)
 *          register_ODR_offset     = 0x14       (From STM32F4 reference manual)
 *
 *          byte_offset = port_G_address + register_ODR_offset - peripheral_base_address
 *                      = 0x40021800 + 0x14 - 0x40000000
 *                      = 0x00021814
 *
 *          bit_number  = 13 (Green LED connected to PG13)
 *
 *          bit_word_addr = 0x42000000 + (0x00021814 * 32) + (13 * 4)
 *                        = 0x42000000 + 0x00430280 + 0x34
 *                        = 0x424302B4
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "stm32f4xx.h"

/**
 * @brief   On-board LEDs
 */
typedef enum
{
  EVAL_GREEN_LED,
  EVAL_GREEN_LED_BITBAND,
  EVAL_RED_LED,
  EVAL_ALL_LEDs
} Led_Type;

/**
 * @brief   Define base address of peripheral bit-band
 */
#define BITBAND_PERI_BASE 0x40000000

/**
 * @brief   Define base address of peripheral alias band
 */
#define ALIAS_PERI_BASE 0x42000000

/**
 * @brief   Define address of GPIOG
 */
#define GPIOG_ODR 0x40021814

/**
 * @brief   Convert PERI address to alias region
 */
#define BITBAND_PERI(reg_address, bit_number) ((ALIAS_PERI_BASE + \
                (reg_address - BITBAND_PERI_BASE) * 32 + (bit_number * 4)))

/**
 * @brief   Green LED connected to GPIOG bit 13
 */
#define GREEN_LED_BITBAND *((volatile uint32_t *)(BITBAND_PERI(GPIOG_ODR, 13)))

/**
 * @brief   On-board LEDs initialization function
 * @note    EVAL_GREEN_LED -> PG13
 * @param
 * @retval
 */
void GPIO_Init_LED(Led_Type led);

/**
 * @brief   Turns on-board LED on
 * @note    EVAL_GREEN_LED -> PG13
 * @param   Led_Type led
 * @retval
 */
void GPIO_TurnON_LED(Led_Type led);

/**
 * @brief   Turns on-board LED off
 * @note    EVAL_GREEN_LED -> PG13
 * @param   Led_Type led
 * @retval
 */
void GPIO_TurnOFF_LED(Led_Type led);

/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif


#endif /* INC_GPIO_H_ */
