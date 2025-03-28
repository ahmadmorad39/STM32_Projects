/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2024-11-12

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "inc/gpio.h"
#include "inc/SysTick.h"
#include "inc/irq.h"
#include "inc/memcpy.h"
#include "inc/dma.h"
#include "inc/exti.h"
#include "inc/usart1.h"
#include "rtos.h"
/**
 * @addtogroup stm32_examples
 * @{
 */

/**
 * @defgroup main
 * @brief
 * @{
 */

/**
 * @defgroup main_private_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_private_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_private_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_private_variables
 * @{
 */

static RTOS_thread_t thread1;
static RTOS_stack_t thread1stack;
static RTOS_thread_t thread2;
static RTOS_stack_t thread2stack;
static RTOS_thread_t thread3;
static RTOS_stack_t thread3stack;
static RTOS_thread_t thread4;
static RTOS_stack_t thread4stack;

static RTOS_mutex_t mutex1;
static RTOS_semaphore_t semaphore1;
static RTOS_mailbox_t mailbox1;
static uint32_t mailbox1buffer[2];

/**
 * @}
 */

/**
 * @defgroup main_private_function_prototypes
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup main_private_functions
 * @{
 */
/**
 * @brief   thread1function
 * @note
 * @param   none
 * @retval  none
 */
void thread1function(void)
{

  while(1)
  {
    ITM_Printf("Hello World! from thread 1\n");
    ITM_Printf("**************************\n");

    for (int var = 0; var < 1000000; ++var)
    {
    }
  }
}

/**
 * @brief   thread2function
 * @note
 * @param   none
 * @retval  none
 */
void thread2function(void)
{

  while(1)
  {
    ITM_Printf("Hello World! from thread 2\n");
    ITM_Printf("**************************\n");

    for (int var = 0; var < 1000000; ++var)
    {
    }
  }
}

/**
 * @brief   thread2function
 * @note
 * @param   none
 * @retval  none
 */
void thread3function(void)
{

  while(1)
  {
    ITM_Printf("Hello World! from thread 3\n");
    ITM_Printf("**************************\n");

    for (int var = 0; var < 1000000; ++var)
    {
    }
  }
}

/**
 * @brief   thread2function
 * @note
 * @param   none
 * @retval  none
 */
void thread4function(void)
{

  while(1)
  {
    ITM_Printf("Hello World! from thread 4\n");
    ITM_Printf("**************************\n");

    for (int var = 0; var < 1000000; ++var)
    {
    }
  }
}

/**
 * @}
 */

/**
 * @defgroup main_exported_functions
 * @{
 */

/**
 * @brief   Main function
 * @note
 * @param   none
 * @retval  none
 */
int main(void)
{
  RTOS_init();

  RTOS_SVC_threadCreate(&thread1, &thread1stack, 1, thread1function);
  RTOS_SVC_threadCreate(&thread2, &thread2stack, 1, thread2function);
  RTOS_SVC_threadCreate(&thread3, &thread3stack, 1, thread3function);
  RTOS_SVC_threadCreate(&thread4, &thread4stack, 1, thread4function);


  RTOS_SVC_mutexCreate(&mutex1, 1);
  RTOS_SVC_semaphoreCreate(&semaphore1, 1);
  RTOS_SVC_mailboxCreate(&mailbox1, mailbox1buffer, 2, 4);


  RTOS_SVC_schedulerStart();

  /* Infinite loop */
  while(1)
  {

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
