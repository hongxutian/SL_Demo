#ifndef _FPM_H
#define _FPM_H

#include "stm32f10x.h"
#include "board.h"
#include "rtthread.h"

//�����ź�����
//���Ŷ���
#define TOUCH_INT_GPIO_PORT         GPIOA
#define TOUCH_INT_GPIO_CLK          (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define TOUCH_INT_GPIO_PIN          GPIO_Pin_0
#define TOUCH_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOA
#define TOUCH_INT_EXTI_PINSOURCE    GPIO_PinSource0
#define TOUCH_INT_EXTI_LINE         EXTI_Line0
#define TOUCH_INT_EXTI_IRQ          EXTI0_IRQn

#define TOUCH_IRQHandler            	EXTI0_IRQHandler

// ����2-USART2
#define  FPM_USARTx                   USART2
#define  FPM_USART_CLK                RCC_APB1Periph_USART2
#define  FPM_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  FPM_USART_BAUDRATE           19200

// USART GPIO ���ź궨��
#define  FPM_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  FPM_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  FPM_USART_TX_GPIO_PORT       GPIOA   
#define  FPM_USART_TX_GPIO_PIN        GPIO_Pin_2
#define  FPM_USART_RX_GPIO_PORT       GPIOA
#define  FPM_USART_RX_GPIO_PIN        GPIO_Pin_3

#define  FPM_USART_IRQ                USART2_IRQn
#define  FPM_USART_IRQHandler         USART2_IRQHandler


#define 	FPM_ACK_SUCCESS  						0x00	//�����ɹ�
#define		FPM_ACK_FAIL	  						0x01	//����ʧ��
#define 	FPM_ACK_FULL	  						0x04	//ָ�����ݿ�����
#define 	FPM_ACK_NOUSER   						0x05	//�޴��û�
#define 	FPM_ACK_USER_OCCUPIED 			0x06  //��ID�û��Ѵ���
#define 	FPM_ACK_USER_EXIST 					0x07 	//�û��Ѵ���
#define 	FPM_ACK_TIMEOUT  						0x08	//�ɼ���ʱ


//��������
#define FPM_CONTROL_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define FPM_CONTROL_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define FPM_CONTROL_GPIO_PIN			GPIO_Pin_4		      

#define FPM_CONTROL_DOWN GPIO_SetBits(FPM_CONTROL_GPIO_PORT,FPM_CONTROL_GPIO_PIN)
#define FPM_CONTROL_UP   GPIO_ResetBits(FPM_CONTROL_GPIO_PORT,FPM_CONTROL_GPIO_PIN)

typedef struct
{
	uint16_t num;
	uint8_t auth;
}FPM_USER_INFO_STRUC;

void FPM_Init(void);
uint8_t FPM_GetUserNumber(uint16_t *res);
uint8_t FPM_Sleep(void);
uint8_t FPM_SetAddMode(uint8_t mode);
uint8_t FPM_ReadAddMode(uint8_t *mode);
uint8_t FPM_AddUser(uint8_t cmd,uint16_t usernum,uint8_t auth,uint8_t * res);
uint8_t FPM_DeleteUser(uint16_t usernum,uint8_t * res);
uint8_t FPM_DeleteAllUser(uint8_t * res);
uint8_t FPM_CompUser(uint16_t usernum,uint8_t * res);
uint8_t FPM_CompAllUser(uint16_t *usernum,uint8_t * res);
uint8_t FPM_GetUserAuth(uint16_t usernum,uint8_t * res);
uint8_t FPM_GetAllUserInfo(uint8_t * res,uint16_t *num,FPM_USER_INFO_STRUC **userinfo);
uint8_t FPM_SetCompLevel(uint8_t level,uint8_t * res);
uint8_t FPM_ReadCompLevel(uint8_t *level,uint8_t * res);
uint8_t FPM_GetAvailableUserNumber(uint16_t *usernum,uint8_t *res);

#endif

