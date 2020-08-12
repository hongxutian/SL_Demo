//
// Created by HUAWEI on 2020/4/7.
//

#ifndef BASE64_H
#define BASE64_H

//#include <stdint-gcc.h>
#include "stm32f10x.h"

/**
 * base64�����ַ��������ܺ�õ��ַ����������׷��һ���ַ����Ľ�����\0
 * @param data �����ܵ�����
 * @param dataNum ���������ݵĳ���
 * @param result �洢���ܺ���������飬������Ĵ�С����������ݵı���Ϊ4��3
 * @param resNum ���ܺ����ݵĴ�С
 */
void Base64_EncodeStr(char *data, int16_t dataNum, char *result, int16_t *resNum);

/**
 * base64�����ֽڣ����ܺ�õ��ַ����������׷��һ���ַ����Ľ�����\0
 * @param data �����ܵ�����
 * @param dataNum ���������ݵĳ���
 * @param result �洢���ܺ���������飬������Ĵ�С����������ݵı���Ϊ4��3
 * @param resNum ���ܺ����ݵĴ�С
 */
void Base64_EncodeUChArr(uint8_t *data,int16_t dataNum,char *result,int16_t *resNum);

/**
 * base64���ܳ��ַ����������׷��һ���ַ����Ľ�����\0
 * @param data �����ܵ�����
 * @param dataNum ���������ݵĳ���
 * @param result �洢���ܺ���������飬������Ĵ�С����������ݵı���Ϊ3��4
 * @param resNum ���ܺ����ݵĴ�С
 */
void Base64_DecodeToStr(char *data,int16_t dataNum,char *result,int16_t *resNum);

/**
 * base64���ܳ��ֽ�
 * @param data �����ܵ�����
 * @param dataNum ���������ݵĳ���
 * @param result �洢���ܺ���������飬������Ĵ�С����������ݵı���Ϊ3��4
 * @param resNum ���ܺ����ݵĴ�С
 */
void Base64_DecodeToUChArr(char *data,int16_t dataNum,uint8_t *result,int16_t *resNum);

#endif //BASE64_H
