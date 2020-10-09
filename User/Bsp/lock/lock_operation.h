#ifndef __LOCK_OPERATION_H
#define __LOCK_OPERATION_H

#include "stm32f10x.h"

#define LOCK_OPERATION_GPIO_PORT			GPIOE
#define LOCK_OPERATION_GPIO_CLK				RCC_APB2Periph_GPIOE
#define LOCK_OPERATION_GPIO_PIN				GPIO_Pin_8

#define LOCK_OPERATION_OPEN 					GPIO_ResetBits(LOCK_OPERATION_GPIO_PORT,LOCK_OPERATION_GPIO_PIN)
#define LOCK_OPERATION_CLOSE 					GPIO_SetBits(LOCK_OPERATION_GPIO_PORT,LOCK_OPERATION_GPIO_PIN)


void Lock_Operation_Config(void);
void lock_operation_thread_entry(void *param);

#endif

