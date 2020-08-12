#include "menu_page.h"
#include "board.h"
#include "string.h"
#include "UI.h"
#include "bind_device_page.h"
#include "query_user_page.h"
#include "modify_manager_password_page.h"
#include "add_gen_password_page.h"
#include "manage_gen_password_page.h"

char MENU_ITEM[5][17]=
{
	"绑定设备",
	"查看用户",
	"修改管理员密码",
	"管理普通密码",
	"添加普通密码"
};

struct Menu_Page_Structure
{
	char point;
	char top;
	char display_flag;
};

struct Menu_Page_Structure *menu_page_struc=RT_NULL;

//初始化页面
char Menu_Page_Init(void *param)
{
	if(menu_page_struc == RT_NULL)
	{
		menu_page_struc = (struct Menu_Page_Structure *)rt_malloc(sizeof(struct Menu_Page_Structure));
		menu_page_struc->point=0;
		menu_page_struc->top=0;
		menu_page_struc->display_flag=1;
	}else
	{
		menu_page_struc->point=0;
		menu_page_struc->top=0;
		menu_page_struc->display_flag=1;
	}
	return 0;
}
	
//清除	
void Menu_Page_Clear(void *param)
{
	if(menu_page_struc != RT_NULL)
	{
		rt_free(menu_page_struc);
		menu_page_struc = RT_NULL;
	}
}

void Menu_Page_Load(void *param)
{
	menu_page_struc->display_flag=1;
}

//显示
void Menu_Page_Display(void *param)
{
	char i;
	if(menu_page_struc->display_flag == 1)
	{
		menu_page_struc->display_flag=0;
		OLED_GRAM_ClearScreen();
		OLED_GRAM_WriteStr(0,0,"菜单:");
		for(i=1;i<=3;i++)
		{
			OLED_GRAM_WriteStr(0,16*i,MENU_ITEM[menu_page_struc->top+i-1]);
		}
		i=menu_page_struc->point-menu_page_struc->top;
		OLED_GRAM_Rectangle(0,16*(i+1),127,16*(i+2)-1);
		OLED_GRAM_Reflash();
	}
}
	
//响应输入
void Menu_Page_Action(char value)
{
	if(value <= 9)
	{
		menu_page_struc->display_flag=1;
	}else if(value == 10)
	{
		UI_Page_Clear();
	}else if(value == 11)
	{
		if(menu_page_struc->point==0)
		{
			UI_Page_Add(Bind_Device_Page_Init,Bind_Device_Page_Clear,Bind_Device_Page_Display,Bind_Device_Page_Load,Bind_Device_Page_Action,RT_NULL);
		}else if(menu_page_struc->point==1)
		{
			UI_Page_Add(Query_User_Page_Init,Query_User_Page_Clear,Query_User_Page_Display,Query_User_Page_Load,Query_User_Page_Action,RT_NULL);
		}else if(menu_page_struc->point==2)
		{
			UI_Page_Add(Modify_Manager_Password_Page_Init,Modify_Manager_Password_Page_Clear,Modify_Manager_Password_Page_Display,Modify_Manager_Password_Page_Load,Modify_Manager_Password_Page_Action,RT_NULL);
		}else if(menu_page_struc->point==3)
		{
			UI_Page_Add(Manage_Gen_Password_Page_Init,Manage_Gen_Password_Page_Clear,Manage_Gen_Password_Page_Display,Manage_Gen_Password_Page_Load,Manage_Gen_Password_Page_Action,RT_NULL);
		}else if(menu_page_struc->point==4)
		{
			UI_Page_Add(Add_Gen_Password_Page_Init,Add_Gen_Password_Page_Clear,Add_Gen_Password_Page_Display,Add_Gen_Password_Page_Load,Add_Gen_Password_Page_Action,RT_NULL);
		}
	}else if(value == 12)
	{
		menu_page_struc->display_flag=1;
	}else if(value == 13)
	{
		UI_Page_Clear();
	}else if(value == 14)
	{
		if(menu_page_struc->point>0)
		{
			menu_page_struc->point--;
			if(menu_page_struc->point<menu_page_struc->top)
			{
				menu_page_struc->top--;
			}
		}
		menu_page_struc->display_flag=1;
	}else if(value == 15)
	{
		if(menu_page_struc->point<4)
		{
			menu_page_struc->point++;
			if(menu_page_struc->point>menu_page_struc->top+2)
			{
				menu_page_struc->top++;
			}
		}
		menu_page_struc->display_flag=1;
	}
}

