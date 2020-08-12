#include "key.h"

void delay(void)
{
	uint16_t i = 0;
	while(i<100)
	{
		i++;
	}
}

 /**
  * @brief  ��ʼ������KEY��IO
  * @param  ��
  * @retval ��
  */
void Key_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����������ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( KEY_SDO_GPIO_CLK | KEY_SCL_GPIO_CLK, ENABLE);
	
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY_SDO_GPIO_PIN;
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY_SDO_GPIO_PORT, &GPIO_InitStructure);
	
	
	
	
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY_SCL_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY_SCL_GPIO_PORT, &GPIO_InitStructure);	
	
	
		
		
		
	
		
		GPIO_SetBits(KEY_SCL_GPIO_PORT, KEY_SCL_GPIO_PIN);	 
		GPIO_SetBits(KEY_SDO_GPIO_PORT, KEY_SCL_GPIO_PIN);	 
}

 /**
  * @brief  ��ʼ������
  * @param  ��
  * @retval ��
  */
void Key_Init(void)
{
	Key_GPIO_Config();
}

 /**
  * @brief  ����ɨ��
  * @param  ��
  * @retval 0��ʾû�а������£�1~16��ʾ�а�������
  */
uint16_t Key_Scan(void)
{
	uint8_t i;
	uint16_t res = 0;
	KEY_SCL_0;
	rt_thread_delay(10);
	for(i=0;i<17;i++)
	{
		//rt_thread_delay(5);
		delay();
		KEY_SCL_1;
		//rt_thread_delay(5);
		delay();
		if(GPIO_ReadInputDataBit(KEY_SDO_GPIO_PORT,KEY_SDO_GPIO_PIN) == 0)
		{
			res = i;
		}
		KEY_SCL_0;
	}
	return res;
}

 /**
  * @brief  ����ɨ��
  * @param  ��
  * @retval ��
  */
void key_thread_entry(void* parameter)
{
	uint8_t i=0, cur,pre=255;
	while(1)
	{
		i = Key_Scan();
		cur = i;
		//rt_kprintf("\n i==%d,pre=%d",i,pre);
		if(i > 0 && i!=pre)
		{
			switch(i)
			{
				case 1:
					i = 7;
					break;
				case 2:
					i = 8;
					break;
				case 3:
					i = 9;
					break;
				case 4:
					i = 12;
					break;
				case 5:
					i = 4;
					break;
				case 6:
					i = 5;
					break;
				case 7:
					i = 6;
					break;
				case 8:
					i = 13;
					break;
				case 9:
					i = 1;
					break;
				case 10:
					i = 2;
					break;
				case 11:
					i = 3;
					break;
				case 12:
					i = 14;
					break;
				case 13:
					i = 10;
					break;
				case 14:
					i = 0;
					break;
				case 15:
					i = 11;
					break;
				case 16:
					i = 15;
					break;
			}
			//rt_kprintf("\n key=%d",i);
			rt_mq_send(	inputsig_mq,&i,1);
		}
		pre=cur;
		rt_thread_delay(100);
	}
}

