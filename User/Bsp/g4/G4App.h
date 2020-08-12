#ifndef __G4APP_H
#define	__G4APP_H

#include "stm32f10x.h"

void G4_Thread_Entry(void *parameter);
uint8_t G4_Cmd ( char * cmd, char * reply1, char * reply2, uint32_t waittime, uint32_t prewaittime);
uint8_t G4_EnterATMode(void);
uint8_t G4_TestATCmd(void);
uint8_t G4_Init(void);
uint8_t G4_Net_Config(void);
uint8_t G4_Net_Connect(char *ip,char *port);
void G4APP_Rece_Thread_Entry(void *parameter);
void G4APP_Send_Thread_Entry(void *parameter);

#endif

