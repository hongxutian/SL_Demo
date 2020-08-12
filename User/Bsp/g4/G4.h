#ifndef __G4_H
#define	__G4_H


#include "stm32f10x.h"
#include <stdio.h>


// 串口4-UART4
#define  G4_USARTx                   UART4
#define  G4_USART_CLK                RCC_APB1Periph_UART4
#define  G4_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  G4_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  G4_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC)
#define  G4_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  G4_USART_TX_GPIO_PORT       GPIOC   
#define  G4_USART_TX_GPIO_PIN        GPIO_Pin_10
#define  G4_USART_RX_GPIO_PORT       GPIOC
#define  G4_USART_RX_GPIO_PIN        GPIO_Pin_11

#define  G4_USART_IRQ                UART4_IRQn
#define  G4_USART_IRQHandler         UART4_IRQHandler

#define  G4_BUFF_SIZE_MAX            1024

typedef struct{
	uint16_t num;
	uint8_t buff[G4_BUFF_SIZE_MAX];
}G4_UART_BUFF;

void G4_Usart_Config(void);
void G4_Usart_SendByte(uint8_t ch);
void G4_Usart_SendString(char *str);
void G4_Usart_SendHalfWord(uint16_t ch);
void G4_Usart_SendArray(uint8_t *array, uint16_t num);

#endif /* __USART_H */


