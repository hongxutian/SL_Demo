#ifndef __BSP_RTC_H
#define	__BSP_RTC_H


#include "stm32f10x.h"


//使用LSE外部时钟 或 LSI内部时钟
#define RTC_CLOCK_SOURCE_LSE      
//#define RTC_CLOCK_SOURCE_LSI



#define RTC_BKP_DRX          BKP_DR1
// 写入到备份寄存器的数据宏定义
#define RTC_BKP_DATA         0xA5A5




void RTC_Configuration(void);
void Time_Adjust(uint32_t tm);
void RTC_CheckAndConfig(uint32_t tm);
uint32_t Get_RTC_Current_Time(void);
void Set_RTC_Current_Time(uint32_t tm);

#endif /* __XXX_H */
