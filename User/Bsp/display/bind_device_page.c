#include "bind_device_page.h"
#include "board.h"
#include "string.h"
#include "UI.h"

struct Bind_Device_Page_Structure
{
	char display_buff[30];
	char display_flag;
};

struct Bind_Device_Page_Structure *bind_page_struc=RT_NULL;
void Bind_Device_Page_Init(void *param)
{
	if(bind_page_struc == RT_NULL)
	{
		bind_page_struc = (struct Bind_Device_Page_Structure *)rt_malloc(sizeof(struct Bind_Device_Page_Structure));
		strcpy(bind_page_struc->display_buff,"请在手机上输入绑定码:11234567");
		bind_page_struc->display_flag=1;
	}else
	{
		strcpy(bind_page_struc->display_buff,"请在手机上输入绑定码:11234567");
		bind_page_struc->display_flag=1;
	}
}
	

void Bind_Device_Page_Clear(void *param)
{
	if(bind_page_struc != RT_NULL)
	{
		rt_free(bind_page_struc);
		bind_page_struc = RT_NULL;
	}
}

void Bind_Device_Page_Load(void *param)
{
	bind_page_struc->display_flag=1;
}

void Bind_Device_Page_Display(void *param)
{
	if(bind_page_struc->display_flag == 1)
	{
		bind_page_struc->display_flag=0;
		OLED_GRAM_ClearScreen();
		OLED_GRAM_WriteStr(0,0,"绑定设备:");
		OLED_GRAM_WriteStr(0,16,bind_page_struc->display_buff);
		OLED_GRAM_Reflash();
	}
}
	
void Bind_Device_Page_Action(char value)
{
	if(value <= 9)
	{
		bind_page_struc->display_flag=1;
	}else if(value == 10)
	{
		UI_Page_Delete();
	}else if(value == 11)
	{
		bind_page_struc->display_flag=1;
	}else if(value == 12)
	{
		bind_page_struc->display_flag=1;
	}else if(value == 13)
	{
		UI_Page_Clear();
	}else if(value == 14)
	{
		bind_page_struc->display_flag=1;
	}else if(value == 15)
	{
		bind_page_struc->display_flag=1;
	}
}

