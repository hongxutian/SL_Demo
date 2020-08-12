/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   RT-Thread 3.0 + STM32 ��̬�ڴ����
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 

/*
*************************************************************************
*                             ������ͷ�ļ�
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
*                               ����
******************************************************************
*/
/* �����߳̿��ƿ� */
rt_thread_t key_th = RT_NULL;
/* ������Ϣ���п��ƿ� */
rt_mq_t test_mq = RT_NULL;

rt_thread_t g4th = RT_NULL;//ת��4Gģ�鷵����Ϣ���߳�
rt_mailbox_t g4mb = RT_NULL;//4Gģ�鴮����4Gģ������ת���̷߳��͵�����

rt_thread_t g4appreceth = RT_NULL;//���պ����ӷ��������߳�
rt_mailbox_t g4appmb = RT_NULL;//4Gģ������ת���߳�����պ����ӷ������̷߳��͵�����

rt_thread_t g4appsendth = RT_NULL;//���ݷ����߳�
rt_mq_t g4msgmq = RT_NULL;//�����������������ʱ�������ݷ��͵������Ϣ���У������ݷ����̸߳�����

rt_thread_t uith = RT_NULL;

rt_mq_t inputsig_mq = RT_NULL;//�ⲿ�����ź���Ϣ����

/************************* ȫ�ֱ������� ****************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩȫ�ֱ�����
 */

/* ��غ궨�� */

/*
*************************************************************************
*                             ��������
*************************************************************************
*/

/*
*************************************************************************
*                             main ����
*************************************************************************
*/
/**
  * @brief  ������
  * @param  ��
  * @retval ��
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
	
  /* ����һ����Ϣ���� */
	g4msgmq = rt_mq_create("g4msgmq",/* ��Ϣ�������� */
                     1024,     /* ��Ϣ����󳤶� */
                     2,    /* ��Ϣ���е�������� */
                     RT_IPC_FLAG_FIFO);/* ����ģʽ FIFO(0x00)*/
  if (g4msgmq != RT_NULL)
    rt_kprintf("��Ϣ���д����ɹ���\n\n");
	
	 /* ����һ����Ϣ���� */
	inputsig_mq = rt_mq_create("inputsig",/* ��Ϣ�������� */
                     1,     /* ��Ϣ����󳤶� */
                     2,    /* ��Ϣ���е�������� */
                     RT_IPC_FLAG_FIFO);/* ����ģʽ FIFO(0x00)*/
  if (inputsig_mq != RT_NULL)
    rt_kprintf("��Ϣ���д����ɹ���\n\n");
  

		
	
		
		 
		 
		 /* ����һ������ */
	g4th =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "g4",              /* �߳����� */
                      G4_Thread_Entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      256,                 /* �߳�ջ��С */
                      5,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (g4th != RT_NULL)
        rt_thread_startup(g4th);
    else
        return -1;
		
	  /* ����һ������ */
	g4appreceth =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "g4rec",              /* �߳����� */
                      G4APP_Rece_Thread_Entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      4096,                 /* �߳�ջ��С */
                      5,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (g4appreceth != RT_NULL)
        rt_thread_startup(g4appreceth);
    else
        return -1;
		
	 /* ����һ������ */
	g4appsendth =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "g4sen",              /* �߳����� */
                      G4APP_Send_Thread_Entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      4096,                 /* �߳�ջ��С */
                      5,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (g4appsendth != RT_NULL)
        rt_thread_startup(g4appsendth);
    else
        return -1;

		/* ����һ������ */
	uith =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "ui",              /* �߳����� */
                      UI_Thread_Entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      4096,                 /* �߳�ջ��С */
                      7,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (uith != RT_NULL)
        rt_thread_startup(uith);
    else
        return -1;
		
	/* ����һ������ */
	key_th =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "key",              /* �߳����� */
                      key_thread_entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      256,                 /* �߳�ջ��С */
                      5,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (key_th != RT_NULL)
        rt_thread_startup(key_th);
    else
        return -1;
}

/*
*************************************************************************
*                             �̶߳���
*************************************************************************
*/






/********************************END OF FILE****************************/
