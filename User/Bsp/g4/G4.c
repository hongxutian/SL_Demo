#include "G4.h"
#include "board.h"

G4_UART_BUFF g4_buff[5];
G4_UART_BUFF *g4_buff_p=&g4_buff[0];
uint8_t g4_buff_count=0;

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = G4_USART_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void G4_Usart_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	G4_USART_GPIO_APBxClkCmd(G4_USART_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	G4_USART_APBxClkCmd(G4_USART_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = G4_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(G4_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = G4_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(G4_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = G4_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(G4_USARTx, &USART_InitStructure);
	
	// �����ж����ȼ�����
	NVIC_Configuration();
	
	// ʹ�ܴ��ڽ����ж�
	
	USART_ITConfig(G4_USARTx, USART_IT_RXNE, ENABLE);	
	USART_ITConfig(G4_USARTx, USART_IT_IDLE, ENABLE);	
	
	// ʹ�ܴ���
	USART_Cmd(G4_USARTx, ENABLE);	    
}

/*****************  ����һ���ֽ� **********************/
void G4_Usart_SendByte(uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(G4_USARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(G4_USARTx, USART_FLAG_TXE) == RESET);	
}

/****************** ����8λ������ ************************/
void G4_Usart_SendArray(uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    G4_Usart_SendByte(array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(G4_USARTx,USART_FLAG_TC)==RESET);
}

/*****************  �����ַ��� **********************/
void G4_Usart_SendString(char *str)
{
	unsigned int k=0;
  do 
  {
      G4_Usart_SendByte( *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(G4_USARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  ����һ��16λ�� **********************/
void G4_Usart_SendHalfWord(uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(G4_USARTx,temp_h);	
	while (USART_GetFlagStatus(G4_USARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(G4_USARTx,temp_l);	
	while (USART_GetFlagStatus(G4_USARTx, USART_FLAG_TXE) == RESET);	
}

void G4_USART_IRQHandler(void)
{
	uint8_t chTemp;
	static int16_t getnum=0;
	if ( USART_GetITStatus ( G4_USARTx, USART_IT_RXNE ) != RESET )
	{
		chTemp=USART_ReceiveData( G4_USARTx ); 
		g4_buff_p->buff[getnum]=chTemp;
		if(getnum < G4_BUFF_SIZE_MAX)
		{
			getnum++;
		}
	}else if ( USART_GetITStatus( G4_USARTx, USART_IT_IDLE ) == SET ) 
	{
		chTemp=USART_ReceiveData( G4_USARTx ); 
		g4_buff_p->buff[getnum] = '\0';
		g4_buff_p->num = getnum;
		getnum = 0;
		rt_mb_send(g4mb,(rt_uint32_t)g4_buff_p);
		g4_buff_count = (g4_buff_count + 1)%5;
		g4_buff_p = &g4_buff[g4_buff_count];
	}
}
