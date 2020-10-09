#include "lock_operation.h"
#include "stm32f10x.h"
#include "board.h"

void Lock_Operation_Config(void)
{
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( LOCK_OPERATION_GPIO_CLK, ENABLE);
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LOCK_OPERATION_GPIO_PIN;	
		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LOCK_OPERATION_GPIO_PORT, &GPIO_InitStructure);
		GPIO_SetBits(LOCK_OPERATION_GPIO_PORT, LOCK_OPERATION_GPIO_PIN);
		
		LOCK_OPERATION_CLOSE;
}

void lock_operation_thread_entry(void *param)
{
	rt_err_t err;
	char cache;
	while(1)
	{
		err = rt_mq_recv(lockmq,&cache,1,10000);
		if(err == RT_EOK)
		{
			continue;
		}
		err = rt_mq_recv(lockmq,&cache,1,RT_WAITING_FOREVER);
		if(err == RT_EOK)
		{
			if(cache == 1)
			{
				LOCK_OPERATION_OPEN;
				rt_thread_delay(1000);
				LOCK_OPERATION_CLOSE;
			}
		}
	}
}