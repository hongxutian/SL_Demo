#ifndef DEMO1_CRC_H
#define DEMO1_CRC_H

#include "stm32f10x.h"

/**
 * ����CRCУ���ֵ
 * @param ptr ����
 * @param len ���ݳ���
 * @return CRCֵ
 */
uint16_t crc16bitbybit(uint8_t *ptr, uint16_t len);

/**
 * ����CRCУ���ֵ
 * @param ptr ����
 * @param len ���ݳ���
 * @return CRCֵ
 */
uint16_t crc16table(uint8_t *ptr, uint16_t len);

/**
 * ����CRCУ���ֵ
 * @param ptr ����
 * @param len ���ݳ���
 * @return CRCֵ
 */
uint16_t crc16tablefast(uint8_t *ptr, uint16_t len);

#endif //DEMO1_CRC_H
