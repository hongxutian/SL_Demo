#include "manage_gen_password_page.h"
#include "board.h"
#include "string.h"
#include "UI.h"
#include "sysinit.h"

//管理普通密码的界面代码

//存储界面缓存数据的结构体
struct Manage_Gen_Password_Page_Structure
{
	char display_flag;
	char display_buff[50];
	char work_state;//0 显示密码，1询问是否删除密码，2删除成功，3删除失败
	struct General_Password_Structure *password_info;
	struct General_Password_Structure *password_info_head;
	int password_total;//表示密码总数
	int password_pos;//当前是第几个密码
};

//存储界面缓存数据的结构体的指针
struct Manage_Gen_Password_Page_Structure *managegp_page_struc=RT_NULL;

//初始化页面
char Manage_Gen_Password_Page_Init(void *param)
{
	struct General_Password_Structure *p;
	
	if(managegp_page_struc == RT_NULL)//指针为空时的初始化
	{
		//申请内存
		managegp_page_struc = (struct Manage_Gen_Password_Page_Structure *)rt_malloc(sizeof(struct Manage_Gen_Password_Page_Structure));
		managegp_page_struc->work_state=0;
		managegp_page_struc->display_flag=1;
		p=Get_General_Password(&UI_FILE);
		if(p == RT_NULL)
		{
			managegp_page_struc->password_total=0;
			managegp_page_struc->password_pos=0;
			managegp_page_struc->password_info=RT_NULL;
			managegp_page_struc->password_info_head=RT_NULL;
		}else
		{
			managegp_page_struc->password_pos=1;
			managegp_page_struc->password_info=p;
			managegp_page_struc->password_info_head=p;
			managegp_page_struc->password_total=0;
			while(p != RT_NULL)
			{
				managegp_page_struc->password_total++;
				p=p->next;
			}
		}
	}else
	{
		managegp_page_struc->work_state=0;
		managegp_page_struc->display_flag=1;
		
		if(managegp_page_struc->password_info_head != RT_NULL)
		{
			while(managegp_page_struc->password_info_head != RT_NULL)
			{
				p=managegp_page_struc->password_info_head;
				managegp_page_struc->password_info_head = managegp_page_struc->password_info_head->next;
				rt_free(p);
			}
		}
		
		p=Get_General_Password(&UI_FILE);
		if(p == RT_NULL)
		{
			managegp_page_struc->password_total=0;
			managegp_page_struc->password_pos=0;
			managegp_page_struc->password_info=RT_NULL;
			managegp_page_struc->password_info_head=RT_NULL;
		}else
		{
			managegp_page_struc->password_pos=1;
			managegp_page_struc->password_info=p;
			managegp_page_struc->password_info_head=p;
			managegp_page_struc->password_total=0;
			while(p != RT_NULL)
			{
				managegp_page_struc->password_total++;
				p=p->next;
			}
		}
	}
	return 0;
}
	
//清除	
void Manage_Gen_Password_Page_Clear(void *param)
{
	struct General_Password_Structure *p;
	if(managegp_page_struc != RT_NULL)
	{
		if(managegp_page_struc->password_info_head != RT_NULL)
		{
			while(managegp_page_struc->password_info_head != RT_NULL)
			{
				p=managegp_page_struc->password_info_head;
				managegp_page_struc->password_info_head = managegp_page_struc->password_info_head->next;
				rt_free(p);
			}
		}
		
		rt_free(managegp_page_struc);
		managegp_page_struc = RT_NULL;
	}
}

void Manage_Gen_Password_Page_Load(void *param)
{
	managegp_page_struc->display_flag=1;
}

//显示
void Manage_Gen_Password_Page_Display(void *param)
{
	if(managegp_page_struc->display_flag == 1)
	{
		managegp_page_struc->display_flag=0;
		OLED_GRAM_ClearScreen();
		OLED_GRAM_WriteStr(0,0,"管理普通密码:");
		if(managegp_page_struc->work_state == 0)
		{
			if(managegp_page_struc->password_info != RT_NULL)
			{
				sprintf(managegp_page_struc->display_buff,"总数:%d当前:%d\n%s",
				managegp_page_struc->password_total,managegp_page_struc->password_pos,managegp_page_struc->password_info->password);
			}else
			{
				sprintf(managegp_page_struc->display_buff,"没有设置密码");
			}
			OLED_GRAM_WriteStr(0,16,managegp_page_struc->display_buff);
		}else if(managegp_page_struc->work_state == 1)
		{
			sprintf(managegp_page_struc->display_buff,"是否要删除密码%d?",managegp_page_struc->password_pos);
			OLED_GRAM_WriteStr(0,16,managegp_page_struc->display_buff);
		}else if(managegp_page_struc->work_state == 2)
		{
			sprintf(managegp_page_struc->display_buff,"删除成功");
			OLED_GRAM_WriteStr(0,16,managegp_page_struc->display_buff);
		}else if(managegp_page_struc->work_state == 3)
		{
			sprintf(managegp_page_struc->display_buff,"删除失败");
			OLED_GRAM_WriteStr(0,16,managegp_page_struc->display_buff);
		}
		OLED_GRAM_Reflash();
	}
}
	
//响应输入
void Manage_Gen_Password_Page_Action(char value)
{
	struct General_Password_Structure *p;
	if(value <= 9)//此页面中输入0到9不响应
	{
		managegp_page_struc->display_flag=1;
	}else if(value == 10)
	{
		if(managegp_page_struc->work_state == 0)
		{
			UI_Page_Delete();
		}else
		{
			managegp_page_struc->display_flag=1;
			managegp_page_struc->work_state = 0;
		}
		
	}else if(value == 11)
	{
		managegp_page_struc->display_flag=1;
		if(managegp_page_struc->work_state == 0)
		{
			if(managegp_page_struc->password_info_head!=RT_NULL)
			{
				managegp_page_struc->work_state = 1;
			}
		}else if(managegp_page_struc->work_state == 1)
		{
			if(Delete_General_Password(managegp_page_struc->password_info->password,&UI_FILE) == 0)
			{
				managegp_page_struc->work_state = 2;
				if(managegp_page_struc->password_info->prev == RT_NULL)
				{
					managegp_page_struc->password_total--;
					p = managegp_page_struc->password_info;
					managegp_page_struc->password_info = managegp_page_struc->password_info->next;
					rt_free(p);
					managegp_page_struc->password_info_head=managegp_page_struc->password_info;
					if(managegp_page_struc->password_info == RT_NULL)
					{
						managegp_page_struc->password_pos=0;
					}else
					{
						managegp_page_struc->password_info->prev=RT_NULL;
					}
				}else if(managegp_page_struc->password_info->next == RT_NULL)
				{
					managegp_page_struc->password_total--;
					p = managegp_page_struc->password_info;
					managegp_page_struc->password_info = managegp_page_struc->password_info->prev;
					rt_free(p);
					if(managegp_page_struc->password_info == RT_NULL)
					{
						managegp_page_struc->password_info_head=RT_NULL;
						managegp_page_struc->password_pos=0;
					}else
					{
						managegp_page_struc->password_pos--;
						managegp_page_struc->password_info->next=RT_NULL;
					}
				}else 
				{
					managegp_page_struc->password_total--;
					p = managegp_page_struc->password_info;
					managegp_page_struc->password_info = p->next;
					managegp_page_struc->password_info->prev = p->prev;
					p->prev->next=managegp_page_struc->password_info;
					rt_free(p);
				}
			}else
			{
				managegp_page_struc->work_state = 3;
			}
		}else if(managegp_page_struc->work_state == 2 || managegp_page_struc->work_state == 3)
		{
			managegp_page_struc->work_state = 0;
		}
	}else if(value == 12)
	{
		managegp_page_struc->display_flag=1;
	}else if(value == 13)
	{
		UI_Page_Clear();
	}else if(value == 14)
	{
		managegp_page_struc->display_flag=1;
		if(managegp_page_struc->password_info->prev != RT_NULL)
		{
			managegp_page_struc->password_info=managegp_page_struc->password_info->prev;
			managegp_page_struc->password_pos--;
		}
	}else if(value == 15)
	{
		managegp_page_struc->display_flag=1;
		if(managegp_page_struc->password_info->next != RT_NULL)
		{
			managegp_page_struc->password_info=managegp_page_struc->password_info->next;
			managegp_page_struc->password_pos++;
		}
	}
}

