#include "modify_manager_password_page.h"
#include "board.h"
#include "string.h"
#include "UI.h"
#include "sysinit.h"



struct Modify_Manager_Password_Page_Structure
{
	char display_flag;
	char work_state;
	char password0[20];
	char password0_len;
	char password1[20];
	char password1_len;
	char display_buff[50];
};

struct Modify_Manager_Password_Page_Structure *modify_page_struc=RT_NULL;

//��ʼ��ҳ��
void Modify_Manager_Password_Page_Init(void *param)
{
	if(modify_page_struc == RT_NULL)
	{
		modify_page_struc = (struct Modify_Manager_Password_Page_Structure *)rt_malloc(sizeof(struct Modify_Manager_Password_Page_Structure));
		modify_page_struc->display_flag=1;
		modify_page_struc->work_state=0;
		modify_page_struc->password0[0]='\0';
		modify_page_struc->password1[0]='\0';
		modify_page_struc->password0_len=0;
		modify_page_struc->password1_len=0;
		strcpy(modify_page_struc->display_buff,"������:\n");
	}else
	{
		modify_page_struc->display_flag=1;
		modify_page_struc->work_state=0;
		modify_page_struc->password0[0]='\0';
		modify_page_struc->password1[0]='\0';
		modify_page_struc->password0_len=0;
		modify_page_struc->password1_len=0;
		strcpy(modify_page_struc->display_buff,"������:\n");
	}
}
	
//���	
void Modify_Manager_Password_Page_Clear(void *param)
{
	if(modify_page_struc != RT_NULL)
	{
		rt_free(modify_page_struc);
		modify_page_struc = RT_NULL;
	}
}

void Modify_Manager_Password_Page_Load(void *param)
{
	modify_page_struc->display_flag=1;
}

//��ʾ
void Modify_Manager_Password_Page_Display(void *param)
{
	if(modify_page_struc->display_flag == 1)
	{
		modify_page_struc->display_flag=0;
		OLED_GRAM_ClearScreen();
		OLED_GRAM_WriteStr(0,0,"�޸Ĺ���Ա����:");
		OLED_GRAM_WriteStr(0,16,modify_page_struc->display_buff);
		OLED_GRAM_Reflash();
	}
}
	
//��Ӧ����
void Modify_Manager_Password_Page_Action(char value)
{
	if(value <= 9)
	{
		if(modify_page_struc->work_state==0)
		{
			modify_page_struc->password0[modify_page_struc->password0_len]=value+'0';
			modify_page_struc->password0_len++;
			modify_page_struc->password0[modify_page_struc->password0_len]='\0';
			strcat(modify_page_struc->display_buff,"*");
			modify_page_struc->work_state=1;
		}else if(modify_page_struc->work_state==1)
		{
			if(modify_page_struc->password0_len <= 10)
			{
				modify_page_struc->password0[modify_page_struc->password0_len]=value+'0';
				modify_page_struc->password0_len++;
				modify_page_struc->password0[modify_page_struc->password0_len]='\0';
				strcat(modify_page_struc->display_buff,"*");
			}else
			{
				modify_page_struc->password0[0]='\0';
				modify_page_struc->password1[0]='\0';
				modify_page_struc->password0_len=0;
				modify_page_struc->password1_len=0;
				modify_page_struc->work_state=9;
				strcpy(modify_page_struc->display_buff,"���볤�Ȳ��ܳ���10λ");
			}
		}else if(modify_page_struc->work_state==2)
		{
			if(modify_page_struc->password1_len <= 10)
			{
				modify_page_struc->password1[modify_page_struc->password1_len]=value+'0';
				modify_page_struc->password1_len++;
				modify_page_struc->password1[modify_page_struc->password1_len]='\0';
				strcat(modify_page_struc->display_buff,"*");
			}else
			{
				modify_page_struc->password0[0]='\0';
				modify_page_struc->password1[0]='\0';
				modify_page_struc->password0_len=0;
				modify_page_struc->password1_len=0;
				modify_page_struc->work_state=9;
				strcpy(modify_page_struc->display_buff,"���볤�Ȳ��ܳ���10λ");
			}
		}
		modify_page_struc->display_flag=1;
	}else if(value == 10)
	{
		UI_Page_Delete();
	}else if(value == 11)
	{
		if(modify_page_struc->work_state==1)
		{
			if(modify_page_struc->password0_len>0)
			{
				modify_page_struc->work_state=2;
				strcpy(modify_page_struc->display_buff,"��֤������:\n");
			}
		}else if(modify_page_struc->work_state==2)
		{
			if(modify_page_struc->password0_len>0)
			{
				if(strcmp(modify_page_struc->password0,modify_page_struc->password1) == 0)
				{
					if(Modify_Manager_Password(modify_page_struc->password0,&UI_FILE)==0)
					{
						strcpy(modify_page_struc->display_buff,"�޸ĳɹ�");
						modify_page_struc->work_state=3;
					}else
					{
						strcpy(modify_page_struc->display_buff,"�޸�ʧ��");
						modify_page_struc->work_state=9;
					}
				}else
				{
					strcpy(modify_page_struc->display_buff,"ǰ�����벻һ��");
					modify_page_struc->work_state=9;
				}
			}
		}else if(modify_page_struc->work_state==3)
		{
			UI_Page_Delete();
		}else if(modify_page_struc->work_state==9)
		{
			modify_page_struc->work_state=0;
			strcpy(modify_page_struc->display_buff,"������:\n");
			modify_page_struc->password0[0]='\0';
			modify_page_struc->password1[0]='\0';
			modify_page_struc->password0_len=0;
			modify_page_struc->password1_len=0;
		}
		modify_page_struc->display_flag=1;
	}else if(value == 12)
	{
		modify_page_struc->display_flag=1;
	}else if(value == 13)
	{
		UI_Page_Clear();
	}else if(value == 14)
	{
		modify_page_struc->display_flag=1;
	}else if(value == 15)
	{
		modify_page_struc->display_flag=1;
	}
}

