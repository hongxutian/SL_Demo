#include "fpm.h"

uint8_t buff[5120];
uint16_t bufflen = 0;

static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = FPM_USART_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
	
//	/* 配置NVIC为优先级组1 */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//  
//  /* 配置中断源：按键1 */
//  NVIC_InitStructure.NVIC_IRQChannel = TOUCH_INT_EXTI_IRQ;
//  /* 配置抢占优先级 */
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  /* 配置子优先级 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* 使能中断通道 */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
}

static void FPM_USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	// 打开串口GPIO的时钟
	FPM_USART_GPIO_APBxClkCmd(FPM_USART_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	FPM_USART_APBxClkCmd(FPM_USART_CLK, ENABLE);
	
	// 开启触控信号相关时钟
	RCC_APB2PeriphClockCmd(TOUCH_INT_GPIO_CLK,ENABLE);
	
	RCC_APB2PeriphClockCmd( FPM_TOUCH_VOL_CONTROL_GPIO_CLK | FPM_WORK_VOL_CONTROL_GPIO_CLK, ENABLE);
	
	
	// 中断优先级配置
	NVIC_Configuration();
	
	//配置触控信号的引脚
	//------------------------------------------------------------------------
	/* 选择按键用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = TOUCH_INT_GPIO_PIN;
  /* 配置为浮空输入 */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(TOUCH_INT_GPIO_PORT, &GPIO_InitStructure);

//	/* 选择EXTI的信号源 */
//  GPIO_EXTILineConfig(TOUCH_INT_EXTI_PORTSOURCE, TOUCH_INT_EXTI_PINSOURCE); 
//  EXTI_InitStructure.EXTI_Line = TOUCH_INT_EXTI_LINE;
//	
//	/* EXTI为中断模式 */
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	/* 上升沿中断 */
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//  /* 使能中断 */	
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
	//------------------------------------------------------------------------
	
	GPIO_InitStructure.GPIO_Pin = FPM_TOUCH_VOL_CONTROL_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FPM_TOUCH_VOL_CONTROL_GPIO_PORT, &GPIO_InitStructure);
	FPM_TOUCH_VOL_CONTROL_DOWN;
	
	GPIO_InitStructure.GPIO_Pin = FPM_WORK_VOL_CONTROL_GPIO_PIN;
	GPIO_Init(FPM_WORK_VOL_CONTROL_GPIO_PORT, &GPIO_InitStructure);
	FPM_WORK_VOL_CONTROL_UP;




	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = FPM_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FPM_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = FPM_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(FPM_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = FPM_USART_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(FPM_USARTx, &USART_InitStructure);
	
	
	
	// 使能串口接收中断
	USART_ITConfig(FPM_USARTx, USART_IT_RXNE, ENABLE);	
	USART_ITConfig(FPM_USARTx, USART_IT_IDLE, ENABLE);	
	
	// 使能串口
	USART_Cmd(FPM_USARTx, ENABLE);	    
}

void FPM_Init(void)
{
	FPM_USART_Config();
}

void FPM_SendByte(uint8_t b)
{
	USART_SendData(FPM_USARTx,b);
	while (USART_GetFlagStatus(FPM_USARTx, USART_FLAG_TXE) == RESET);
}

void FPM_SendArray(uint8_t *arry,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++)
	{
		FPM_SendByte(arry[i]);
	}
}

/**
  * @brief  检测指纹模块是否被按下
  * @param  无
  * @retval 0表示没有按下，1表示按下
  */
uint8_t FPM_IsTouch(void)
{
	if(GPIO_ReadInputDataBit(TOUCH_INT_GPIO_PORT,TOUCH_INT_GPIO_PIN) == 1)
	{
		return 1;
	}else 
	{
		return 0;
	}
}

 /**
  * @brief  获取指纹模块中的用户数
  * @param  res 返回的用户数
  * @retval 0表示res值有效，1表示res值无效
  */
uint8_t FPM_GetUserNumber(uint16_t *res)
{
	uint16_t i;
	FPM_SendByte(0xf5);
	FPM_SendByte(0x09);
	FPM_SendByte(0x00);
	FPM_SendByte(0x00);
	FPM_SendByte(0x00);
	FPM_SendByte(0x00);
	FPM_SendByte(0x09^0x00^0x00^0x00^0x00);
	FPM_SendByte(0xf5);
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 20)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			if(buff[4] == FPM_ACK_SUCCESS)
			{
				*res = ((uint16_t)buff[2] << 8)+buff[3];
				return 0;
			}
		}
	}
	return 1;
}

 /**
  * @brief  获取指纹模块里面可用的
  * @param  res 返回查询结果 usernum有效的用户号，在res=0时有效
  * @retval 0表示res值有效，1表示res值无效
  */
uint8_t FPM_GetAvailableUserNumber(uint16_t *usernum,uint8_t *res)
{
	uint16_t i;
	FPM_SendByte(0xf5);//1
	FPM_SendByte(0x47);//2
	FPM_SendByte(0x00);//3
	FPM_SendByte(0x04);//4
	FPM_SendByte(0x00);//5
	FPM_SendByte(0x00);//6
	FPM_SendByte(0x47^0x00^0x04^0x00^0x00);//7
	FPM_SendByte(0xf5);//8
	
	FPM_SendByte(0xf5);//1
	FPM_SendByte(0x00);//2
	FPM_SendByte(0x01);//3
	FPM_SendByte(0x00);//4
	FPM_SendByte(0x64);//5
	FPM_SendByte(0x00^0x64^0x00^0x01);//6
	FPM_SendByte(0xf5);//7
	
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 20)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			*usernum = ((uint16_t)buff[2] << 8)+buff[3];
			*res = buff[4];
			return 0;
		}
	}
	return 1;
}

 /**
  * @brief  使模块进入休眠状态
  * @param  无
  * @retval 0表示成功，1表示失败
  */
uint8_t FPM_Sleep(void)
{
	uint16_t i;
	FPM_SendByte(0xf5);
	FPM_SendByte(0x2c);
	FPM_SendByte(0x00);
	FPM_SendByte(0x00);
	FPM_SendByte(0x00);
	FPM_SendByte(0x00);
	FPM_SendByte(0x2c);
	FPM_SendByte(0xf5);
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 20)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			if(buff[4] == FPM_ACK_SUCCESS)
			{
				return 0;
			}
		}
	}
	return 1;
}

 /**
  * @brief  设置指纹添加模式
  * @param  mode 模式，0允许指纹重复，1不允许指纹重复
  * @retval 0表示成功，1表示失败
  */
uint8_t FPM_SetAddMode(uint8_t mode)
{
	uint16_t i;
	if(mode !=0 && mode != 1)
	{
		return 1;
	}
	FPM_SendByte(0xf5);//1
	FPM_SendByte(0x2d);//2
	FPM_SendByte(0x00);//3
	FPM_SendByte(mode);//4
	FPM_SendByte(0x00);//5
	FPM_SendByte(0x00);//6
	FPM_SendByte(0x2d^mode);//7
	FPM_SendByte(0xf5);//8
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 20)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			if(buff[4] == FPM_ACK_SUCCESS)
			{
				return 0;
			}
		}
	}
	return 1;
}

 /**
  * @brief  读取指纹添加模式
  * @param  mode 返回指纹添加模式，0允许指纹重复，1不允许指纹重复
  * @retval 0表示成功，1表示失败
  */
uint8_t FPM_ReadAddMode(uint8_t *mode)
{
	uint16_t i;
	FPM_SendByte(0xf5);//1
	FPM_SendByte(0x2d);//2
	FPM_SendByte(0x00);//3
	FPM_SendByte(0x00);//4
	FPM_SendByte(0x01);//5
	FPM_SendByte(0x00);//6
	FPM_SendByte(0x2d^0x01);//7
	FPM_SendByte(0xf5);//8
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 20)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			if(buff[4] == FPM_ACK_SUCCESS)
			{
				*mode = buff[3];
				return 0;
			}
		}
	}
	return 1;
}


 /**
  * @brief  添加指纹
  * @param  cmd添加命令0x01/0x02/0x03,usernum用户号,auth用户权限1/2/3,res返回的结果
  * @retval 0表示操作成功模块有反应，1表示失败
  */
uint8_t FPM_AddUser(uint8_t cmd,uint16_t usernum,uint8_t auth,uint8_t * res)
{
	uint16_t i;
	uint8_t numhi,numlo;
	numhi = usernum >> 8;
	numlo = usernum ;
	FPM_SendByte(0xf5);//1
	FPM_SendByte(cmd);//2
	FPM_SendByte(numhi);//3
	FPM_SendByte(numlo);//4
	FPM_SendByte(auth);//5
	FPM_SendByte(0x00);//6
	FPM_SendByte(cmd^numhi^numlo^auth);//7
	FPM_SendByte(0xf5);//8
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i<20*10)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			*res = buff[4];
			return 0;
		}
	}
	return 1;
}

 /**
  * @brief  删除指纹
  * @param  usernum用户号,res返回的结果
  * @retval 0表示操作成功模块有反应，1表示失败
  */
uint8_t FPM_DeleteUser(uint16_t usernum,uint8_t * res)
{
	uint16_t i;
	uint8_t numhi,numlo;
	numhi = usernum >> 8;
	numlo = usernum ;
	FPM_SendByte(0xf5);//1
	FPM_SendByte(0x04);//2
	FPM_SendByte(numhi);//3
	FPM_SendByte(numlo);//4
	FPM_SendByte(0x00);//5
	FPM_SendByte(0x00);//6
	FPM_SendByte(0x04^numhi^numlo);//7
	FPM_SendByte(0xf5);//8
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 20)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			*res = buff[4];
			return 0;
		}
	}
	return 1;
}

 /**
  * @brief  删除所有指纹
  * @param  usernum用户号,res返回的结果
  * @retval 0表示操作成功模块有反应，1表示失败
  */
uint8_t FPM_DeleteAllUser(uint8_t * res)
{
	uint16_t i;
	FPM_SendByte(0xf5);//1
	FPM_SendByte(0x05);//2
	FPM_SendByte(0x00);//3
	FPM_SendByte(0x00);//4
	FPM_SendByte(0x00);//5
	FPM_SendByte(0x00);//6
	FPM_SendByte(0x05);//7
	FPM_SendByte(0xf5);//8
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 20)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			*res = buff[4];
			return 0;
		}
	}
	return 1;
}


 /**
  * @brief  比对指纹
  * @param  usernum用户号,res返回的结果
  * @retval 0表示操作成功模块有反应，1表示失败
  */
uint8_t FPM_CompUser(uint16_t usernum,uint8_t * res)
{
	uint16_t i;
	uint8_t numhi,numlo;
	numhi = usernum >> 8;
	numlo = usernum ;
	FPM_SendByte(0xf5);//1
	FPM_SendByte(0x0b);//2
	FPM_SendByte(numhi);//3
	FPM_SendByte(numlo);//4
	FPM_SendByte(0x00);//5
	FPM_SendByte(0x00);//6
	FPM_SendByte(0x0b^numhi^numlo);//7
	FPM_SendByte(0xf5);//8
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 20)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			*res = buff[4];
			return 0;
		}
	}
	return 1;
}

/**
  * @brief  比对指纹
  * @param  usernum比对结果用户号,res返回的结果
  * @retval 0表示操作成功模块有反应，1表示失败
  */
uint8_t FPM_CompAllUser(uint16_t *usernum,uint8_t * res)
{
	uint16_t i;
	FPM_SendByte(0xf5);//1
	FPM_SendByte(0x0c);//2
	FPM_SendByte(0x00);//3
	FPM_SendByte(0x00);//4
	FPM_SendByte(0x00);//5
	FPM_SendByte(0x00);//6
	FPM_SendByte(0x0c);//7
	FPM_SendByte(0xf5);//8
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 20*2)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			*res = buff[4];
			*usernum = buff[2]*256+buff[3];
			return 0;
		}
	}
	return 1;
}

/**
  * @brief  读取用户的权限
  * @param  usernum用户号,res返回的结果
  * @retval 0表示操作成功模块有反应，1表示失败
  */
uint8_t FPM_GetUserAuth(uint16_t usernum,uint8_t * res)
{
	uint16_t i;
	FPM_SendByte(0xf5);//1
	FPM_SendByte(0x0a);//2
	FPM_SendByte(0x00);//3
	FPM_SendByte(0x00);//4
	FPM_SendByte(0x00);//5
	FPM_SendByte(0x00);//6
	FPM_SendByte(0x0a);//7
	FPM_SendByte(0xf5);//8
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 10)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			*res = buff[4];
			return 0;
		}
	}
	return 1;
}

/**
  * @brief  读取所有用户的信息
  * @param  num用户数量,res返回的结果，userinfo用户信息
  * @retval 0表示操作成功模块有反应，1表示失败
  */
uint8_t FPM_GetAllUserInfo(uint8_t * res,uint16_t *num,FPM_USER_INFO_STRUC **userinfo)
{
	uint16_t i;
	FPM_USER_INFO_STRUC *p;
	uint8_t *q;
	FPM_SendByte(0xf5);//1
	FPM_SendByte(0x2b);//2
	FPM_SendByte(0x00);//3
	FPM_SendByte(0x00);//4
	FPM_SendByte(0x00);//5
	FPM_SendByte(0x00);//6
	FPM_SendByte(0x2b);//7
	FPM_SendByte(0xf5);//8
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 40)
	{
		rt_thread_delay(50);
		i++;
	}
	//检查数据头
	if(bufflen >= 8)
	{
		*res = buff[4];
		if(bufflen == 8)
		{
			*num = 0;
			userinfo = 0;
			return 0;
		}
		*num=buff[9]*256+buff[10];
		p =(FPM_USER_INFO_STRUC *) rt_malloc(sizeof(FPM_USER_INFO_STRUC)*(*num));
		i=0;
		q=&buff[11];
		while(i<*num)
		{
			p[i].num=(*q * 256)+(*(q+1));
			p[i].auth=*(q+2);
			q=q+3;
			i++;
		}
		*userinfo=p;
		return 0;
	}
	return 1;
}

/**
  * @brief  设置比对等级
  * @param  level比对等级,res返回的结果
  * @retval 0表示操作成功模块有反应，1表示失败
  */
uint8_t FPM_SetCompLevel(uint8_t level,uint8_t * res)
{
	uint16_t i;
	FPM_SendByte(0xf5);//1
	FPM_SendByte(0x28);//2
	FPM_SendByte(0x00);//3
	FPM_SendByte(level);//4
	FPM_SendByte(0x00);//5
	FPM_SendByte(0x00);//6
	FPM_SendByte(0x28^level);//7
	FPM_SendByte(0xf5);//8
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 10)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			*res = buff[4];
			return 0;
		}
	}
	return 1;
}

/**
  * @brief  读取比对等级
  * @param  level比对等级,res返回的结果
  * @retval 0表示操作成功模块有反应，1表示失败
  */
uint8_t FPM_ReadCompLevel(uint8_t *level,uint8_t * res)
{
	uint16_t i;
	FPM_SendByte(0xf5);//1
	FPM_SendByte(0x28);//2
	FPM_SendByte(0x00);//3
	FPM_SendByte(0x00);//4
	FPM_SendByte(0x01);//5
	FPM_SendByte(0x00);//6
	FPM_SendByte(0x28^0x01);//7
	FPM_SendByte(0xf5);//8
	bufflen = 0;
	i=0;
	while(bufflen == 0 && i < 10)
	{
		rt_thread_delay(50);
		i++;
	}
	if(bufflen == 8)
	{
		if(buff[1]^buff[2]^buff[3]^buff[4]^buff[5] == buff[6])
		{
			*res = buff[4];
			*level = buff[3];
			return 0;
		}
	}
	return 1;
}

void FPM_USART_IRQHandler()
{
	static uint16_t count = 0;
	uint8_t temp;
	uint8_t i;
	if ( USART_GetITStatus ( FPM_USARTx, USART_IT_RXNE ) != RESET )
	{
		temp=USART_ReceiveData( FPM_USARTx ); 
		buff[count++] = temp;
	}else if ( USART_GetITStatus( FPM_USARTx, USART_IT_IDLE ) == SET )
	{
		temp=USART_ReceiveData( FPM_USARTx );
		bufflen = count;
		rt_kprintf("\n\nback:\n");
		for(i=0;i<count;i++)
		{
			rt_kprintf("%x ",buff[i]);
		}
		rt_kprintf("\nbufflen = %d\n",bufflen);
		count = 0;
	}
}

//void TOUCH_IRQHandler(void)
//{
//  uint8_t data = 16;
//	uint8_t t;
//	//确保是否产生了EXTI Line中断
//	if(EXTI_GetITStatus(TOUCH_INT_EXTI_LINE) != RESET) 
//	{
//		t = GPIO_ReadInputDataBit(TOUCH_INT_GPIO_PORT,TOUCH_INT_GPIO_PIN);
//		//rt_kprintf("\nfinger touch,t=%d",t);
//		if(t == 1)
//		{
//			FPM_TOUCH_VOL_CONTROL_UP;
//			/* 将数据写入（发送）到队列中，等待时间为 0  */
//			rt_mq_send(	inputsig_mq,	/* 写入（发送）队列的ID(句柄) */
//									&data,			/* 写入（发送）的数据 */
//									1);	/* 数据的长度 */
//			//清除中断标志位
//			
//		}else
//		{
//			//GPIO_ResetBits(FPM_CONTROL_GPIO_PORT,FPM_CONTROL_GPIO_PIN);
//		}
//		EXTI_ClearITPendingBit(TOUCH_INT_EXTI_LINE);     
//	}  
//}

