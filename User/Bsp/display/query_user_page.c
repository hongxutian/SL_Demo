#include "query_user_page.h"
#include "board.h"
#include "string.h"
#include "UI.h"
#include "sysinit.h"


struct Query_User_Page_Structure
{
	char display_flag;
	char display_buff[50];
	struct User_Info_Structure *user_info;
	struct User_Info_Structure *user_info_head;
	int user_total;//表示用户的总数
	int user_pos;//当前是第几个用户
};

struct Query_User_Page_Structure *query_user_page_struc=RT_NULL;

//初始化页面
char Query_User_Page_Init(void *param)
{
	struct User_Info_Structure *p;
	if(query_user_page_struc == RT_NULL)
	{
		query_user_page_struc = (struct Query_User_Page_Structure *)rt_malloc(sizeof(struct Query_User_Page_Structure));
		p=Get_All_User_Info(&UI_FILE);
		if(p == RT_NULL)
		{
			query_user_page_struc->display_flag=1;
			query_user_page_struc->user_total=0;
			query_user_page_struc->user_pos=0;
			query_user_page_struc->user_info=RT_NULL;
			query_user_page_struc->user_info_head=RT_NULL;
		}else
		{
			query_user_page_struc->user_pos=1;
			query_user_page_struc->user_info=p;
			query_user_page_struc->user_info_head=p;
			query_user_page_struc->user_total=0;
			while(p != RT_NULL)
			{
				query_user_page_struc->user_total++;
				p=p->next;
			}
		}
	}else
	{
		if(query_user_page_struc->user_info_head != RT_NULL)
		{
			while(query_user_page_struc->user_info_head != RT_NULL)
			{
				p=query_user_page_struc->user_info_head;
				query_user_page_struc->user_info_head = query_user_page_struc->user_info_head->next;
				rt_free(p);
			}
		}
		
//		query_user_page_struc = (struct Query_User_Page_Structure *)rt_malloc(sizeof(struct Query_User_Page_Structure));
		p=Get_All_User_Info(&UI_FILE);
		if(p == RT_NULL)
		{
			query_user_page_struc->display_flag=1;
			query_user_page_struc->user_total=0;
			query_user_page_struc->user_pos=0;
			query_user_page_struc->user_info=RT_NULL;
			query_user_page_struc->user_info_head=RT_NULL;
		}else
		{
			query_user_page_struc->user_pos=1;
			query_user_page_struc->user_info=p;
			query_user_page_struc->user_info_head=p;
			query_user_page_struc->user_total=0;
			while(p != RT_NULL)
			{
				query_user_page_struc->user_total++;
				p=p->next;
			}
		}
	}
	return 0;
}
	
//清除	
void Query_User_Page_Clear(void *param)
{
	struct User_Info_Structure *p;
	if(query_user_page_struc != RT_NULL)
	{
		if(query_user_page_struc->user_info_head != RT_NULL)
		{
			while(query_user_page_struc->user_info_head != RT_NULL)
			{
				p=query_user_page_struc->user_info_head;
				query_user_page_struc->user_info_head = query_user_page_struc->user_info_head->next;
				rt_free(p);
			}
		}
		
		rt_free(query_user_page_struc);
		query_user_page_struc = RT_NULL;
	}
}

void Query_User_Page_Load(void *param)
{
	query_user_page_struc->display_flag=1;
}

//显示
void Query_User_Page_Display(void *param)
{
	if(query_user_page_struc->display_flag == 1)
	{
		query_user_page_struc->display_flag=0;
		OLED_GRAM_ClearScreen();
		OLED_GRAM_WriteStr(0,0,"查看用户:");
		if(query_user_page_struc->user_info != RT_NULL)
		{
			sprintf(query_user_page_struc->display_buff,"总数:%d当前:%d\n%s\n%s",
			query_user_page_struc->user_total,query_user_page_struc->user_pos,query_user_page_struc->user_info->name,query_user_page_struc->user_info->number);
		}else
		{
			sprintf(query_user_page_struc->display_buff,"没有用户");
		}
		OLED_GRAM_WriteStr(0,16,query_user_page_struc->display_buff);
		OLED_GRAM_Reflash();
	}
}
	
//响应输入
void Query_User_Page_Action(char value)
{
	if(value <= 9)
	{
		query_user_page_struc->display_flag=1;
	}else if(value == 10)
	{
		UI_Page_Delete();
	}else if(value == 11)
	{
		query_user_page_struc->display_flag=1;
	}else if(value == 12)
	{
		query_user_page_struc->display_flag=1;
	}else if(value == 13)
	{
		UI_Page_Clear();
	}else if(value == 14)
	{
		query_user_page_struc->display_flag=1;
		if(query_user_page_struc->user_info->prev != RT_NULL)
		{
			query_user_page_struc->user_info=query_user_page_struc->user_info->prev;
			query_user_page_struc->user_pos--;
		}
	}else if(value == 15)
	{
		query_user_page_struc->display_flag=1;
		if(query_user_page_struc->user_info->next != RT_NULL)
		{
			query_user_page_struc->user_info=query_user_page_struc->user_info->next;
			query_user_page_struc->user_pos++;
		}
	}
}

