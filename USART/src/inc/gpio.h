/*
 * gpio.h
 *
 * @author  Ahmad Murad
 * @date    Feb 18, 2025
 *
 * @brief   some examples on how to use STM32 GPIOs
 *
 * @note    Example: calculate the bit band address of the green LED
 *			        connected to PG13
 *
 *			General equation:
 *			bit_word_addr = bit_band_base + (byte_offset * 32) + (bit_number * 4)
 *
 *			peripheral_base_address = 0x40000000 (Fixed for all ARM Cortex-M4)
 *			bit_band_base           = 0x42000000 (Fixed for all ARM Cortex-M4)
 *			port_G_address          = 0x40021800 (From STM32F4 datasheet)
 *			register_ODR_offset     = 0x14       (From STM32F4 datasheet)
 *
 *			byte_offset = port_G_address + register_ODR_offset - peripheral_base_address
 *						= 0x40021800 + 0x14 - 0x40000000
 *						= 0x00021814
 *
 *			bit_number = 13 (Green LED connected to PG13)
 *
 *			bit_word_addr = 0x42000000 + (0x00021814 * 32) + (13 * 4)
 *						  = 0x424302B4
 *
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f429i_discovery.h"

/**
 * @brief  Define base address of peripheral bit-band
 *
 */
#define BITBAND_PERI_BASE  0x40000000

/**
 * @brief  Define base address of peripheral alias band
 */

#define ALIAS_PERI_BASE   0x42000000

/**
 * @brief  Define address of GPIOG
 */
#define GPIOG_ODR         0x40021800

/**
 * @brief  Convert PERI address to alias region
 */
#define BITBAND_PERI(reg_address, bit_number) ((ALIAS_PERI_BASE + \
		(reg_address - BITBAND_PERI_BASE) * 32 + (bit_number * 4)))

#define GREEN_LED_BITBAND *((volatile uint32_t *) BITBAND_PERI(GPIOG_ODR,13))



/**
 * @brief  On-board LEDs
 */
typedef enum
{
	EVAL_GREEN_LED,
	EVAL_GREEN_LED_BITBAND,
	EVAL_RED_LED,
	EVAL_ALL_LEDs
} Led_Type;

void GPIO_TurnON_LED(Led_Type led);
void GPIO_Init_LED(Led_Type led);
void GPIO_TurnOFF_LED(Led_Type led);
void GPIO_Init_PB();


#endif /* INC_GPIO_H_ */
