#include "msg_page.h"
#include "board.h"
#include "string.h"
#include "UI.h"

struct Msg_Page_Structure
{
	char display_buff[65];
	char display_flag;
	struct Msg_Page_Structure *next;
};

struct Msg_Page_Structure *msg_struc=RT_NULL;
void Msg_Page_Init(void *param)
{
	struct Msg_Page_Structure *p;
	if(msg_struc == RT_NULL)
	{
		msg_struc = (struct Msg_Page_Structure *)rt_malloc(sizeof(struct Msg_Page_Structure));
		msg_struc->next=RT_NULL;
		strcpy(msg_struc->display_buff,param);
		msg_struc->display_flag=1;
	}else
	{
		p = (struct Msg_Page_Structure *)rt_malloc(sizeof(struct Msg_Page_Structure));
		p->next=msg_struc;
		msg_struc=p;
		strcpy(msg_struc->display_buff,param);
		msg_struc->display_flag=1;
	}
}
	

void Msg_Page_Clear(void *param)
{
	struct Msg_Page_Structure *p;
	if(msg_struc != RT_NULL)
	{
		p=msg_struc->next;
		rt_free(msg_struc);
		msg_struc = p;
	}
}

void Msg_Page_Load(void *param)
{
	msg_struc->display_flag=1;
}

void Msg_Page_Display(void *param)
{
	
	if(msg_struc->display_flag == 1)
	{
		msg_struc->display_flag=0;
		OLED_GRAM_ClearScreen();
		OLED_GRAM_WriteStr(0,0,"ÏûÏ¢ÌáÐÑ:");
		OLED_GRAM_WriteStr(0,16,msg_struc->display_buff);
		OLED_GRAM_Reflash();
	}
}
	
void Msg_Page_Action(char value)
{
	if(value <= 9)
	{
		msg_struc->display_flag=1;
	}else if(value == 10)
	{
		UI_Page_Delete();
	}else if(value == 11)
	{
		UI_Page_Delete();
	}else if(value == 12)
	{
		msg_struc->display_flag=1;
	}else if(value == 13)
	{
		UI_Page_Clear();
	}else if(value == 14)
	{
		msg_struc->display_flag=1;
	}else if(value == 15)
	{
		msg_struc->display_flag=1;
	}
}

