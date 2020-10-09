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
#ifdef TOUCH_KEY
		

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
#else
		/*����������ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( KEY_ROW_0_GPIO_CLK | KEY_ROW_1_GPIO_CLK | \
														KEY_ROW_2_GPIO_CLK | KEY_ROW_3_GPIO_CLK | \
														KEY_COL_0_GPIO_CLK | KEY_COL_1_GPIO_CLK | \
														KEY_COL_2_GPIO_CLK | KEY_COL_3_GPIO_CLK   \
													, ENABLE);
		/*��ʼ�����󰴼�����*/
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY_ROW_0_GPIO_PIN;	
		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY_ROW_0_GPIO_PORT, &GPIO_InitStructure);
		GPIO_SetBits(KEY_ROW_0_GPIO_PORT, KEY_ROW_0_GPIO_PIN);
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY_ROW_1_GPIO_PIN;
		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY_ROW_1_GPIO_PORT, &GPIO_InitStructure);
		GPIO_SetBits(KEY_ROW_1_GPIO_PORT, KEY_ROW_1_GPIO_PIN);	
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY_ROW_2_GPIO_PIN;
		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY_ROW_2_GPIO_PORT, &GPIO_InitStructure);
		GPIO_SetBits(KEY_ROW_2_GPIO_PORT, KEY_ROW_2_GPIO_PIN);
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY_ROW_3_GPIO_PIN;
		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY_ROW_3_GPIO_PORT, &GPIO_InitStructure);
		GPIO_SetBits(KEY_ROW_3_GPIO_PORT, KEY_ROW_3_GPIO_PIN);
		
		
		/*��ʼ�����󰴼�����*/
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY_COL_0_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY_COL_0_GPIO_PORT, &GPIO_InitStructure);
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY_COL_1_GPIO_PIN;
		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY_COL_1_GPIO_PORT, &GPIO_InitStructure);
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY_COL_2_GPIO_PIN;
		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY_COL_2_GPIO_PORT, &GPIO_InitStructure);
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY_COL_3_GPIO_PIN;
		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY_COL_3_GPIO_PORT, &GPIO_InitStructure);
		
		

#endif
	
		
		
		
	
		

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

#ifdef TOUCH_KEY
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
#else
	for(i=0;i<4;i++)
	{
		if(i == 0)
		{
			GPIO_ResetBits(KEY_ROW_0_GPIO_PORT, KEY_ROW_0_GPIO_PIN);
		}else if(i == 1)
		{
			GPIO_ResetBits(KEY_ROW_1_GPIO_PORT, KEY_ROW_1_GPIO_PIN);
		}else if(i == 2)
		{
			GPIO_ResetBits(KEY_ROW_2_GPIO_PORT, KEY_ROW_2_GPIO_PIN);
		}else
		{
			GPIO_ResetBits(KEY_ROW_3_GPIO_PORT, KEY_ROW_3_GPIO_PIN);
		}
		
		if(GPIO_ReadInputDataBit(KEY_COL_0_GPIO_PORT,KEY_COL_0_GPIO_PIN) == 0)
		{
			res = i*4 + 1;
		}else if(GPIO_ReadInputDataBit(KEY_COL_1_GPIO_PORT,KEY_COL_1_GPIO_PIN) == 0)
		{
			res = i*4 + 2;
		}else if(GPIO_ReadInputDataBit(KEY_COL_2_GPIO_PORT,KEY_COL_2_GPIO_PIN) == 0)
		{
			res = i*4 + 3;
		}else if(GPIO_ReadInputDataBit(KEY_COL_3_GPIO_PORT,KEY_COL_3_GPIO_PIN) == 0)
		{
			res = i*4 + 4;
		}
		
		GPIO_SetBits(KEY_ROW_0_GPIO_PORT, KEY_ROW_0_GPIO_PIN);
		GPIO_SetBits(KEY_ROW_1_GPIO_PORT, KEY_ROW_1_GPIO_PIN);
		GPIO_SetBits(KEY_ROW_2_GPIO_PORT, KEY_ROW_2_GPIO_PIN);
		GPIO_SetBits(KEY_ROW_3_GPIO_PORT, KEY_ROW_3_GPIO_PIN);
		
		if(res != 0)
		{
			break;
		}
	}
	
#endif
	
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
	uint8_t fpm_pre = 0;
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
			rt_kprintf("\n key=%d",i);
			rt_mq_send(	inputsig_mq,&i,1);
		}
		pre=cur;
		
		i = FPM_IsTouch();
		if(i == 1 && fpm_pre == 0)
		{
			cur = 16;
			rt_mq_send(	inputsig_mq,&cur,1);
		}
		fpm_pre = i;
		
		rt_thread_delay(100);
	}
}

