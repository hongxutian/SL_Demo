
#ifndef MYAES_H
#define MYAES_H

#include "stm32f10x.h"
#include "AES.h"
#include "board.h"
#include "rtthread.h"

/**
 * 128λAES����
 * @param aes_key ��Կ��ָ����Կ��ָ�룬��Կ��СΪ16�ֽ�
 * @param data �����ܵ����ݣ�ָ�����ݵ�ָ��
 * @param datalen ���������ݵĳ���
 * @param res �洢���ܺ�����ݵ����飬16�ֽڵ������������ڻ��ߵ��ڴ����ܵ�����
 * @param reslen ���ܺ�����ݵĳ���
 */
void myaes_encrypt(uint8_t *aes_key,uint8_t *data,int16_t datalen,uint8_t *res,int16_t *reslen);

/**
 * 128λAES����
 * @param aes_key ��Կ��ָ����Կ��ָ�룬��Կ��СΪ16�ֽ�
 * @param data �����ܵ����ݣ�ָ�����ݵ�ָ��
 * @param datalen ���������ݵĳ���
 * @param res �洢���ܺ�����ݵ�����
 * @param reslen ���ܺ�����ݵĴ�С
 */
void myaes_decrypt(uint8_t *aes_key,uint8_t *data,int16_t datalen,uint8_t *res,int16_t *reslen);

#endif //MYAES_H
