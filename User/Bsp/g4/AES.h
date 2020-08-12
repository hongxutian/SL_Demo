#ifndef _AES_H_
#define _AES_H_
#include "stm32f10x.h"
#include <stdbool.h>
#include "board.h"
#include "rtthread.h"


#define u8          uint8_t
#define u16         uint16_t

#define AES_KEY_LENGTH	  16//��Կ,����Ϊ16,24,32�ֽ�(128 192 256λ),����Ϊ��������
#define AES_IV_LENGTH	  16//���鳤�ȱ���16ֱ�ӣ���ʼ������Ҳ����Ϊ16�ֽ�,����Ϊ��������
#define BPOLY           0x1B//GF(28)����ʽ 0x1B=00011011 (x^4 + x^3 + x + 1)

/*
AES	      ��Կ���� 	���鳤��(AES_IV����) 	��������
AES-128      16           16	               10
AES-192	     24	          16	               12
AES-256      32           16	               14
*/
// �ӽ���ģʽ
#define AES_MODE_ECB	0				// �������뱾ģʽ��һ��ģʽ��
#define AES_MODE_CBC	1				// �����������ģʽ
#define AES_MODE		AES_MODE_ECB

#define Nk	(AES_KEY_LENGTH / 4)		// �ԡ��֡���4�ֽڣ�Ϊ��λ����Կ����
#define Nb	                  4			// �ԡ��֡���4�ֽڣ�Ϊ��λ�ļӽ������ݿ��С���̶�Ϊ4

// Nr�����ܵ�����
#if   AES_KEY_LENGTH == 16
	#define Nr	10
#elif AES_KEY_LENGTH == 24
	#define Nr	12
#elif AES_KEY_LENGTH == 32
	#define Nr	14
#else
	#error AES_KEY_LENGTH must be 16, 24 or 32 BOOLs!
#endif
 
///////////////////////////////////////////////////////////////////////////////
//	��������	AES_Init
//	������		��ʼ�����ڴ�ִ����չ��Կ������
//	���������	pKey  -- ԭʼ��Կ  ���䳤�ȱ���Ϊ AES_KEY_LENGTH�ֽڡ�
//	���������	pIV   -- ��ʼ���������䳤�ȱ���Ϊ AES_IV_LENGTH�ֽڡ�
///////////////////////////////////////////////////////////////////////////////
void AES_Init(u8 *pKey,u8 *pIV);

//////////////////////////////////////////////////////////////////////////
//	��������	AES_Encrypt
//	������		��������
//	���������	pPlainText	-- ���ģ�������ܵ����ݣ��䳤��ΪnDataLen�ֽڡ�
//				nDataLen	-- ���ݳ��ȣ����ֽ�Ϊ��λ������ΪAES_KEY_LENGTH����������
//	���������	pCipherText	-- ���ģ��������ļ��ܺ�����ݣ�������pPlainText��ͬ��
//////////////////////////////////////////////////////////////////////////
void AES_Encrypt(u8 *pPlainText,u16 nDataLen,u8 *pCipherText);
void AES_Encrypt_Oneself(u8 *pPlainText,u16 nDataLen); //���ܵ�ԭ����

//////////////////////////////////////////////////////////////////////////
//	��������	AES_Decrypt
//	������		��������
//	���������	pCipherText -- ���ģ�������ܵ����ݣ��䳤��ΪnDataLen�ֽڡ�
//				nDataLen	-- ���ݳ��ȣ����ֽ�Ϊ��λ������ΪAES_KEY_LENGTH����������
//	���������	pPlainText  -- ���ģ��������Ľ��ܺ�����ݣ�������pCipherText��ͬ��
//////////////////////////////////////////////////////////////////////////
void AES_Decrypt(u8 *pCipherText,u16 nDataLen,u8 *pPlainText);
void AES_Decrypt_Oneself(u8 *pCipherText,u16 nDataLen); //���ܵ�ԭ����

void AES_TEST(void);

#endif
