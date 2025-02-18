/*
 * @file   SysTick.c
 * @author Ahmad Murad
 * @date   Created on: Feb 18, 2025
 *
 *
 *  @brief SysTick configuration source file
 *
 */

/* Includes */
#include "inc/SysTick.h"


/**
 * @brief  Delay function based on SysTick
 * @note   SysTick will be update with IRQ callback
 * @param  Waiting time in milliseconds.
 * @retval None
 */
void SysTick_Delay(uint32_t wait_time_ms)
{
	/* Store start tick */
	uint32_t startTick = Get_SysTickCounter();

	/* Loop until timeout */
	while((Get_SysTickCounter() - startTick) < wait_time_ms);
}


/**
 * @brief  SysTick initial configuration
 * @param  None
 * @retval None
 */
void SysTick_Init(void)
{
	uint32_t returnCode;

	/* Update clock configuration */
	SystemCoreClockUpdate();

	/* Check clock configuration */
	if (SystemCoreClock != (uint32_t) 180000000)
	{
		/* Clock configuration is not OK */
		while(1);
	}
	else
	{
		/* Clock configuration is OK */
	}

	/* Configure SysTick to generate an interrupt every millisecond */
	returnCode = SysTick_Config(SystemCoreClock / 1000);

	/* Check return code for errors */
	if (returnCode != 0)
	{
		/* SysTick configuration failed */
		while(1);
	}
	else
	{
		/* Do nothing, SysTick configuration is OK */
	}
}
