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
  * @brief  初始化控制KEY的IO
  * @param  无
  * @retval 无
  */
void Key_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启按键相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( KEY_SDO_GPIO_CLK | KEY_SCL_GPIO_CLK, ENABLE);
	
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = KEY_SDO_GPIO_PIN;
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(KEY_SDO_GPIO_PORT, &GPIO_InitStructure);
	
	
	
	
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = KEY_SCL_GPIO_PIN;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(KEY_SCL_GPIO_PORT, &GPIO_InitStructure);	
	
	
		
		
		
	
		
		GPIO_SetBits(KEY_SCL_GPIO_PORT, KEY_SCL_GPIO_PIN);	 
		GPIO_SetBits(KEY_SDO_GPIO_PORT, KEY_SCL_GPIO_PIN);	 
}

 /**
  * @brief  初始化按键
  * @param  无
  * @retval 无
  */
void Key_Init(void)
{
	Key_GPIO_Config();
}

 /**
  * @brief  按键扫描
  * @param  无
  * @retval 0表示没有按键按下，1~16表示有按键按下
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
  * @brief  按键扫描
  * @param  无
  * @retval 无
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

