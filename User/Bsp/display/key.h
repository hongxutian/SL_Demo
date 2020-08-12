#ifndef __KEY_H
#define	__KEY_H

#include "stm32f10x.h"
#include "board.h"
#include "rtthread.h"

#define KEY_SDO_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define KEY_SDO_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define KEY_SDO_GPIO_PIN			GPIO_Pin_11			        /* 连接到SDO的GPIO */

#define KEY_SCL_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define KEY_SCL_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define KEY_SCL_GPIO_PIN			GPIO_Pin_10			        /* 连接到SCL的GPIO */


#define KEY_SCL_0 						GPIO_ResetBits(KEY_SCL_GPIO_PORT,KEY_SCL_GPIO_PIN)
#define KEY_SCL_1 						GPIO_SetBits(KEY_SCL_GPIO_PORT,KEY_SCL_GPIO_PIN)

void Key_Init(void);
uint16_t Key_Scan(void);
void key_thread_entry(void* parameter);
#endif 
