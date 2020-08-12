#include "add_user_page.h"
#include "board.h"
#include "string.h"
#include "UI.h"
#include "cJSON.h" 
#include "sysinit.h"

struct Add_User_Page_Structure
{
	char display_buff[50];
	char display_flag;
	char work_state;
	char error_cnt;
	char user_info[50];
	uint16_t usernum;
};

struct Add_User_Page_Structure *adu_struc=RT_NULL;
char Add_User_Page_Init(void *param)
{
	uint8_t i,res;
	uint16_t num;
	if(adu_struc == RT_NULL)
	{
		adu_struc = (struct Add_User_Page_Structure *)rt_malloc(sizeof(struct Add_User_Page_Structure));
		strcpy(adu_struc->user_info,param);
		rt_kprintf("\nuser name=%s",adu_struc->user_info);
		adu_struc->display_flag=1;
		adu_struc->error_cnt=0;
		
		i=FPM_GetAvailableUserNumber(&num,&res);
		if(i==0)
		{
			if(res == FPM_ACK_SUCCESS)
			{
				adu_struc->usernum=num;
				strcpy(adu_struc->display_buff,"按确定键开始录入指纹");
				adu_struc->work_state=0;
			}else
			{
				strcpy(adu_struc->display_buff,"用户已满,不能增加");
				adu_struc->work_state=4;
			}
		}else
		{
			strcpy(adu_struc->display_buff,"指纹模块出现错误");
			adu_struc->work_state=4;
		}
		return 0;
	}else
	{
		return 1;
	}
}
	

void Add_User_Page_Clear(void *param)
{
	cJSON *jsend;
	char *out;
	if(adu_struc != RT_NULL)
	{
//		if(adu_struc->work_state != 4 && adu_struc->work_state != 5)
//		{
//			jsend=cJSON_CreateObject();
//			cJSON_AddStringToObject(jsend,"type","addUser");
//			cJSON_AddStringToObject(jsend,"result","fail");
//			out=cJSON_PrintUnformatted(jsend);
//			rt_mq_send(g4msgmq,out,(strlen(out)+1));
//			rt_free(out);
//			cJSON_Delete(jsend);	
//		}
		rt_free(adu_struc);
		adu_struc=RT_NULL;
	}
}

void Add_User_Page_Load(void *param)
{
	adu_struc->display_flag=1;
}

void Add_User_Page_Display(void *param)
{
	uint8_t i,res;
	uint16_t temp;
	cJSON *jsend;
	char *out;
	
	if(adu_struc->display_flag == 1)
	{
		adu_struc->display_flag=0;
		OLED_GRAM_ClearScreen();
		OLED_GRAM_WriteStr(0,0,"增加用户:");
		if(adu_struc->work_state == 0)
		{
			sprintf(adu_struc->display_buff,"按确定键开始录入指纹");
			OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
			OLED_GRAM_Reflash();
		}else if(adu_struc->work_state == 1)
		{
			sprintf(adu_struc->display_buff,"将手指放在指纹传感器上采集指纹");
			OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
			OLED_GRAM_Reflash();
			
			i=FPM_AddUser(0x01,adu_struc->usernum,0x01,&res);
			if(i != 0)
			{
				adu_struc->work_state=4;
				FPM_GetUserNumber(&temp);
				sprintf(adu_struc->display_buff,"录入失败");
				OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
				OLED_GRAM_Reflash();
			}else if(res != 0)
			{
				sprintf(adu_struc->display_buff,"指纹错误,按确定键继续");
				OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
				OLED_GRAM_Reflash();
			}else
			{
				sprintf(adu_struc->display_buff,"集到指纹,按确定键继续");
				OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
				OLED_GRAM_Reflash();
			}
		}else if(adu_struc->work_state == 2)
		{
			sprintf(adu_struc->display_buff,"将手指放在指纹传感器上采集指纹");
			OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
			OLED_GRAM_Reflash();
			
			i=FPM_AddUser(0x02,adu_struc->usernum,0x01,&res);
			if(i != 0)
			{
				adu_struc->work_state=4;
				FPM_GetUserNumber(&temp);
				sprintf(adu_struc->display_buff,"录入失败");
				OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
				OLED_GRAM_Reflash();
			}else if(res != 0)
			{
				sprintf(adu_struc->display_buff,"指纹错误,按确定键继续");
				OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
				OLED_GRAM_Reflash();
			}else
			{
				sprintf(adu_struc->display_buff,"集到指纹,按确定键继续");
				OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
				OLED_GRAM_Reflash();
			}
		}else if(adu_struc->work_state == 3)
		{
			sprintf(adu_struc->display_buff,"将手指放在指纹传感器上采集指纹");
			OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
			OLED_GRAM_Reflash();
			
			i=FPM_AddUser(0x03,adu_struc->usernum,0x01,&res);
			if(i != 0)
			{
				adu_struc->work_state=4;
				FPM_GetUserNumber(&temp);
				sprintf(adu_struc->display_buff,"录入失败");
				OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
				OLED_GRAM_Reflash();
			}else if(res != 0)
			{
				adu_struc->work_state=4;
				sprintf(adu_struc->display_buff,"指纹错误,按确定键继续");
				OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
				OLED_GRAM_Reflash();
			}else
			{
				adu_struc->work_state=4;
				sprintf(adu_struc->display_buff,"指纹录入成功");
				OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
				OLED_GRAM_Reflash();
				sprintf(adu_struc->display_buff,"%s %d",adu_struc->user_info,adu_struc->usernum);
				Add_User(adu_struc->display_buff,&UI_FILE);
			}
		}else if(adu_struc->work_state == 4)
		{
			OLED_GRAM_WriteStr(0,16,adu_struc->display_buff);
			OLED_GRAM_Reflash();
		}
//		if(adu_struc->work_state == 4)
//		{
//			jsend=cJSON_CreateObject();
//			cJSON_AddStringToObject(jsend,"type","addUser");
//			cJSON_AddStringToObject(jsend,"result","fail");
//			out=cJSON_PrintUnformatted(jsend);
//			rt_mq_send(g4msgmq,out,(strlen(out)+1));
//			rt_free(out);
//			cJSON_Delete(jsend);	
//		}else if(adu_struc->work_state == 5)
//		{
//			jsend=cJSON_CreateObject();
//			cJSON_AddStringToObject(jsend,"type","addUser");
//			cJSON_AddStringToObject(jsend,"result","success");
//			cJSON_AddNumberToObject(jsend,"number",adu_struc->usernum);
//			out=cJSON_PrintUnformatted(jsend);
//			rt_mq_send(g4msgmq,out,(strlen(out)+1));
//			rt_free(out);
//			cJSON_Delete(jsend);	
//		}
	}
}
	
void Add_User_Page_Action(char value)
{
	if(value <= 9)
	{
		;
	}else if(value == 10)
	{
		UI_Page_Delete();
	}else if(value == 11)
	{
		if(adu_struc->work_state == 0)
		{
			adu_struc->work_state = 1;
			adu_struc->display_flag=1;
		}else if(adu_struc->work_state == 1)
		{
			adu_struc->work_state = 2;
			adu_struc->display_flag=1;
		}else if(adu_struc->work_state == 2)
		{
			adu_struc->work_state = 3;
			adu_struc->display_flag=1;
		}else if(adu_struc->work_state == 4)
		{
			UI_Page_Delete();
		}else if(adu_struc->work_state == 5)
		{
			UI_Page_Delete();
		}
	}else if(value == 12)
	{
		;
	}else if(value == 13)
	{
		UI_Page_Clear();
	}else if(value == 14)
	{
		;
	}else if(value == 15)
	{
		;
	}
}

