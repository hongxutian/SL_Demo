#include "G4.h"
#include "board.h"

G4_UART_BUFF g4_buff[5];
G4_UART_BUFF *g4_buff_p=&g4_buff[0];
uint8_t g4_buff_count=0;

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = G4_USART_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void G4_Usart_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	G4_USART_GPIO_APBxClkCmd(G4_USART_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	G4_USART_APBxClkCmd(G4_USART_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = G4_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(G4_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = G4_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(G4_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = G4_USART_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(G4_USARTx, &USART_InitStructure);
	
	// 串口中断优先级配置
	NVIC_Configuration();
	
	// 使能串口接收中断
	
	USART_ITConfig(G4_USARTx, USART_IT_RXNE, ENABLE);	
	USART_ITConfig(G4_USARTx, USART_IT_IDLE, ENABLE);	
	
	// 使能串口
	USART_Cmd(G4_USARTx, ENABLE);	    
}

/*****************  发送一个字节 **********************/
void G4_Usart_SendByte(uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(G4_USARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(G4_USARTx, USART_FLAG_TXE) == RESET);	
}

/****************** 发送8位的数组 ************************/
void G4_Usart_SendArray(uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* 发送一个字节数据到USART */
	    G4_Usart_SendByte(array[i]);	
  
  }
	/* 等待发送完成 */
	while(USART_GetFlagStatus(G4_USARTx,USART_FLAG_TC)==RESET);
}

/*****************  发送字符串 **********************/
void G4_Usart_SendString(char *str)
{
	unsigned int k=0;
  do 
  {
      G4_Usart_SendByte( *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(G4_USARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  发送一个16位数 **********************/
void G4_Usart_SendHalfWord(uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(G4_USARTx,temp_h);	
	while (USART_GetFlagStatus(G4_USARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
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

