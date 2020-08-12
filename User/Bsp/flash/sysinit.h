#ifndef __SYSINIT_H
#define __SYSINIT_H

#include "board.h"
#include "ff.h"

extern FIL T_FILE;;

struct User_Info_Structure
{
	char name[20];
	char number[10];
	struct User_Info_Structure *prev;
	struct User_Info_Structure *next;
};

struct General_Password_Structure
{
	char password[20];
	struct General_Password_Structure *prev;
	struct General_Password_Structure *next;
};

struct Temporary_Password_Structure
{
	char password[20];//
	uint8_t type;//0验证一次后删除，1超过有效期后删除，2永久有效
	uint32_t effective_time;//有效的时长
	uint32_t write_time;//写入的时间
	struct Temporary_Password_Structure *prev;
	struct Temporary_Password_Structure *next;
};


extern FATFS fs;	

void systeminit(void);
uint8_t taskinit(void);

struct User_Info_Structure * Parse_User_Info(char *data);

char Delete_User(char *number,FIL *file);
char Add_User(char *user,FIL *file);
struct User_Info_Structure * Get_User_Info(char *number,FIL *file);
struct User_Info_Structure * Get_All_User_Info(FIL *file);
char Check_Manager_Password(char *password,FIL *file);
char Modify_Manager_Password(char *password,FIL *file);
char Check_General_Password(char *password,FIL *file);
char Delete_General_Password(char *password,FIL *file);
char Add_General_Password(char *password,FIL *file);
struct General_Password_Structure * Get_General_Password(FIL *file);


char Check_Temporary_Password(char *password,FIL *file);
char Add_Temporary_Password(char *password,uint8_t type,uint32_t effective_time,uint32_t write_time,FIL *file);





#endif

