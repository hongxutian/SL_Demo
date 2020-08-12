#include "main_page.h"
#include "menu_page.h"
#include "board.h"
#include "ff.h"
#include "string.h"
#include "UI.h"
#include "sysinit.h"



struct Main_Page_Structure
{
	char work_state;//0 idle,1 unlock,2 identify, 3 unlock result, 4 identify err result
	char password[20];
	char password_len;
	char display_flag;
	char display_buff[65];
};

struct Main_Page_Structure *main_page_struc=RT_NULL;

//��ʼ��ҳ��
void Main_Page_Init(void *param)
{
	if(main_page_struc == RT_NULL)
	{
		main_page_struc = (struct Main_Page_Structure *)rt_malloc(sizeof(struct Main_Page_Structure));
		main_page_struc->work_state=0;
		main_page_struc->password_len=0;
		main_page_struc->password[0]='\0';
		main_page_struc->display_flag=1;
		strcpy(main_page_struc->display_buff,"������Ҫ��ָ֤�ƻ�����");
	}else
	{
		main_page_struc->work_state=0;
		main_page_struc->password_len=0;
		main_page_struc->password[0]='\0';
		main_page_struc->display_flag=1; 
		strcpy(main_page_struc->display_buff,"������Ҫ��ָ֤�ƻ�����");
	}
}

void Main_Page_Load(void *param)
{
	main_page_struc->work_state=0;
	main_page_struc->password_len=0;
	main_page_struc->password[0]='\0';
	main_page_struc->display_flag=1; 
	strcpy(main_page_struc->display_buff,"������Ҫ��ָ֤�ƻ�����");
}
	
//���	
void Main_Page_Clear(void *param)
{
	if(main_page_struc != RT_NULL)
	{
		rt_free(main_page_struc);
		main_page_struc = RT_NULL;
	}
}

//��ʾ
void Main_Page_Display(void *param)
{
	if(main_page_struc->display_flag == 1)
	{
		main_page_struc->display_flag=0;
		OLED_GRAM_ClearScreen();
		OLED_GRAM_WriteStr(0,0,main_page_struc->display_buff);
		OLED_GRAM_Reflash();
	}
}
	
//��Ӧ����
void Main_Page_Action(char value)
{
	char i;
	if(value <= 9)
	{
		if(main_page_struc->work_state==0)
		{
			main_page_struc->password[main_page_struc->password_len]=value+'0';
			main_page_struc->password_len++;
			main_page_struc->password[main_page_struc->password_len]='\0';
			main_page_struc->display_flag=1;
			strcpy(main_page_struc->display_buff,"����:\n *");
			main_page_struc->work_state=1;
		}else if(main_page_struc->work_state==1 || main_page_struc->work_state==2)
		{
			if(main_page_struc->password_len < PASSWORD_LEN_MAX)
			{
				main_page_struc->password[main_page_struc->password_len]=value+'0';
				main_page_struc->password_len++;
				main_page_struc->password[main_page_struc->password_len]='\0';
				main_page_struc->display_flag=1;
				strcat(main_page_struc->display_buff,"*");
			}else
			{
				main_page_struc->display_flag=1;
				if(main_page_struc->work_state==1)
				{
					main_page_struc->work_state=3;
				}else if(main_page_struc->work_state==2)
				{
					main_page_struc->work_state=4;
				}
				strcpy(main_page_struc->display_buff,"���볬����󳤶�");
			}
		}
	}else if(value == 10)
	{
		main_page_struc->password[0]='\0';
		main_page_struc->password_len=0;
		main_page_struc->work_state=0;
		main_page_struc->display_flag=1;
		strcpy(main_page_struc->display_buff,"������Ҫ��ָ֤�ƻ�����");
	}else if(value == 11)
	{
		if(main_page_struc->work_state==1)
		{
			i=Check_Manager_Password(main_page_struc->password,&UI_FILE);
			if(i!=0)
			{
				i=Check_General_Password(main_page_struc->password,&UI_FILE);
			}
			if(i != 0)
			{
				i=Check_Temporary_Password(main_page_struc->password,&UI_FILE);
			}
			
			if(i == 0)
			{
				strcpy(main_page_struc->display_buff,"������ȷ");
			}else
			{
				strcpy(main_page_struc->display_buff,"�������");
			}
			main_page_struc->password[0]='\0';
			main_page_struc->password_len=0;
			main_page_struc->work_state=3;
			main_page_struc->display_flag=1;
		}else if(main_page_struc->work_state==2)
		{
			if(main_page_struc->password_len>0)
			{
				i=Check_Manager_Password(main_page_struc->password,&UI_FILE);
				if(i == 0)
 				{
					UI_Page_Add(Menu_Page_Init,Menu_Page_Clear,Menu_Page_Display,Menu_Page_Load,Menu_Page_Action,RT_NULL);
					main_page_struc->password[0]='\0';
					main_page_struc->password_len=0;
					main_page_struc->work_state=4;
					strcpy(main_page_struc->display_buff,"��֤�ɹ�");
				}else
				{
					strcpy(main_page_struc->display_buff,"��֤ʧ��");
					main_page_struc->password[0]='\0';
					main_page_struc->password_len=0;
					main_page_struc->work_state=4;
				}
			}
			main_page_struc->display_flag=1;
			
		}else if(main_page_struc->work_state==3)
		{
			main_page_struc->password[0]='\0';
			main_page_struc->password_len=0;
			main_page_struc->work_state=0;
			main_page_struc->display_flag=1;
			strcpy(main_page_struc->display_buff,"������Ҫ��ָ֤�ƻ�����");
		}else if(main_page_struc->work_state==4)
		{
			main_page_struc->password[0]='\0';
			main_page_struc->password_len=0;
			main_page_struc->work_state=0;
			main_page_struc->display_flag=1;
			strcpy(main_page_struc->display_buff,"������Ҫ��ָ֤�ƻ�����");
		}
	}else if(value == 12)
	{		
		main_page_struc->display_flag=1;
		main_page_struc->work_state=2;
		strcpy(main_page_struc->display_buff,"��֤����:\n");
	}else if(value == 13)
	{
		main_page_struc->password[0]='\0';
		main_page_struc->password_len=0;
		main_page_struc->work_state=0;
		main_page_struc->display_flag=1;
		strcpy(main_page_struc->display_buff,"������Ҫ��ָ֤�ƻ�����");
	}else if(value == 14)
	{
		main_page_struc->display_flag=1;
		//rt_kprintf("\ncurrent time=%d",Get_RTC_Current_Time());
	}else if(value == 15)
	{
		main_page_struc->display_flag=1;
		//Set_RTC_Current_Time(100);
	}
}
