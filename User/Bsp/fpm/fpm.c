#include "fpm.h"

uint8_t buff[5120];
uint16_t bufflen = 0;

static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = FPM_USART_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
	
//	/* ����NVICΪ���ȼ���1 */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//  
//  /* �����ж�Դ������1 */
//  NVIC_InitStructure.NVIC_IRQChannel = TOUCH_INT_EXTI_IRQ;
//  /* ������ռ���ȼ� */
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  /* ���������ȼ� */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* ʹ���ж�ͨ�� */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
}

static void FPM_USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	// �򿪴���GPIO��ʱ��
	FPM_USART_GPIO_APBxClkCmd(FPM_USART_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	FPM_USART_APBxClkCmd(FPM_USART_CLK, ENABLE);
	
	// ���������ź����ʱ��
	RCC_APB2PeriphClockCmd(TOUCH_INT_GPIO_CLK,ENABLE);
	
	RCC_APB2PeriphClockCmd( FPM_TOUCH_VOL_CONTROL_GPIO_CLK | FPM_WORK_VOL_CONTROL_GPIO_CLK, ENABLE);
	
	
	// �ж����ȼ�����
	NVIC_Configuration();
	
	//���ô����źŵ�����
	//------------------------------------------------------------------------
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = TOUCH_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(TOUCH_INT_GPIO_PORT, &GPIO_InitStructure);

//	/* ѡ��EXTI���ź�Դ */
//  GPIO_EXTILineConfig(TOUCH_INT_EXTI_PORTSOURCE, TOUCH_INT_EXTI_PINSOURCE); 
//  EXTI_InitStructure.EXTI_Line = TOUCH_INT_EXTI_LINE;
//	
//	/* EXTIΪ�ж�ģʽ */
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	/* �������ж� */
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//  /* ʹ���ж� */	
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




	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = FPM_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FPM_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = FPM_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(FPM_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = FPM_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(FPM_USARTx, &USART_InitStructure);
	
	
	
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(FPM_USARTx, USART_IT_RXNE, ENABLE);	
	USART_ITConfig(FPM_USARTx, USART_IT_IDLE, ENABLE);	
	
	// ʹ�ܴ���
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
  * @brief  ���ָ��ģ���Ƿ񱻰���
  * @param  ��
  * @retval 0��ʾû�а��£�1��ʾ����
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
  * @brief  ��ȡָ��ģ���е��û���
  * @param  res ���ص��û���
  * @retval 0��ʾresֵ��Ч��1��ʾresֵ��Ч
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
  * @brief  ��ȡָ��ģ��������õ�
  * @param  res ���ز�ѯ��� usernum��Ч���û��ţ���res=0ʱ��Ч
  * @retval 0��ʾresֵ��Ч��1��ʾresֵ��Ч
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
  * @brief  ʹģ���������״̬
  * @param  ��
  * @retval 0��ʾ�ɹ���1��ʾʧ��
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
  * @brief  ����ָ�����ģʽ
  * @param  mode ģʽ��0����ָ���ظ���1������ָ���ظ�
  * @retval 0��ʾ�ɹ���1��ʾʧ��
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
  * @brief  ��ȡָ�����ģʽ
  * @param  mode ����ָ�����ģʽ��0����ָ���ظ���1������ָ���ظ�
  * @retval 0��ʾ�ɹ���1��ʾʧ��
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
  * @brief  ���ָ��
  * @param  cmd�������0x01/0x02/0x03,usernum�û���,auth�û�Ȩ��1/2/3,res���صĽ��
  * @retval 0��ʾ�����ɹ�ģ���з�Ӧ��1��ʾʧ��
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
  * @brief  ɾ��ָ��
  * @param  usernum�û���,res���صĽ��
  * @retval 0��ʾ�����ɹ�ģ���з�Ӧ��1��ʾʧ��
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
  * @brief  ɾ������ָ��
  * @param  usernum�û���,res���صĽ��
  * @retval 0��ʾ�����ɹ�ģ���з�Ӧ��1��ʾʧ��
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
  * @brief  �ȶ�ָ��
  * @param  usernum�û���,res���صĽ��
  * @retval 0��ʾ�����ɹ�ģ���з�Ӧ��1��ʾʧ��
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
  * @brief  �ȶ�ָ��
  * @param  usernum�ȶԽ���û���,res���صĽ��
  * @retval 0��ʾ�����ɹ�ģ���з�Ӧ��1��ʾʧ��
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
  * @brief  ��ȡ�û���Ȩ��
  * @param  usernum�û���,res���صĽ��
  * @retval 0��ʾ�����ɹ�ģ���з�Ӧ��1��ʾʧ��
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
  * @brief  ��ȡ�����û�����Ϣ
  * @param  num�û�����,res���صĽ����userinfo�û���Ϣ
  * @retval 0��ʾ�����ɹ�ģ���з�Ӧ��1��ʾʧ��
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
	//�������ͷ
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
  * @brief  ���ñȶԵȼ�
  * @param  level�ȶԵȼ�,res���صĽ��
  * @retval 0��ʾ�����ɹ�ģ���з�Ӧ��1��ʾʧ��
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
  * @brief  ��ȡ�ȶԵȼ�
  * @param  level�ȶԵȼ�,res���صĽ��
  * @retval 0��ʾ�����ɹ�ģ���з�Ӧ��1��ʾʧ��
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
//	//ȷ���Ƿ������EXTI Line�ж�
//	if(EXTI_GetITStatus(TOUCH_INT_EXTI_LINE) != RESET) 
//	{
//		t = GPIO_ReadInputDataBit(TOUCH_INT_GPIO_PORT,TOUCH_INT_GPIO_PIN);
//		//rt_kprintf("\nfinger touch,t=%d",t);
//		if(t == 1)
//		{
//			FPM_TOUCH_VOL_CONTROL_UP;
//			/* ������д�루���ͣ��������У��ȴ�ʱ��Ϊ 0  */
//			rt_mq_send(	inputsig_mq,	/* д�루���ͣ����е�ID(���) */
//									&data,			/* д�루���ͣ������� */
//									1);	/* ���ݵĳ��� */
//			//����жϱ�־λ
//			
//		}else
//		{
//			//GPIO_ResetBits(FPM_CONTROL_GPIO_PORT,FPM_CONTROL_GPIO_PIN);
//		}
//		EXTI_ClearITPendingBit(TOUCH_INT_EXTI_LINE);     
//	}  
//}

