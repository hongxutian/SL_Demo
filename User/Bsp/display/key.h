#ifndef __KEY_H
#define	__KEY_H

#include "stm32f10x.h"
#include "board.h"
#include "rtthread.h"

//#define TOUCH_KEY	

#ifdef TOUCH_KEY

#define KEY_SDO_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define KEY_SDO_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define KEY_SDO_GPIO_PIN			GPIO_Pin_11			        /* 连接到SDO的GPIO */

#define KEY_SCL_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define KEY_SCL_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define KEY_SCL_GPIO_PIN			GPIO_Pin_10			        /* 连接到SCL的GPIO */


#define KEY_SCL_0 						GPIO_ResetBits(KEY_SCL_GPIO_PORT,KEY_SCL_GPIO_PIN)
#define KEY_SCL_1 						GPIO_SetBits(KEY_SCL_GPIO_PORT,KEY_SCL_GPIO_PIN)

#else

#define KEY_ROW_0_GPIO_PORT			GPIOD
#define KEY_ROW_0_GPIO_CLK			RCC_APB2Periph_GPIOD
#define KEY_ROW_0_GPIO_PIN			GPIO_Pin_8

#define KEY_ROW_1_GPIO_PORT			GPIOD
#define KEY_ROW_1_GPIO_CLK			RCC_APB2Periph_GPIOD
#define KEY_ROW_1_GPIO_PIN			GPIO_Pin_9

#define KEY_ROW_2_GPIO_PORT			GPIOD
#define KEY_ROW_2_GPIO_CLK			RCC_APB2Periph_GPIOD
#define KEY_ROW_2_GPIO_PIN			GPIO_Pin_10

#define KEY_ROW_3_GPIO_PORT			GPIOD
#define KEY_ROW_3_GPIO_CLK			RCC_APB2Periph_GPIOD
#define KEY_ROW_3_GPIO_PIN			GPIO_Pin_11

#define KEY_COL_0_GPIO_PORT			GPIOD
#define KEY_COL_0_GPIO_CLK			RCC_APB2Periph_GPIOD
#define KEY_COL_0_GPIO_PIN			GPIO_Pin_12

#define KEY_COL_1_GPIO_PORT			GPIOD
#define KEY_COL_1_GPIO_CLK			RCC_APB2Periph_GPIOD
#define KEY_COL_1_GPIO_PIN			GPIO_Pin_13

#define KEY_COL_2_GPIO_PORT			GPIOD
#define KEY_COL_2_GPIO_CLK			RCC_APB2Periph_GPIOD
#define KEY_COL_2_GPIO_PIN			GPIO_Pin_14

#define KEY_COL_3_GPIO_PORT			GPIOD
#define KEY_COL_3_GPIO_CLK			RCC_APB2Periph_GPIOD
#define KEY_COL_3_GPIO_PIN			GPIO_Pin_15

#endif

void Key_Init(void);
uint16_t Key_Scan(void);
void key_thread_entry(void* parameter);
#endif 
