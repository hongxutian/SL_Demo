#ifndef __BOARD_H__
#define __BOARD_H__

/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/
/* STM32 固件库头文件 */
#include "stm32f10x.h"

/* 开发板硬件bsp头文件 */
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_exti.h"
#include "G4.h"
#include <rthw.h>
#include <rtthread.h>
#include "OLED_I2C.h"
#include "key.h"
#include "bsp_spi_flash.h"
#include "bsp_rtc.h"

#define PASSWORD_LEN_MAX 10

extern rt_thread_t g4th;
extern rt_mailbox_t g4mb;

extern rt_thread_t g4appreceth;
extern rt_mailbox_t g4appmb;

extern rt_thread_t g4appsendth;
extern rt_mq_t g4msgmq;

extern rt_mq_t inputsig_mq;

/*
*************************************************************************
*                               函数声明
*************************************************************************
*/
void rt_hw_board_init(void);
void SysTick_Handler(void);
	

#endif /* __BOARD_H__ */


