/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   RT-Thread 3.0 + STM32 动态内存管理
  *********************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 

/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/ 
#include "board.h"
#include "rtthread.h"
#include <string.h>
#include "G4App.h"
#include "UI.h"
#include "sysinit.h"

/*
******************************************************************
*                               变量
******************************************************************
*/
/* 定义线程控制块 */
rt_thread_t key_th = RT_NULL;
/* 定义消息队列控制块 */
rt_mq_t test_mq = RT_NULL;

rt_thread_t g4th = RT_NULL;//转发4G模块返回信息的线程
rt_mailbox_t g4mb = RT_NULL;//4G模块串口向，4G模块数据转发线程发送的邮箱

rt_thread_t g4appreceth = RT_NULL;//接收和连接服务器的线程
rt_mailbox_t g4appmb = RT_NULL;//4G模块数据转发线程向接收和连接服务器线程发送的邮箱

rt_thread_t g4appsendth = RT_NULL;//数据发送线程
rt_mq_t g4msgmq = RT_NULL;//向服务器发送生数据时，把数据发送到这个消息队列，由数据发送线程负责发送

rt_thread_t uith = RT_NULL;

rt_mq_t inputsig_mq = RT_NULL;//外部输入信号消息队列

/************************* 全局变量声明 ****************************/
/*
 * 当我们在写应用程序的时候，可能需要用到一些全局变量。
 */

/* 相关宏定义 */

/*
*************************************************************************
*                             函数声明
*************************************************************************
*/

/*
*************************************************************************
*                             main 函数
*************************************************************************
*/
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	uint8_t i,res;
	uint16_t num;

	i = FPM_GetUserNumber(&num);
	rt_kprintf("\nnumber:i=%d,num=%d",i,num);
//	i=FPM_GetAvailableUserNumber(&num,&res);
//	rt_kprintf("\navaliable num:i=%d num=%d res=%d",i,num,res);
////	return 0;     
//	i=FPM_AddUser(0x01,100,0x01,&res);
//	rt_kprintf("\nadd:i=%d,res=%d",i,res);
//	return 0;
	
	OLED_Init();
	OLED_GRAM_Fill(0);
	
	systeminit();
	g4mb=rt_mb_create("g4mb",
													5, 
													RT_IPC_FLAG_FIFO);
	g4appmb=rt_mb_create("g4appmb",
													5, 
													RT_IPC_FLAG_FIFO);
	if (g4mb != RT_NULL)
	{
		rt_kprintf("\r\ng4mb success!\n\n");
	}else
	{
		rt_kprintf("\r\ng4mbfail!\n\n");
	}
	
  /* 创建一个消息队列 */
	g4msgmq = rt_mq_create("g4msgmq",/* 消息队列名字 */
                     1024,     /* 消息的最大长度 */
                     2,    /* 消息队列的最大容量 */
                     RT_IPC_FLAG_FIFO);/* 队列模式 FIFO(0x00)*/
  if (g4msgmq != RT_NULL)
    rt_kprintf("消息队列创建成功！\n\n");
	
	 /* 创建一个消息队列 */
	inputsig_mq = rt_mq_create("inputsig",/* 消息队列名字 */
                     1,     /* 消息的最大长度 */
                     2,    /* 消息队列的最大容量 */
                     RT_IPC_FLAG_FIFO);/* 队列模式 FIFO(0x00)*/
  if (inputsig_mq != RT_NULL)
    rt_kprintf("消息队列创建成功！\n\n");
  

		
	
		
		 
		 
		 /* 创建一个任务 */
	g4th =                          /* 线程控制块指针 */
    rt_thread_create( "g4",              /* 线程名字 */
                      G4_Thread_Entry,   /* 线程入口函数 */
                      RT_NULL,             /* 线程入口函数参数 */
                      256,                 /* 线程栈大小 */
                      5,                   /* 线程的优先级 */
                      20);                 /* 线程时间片 */
                   
    /* 启动线程，开启调度 */
   if (g4th != RT_NULL)
        rt_thread_startup(g4th);
    else
        return -1;
		
	  /* 创建一个任务 */
	g4appreceth =                          /* 线程控制块指针 */
    rt_thread_create( "g4rec",              /* 线程名字 */
                      G4APP_Rece_Thread_Entry,   /* 线程入口函数 */
                      RT_NULL,             /* 线程入口函数参数 */
                      4096,                 /* 线程栈大小 */
                      5,                   /* 线程的优先级 */
                      20);                 /* 线程时间片 */
                   
    /* 启动线程，开启调度 */
   if (g4appreceth != RT_NULL)
        rt_thread_startup(g4appreceth);
    else
        return -1;
		
	 /* 创建一个任务 */
	g4appsendth =                          /* 线程控制块指针 */
    rt_thread_create( "g4sen",              /* 线程名字 */
                      G4APP_Send_Thread_Entry,   /* 线程入口函数 */
                      RT_NULL,             /* 线程入口函数参数 */
                      4096,                 /* 线程栈大小 */
                      5,                   /* 线程的优先级 */
                      20);                 /* 线程时间片 */
                   
    /* 启动线程，开启调度 */
   if (g4appsendth != RT_NULL)
        rt_thread_startup(g4appsendth);
    else
        return -1;

		/* 创建一个任务 */
	uith =                          /* 线程控制块指针 */
    rt_thread_create( "ui",              /* 线程名字 */
                      UI_Thread_Entry,   /* 线程入口函数 */
                      RT_NULL,             /* 线程入口函数参数 */
                      4096,                 /* 线程栈大小 */
                      7,                   /* 线程的优先级 */
                      20);                 /* 线程时间片 */
                   
    /* 启动线程，开启调度 */
   if (uith != RT_NULL)
        rt_thread_startup(uith);
    else
        return -1;
		
	/* 创建一个任务 */
	key_th =                          /* 线程控制块指针 */
    rt_thread_create( "key",              /* 线程名字 */
                      key_thread_entry,   /* 线程入口函数 */
                      RT_NULL,             /* 线程入口函数参数 */
                      256,                 /* 线程栈大小 */
                      5,                   /* 线程的优先级 */
                      20);                 /* 线程时间片 */
                   
    /* 启动线程，开启调度 */
   if (key_th != RT_NULL)
        rt_thread_startup(key_th);
    else
        return -1;
}

/*
*************************************************************************
*                             线程定义
*************************************************************************
*/






/********************************END OF FILE****************************/
