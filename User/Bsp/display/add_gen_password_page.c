#include "add_gen_password_page.h"
#include "board.h"
#include "string.h"
#include "UI.h"
#include "sysinit.h"



struct Add_Gen_Password_Page_Structure
{
	char display_flag;
	char work_state;
	char password0[20];
	char password0_len;
	char password1[20];
	char password1_len;
	char display_buff[50];
};

struct Add_Gen_Password_Page_Structure *addp_page_struc=RT_NULL;

//��ʼ��ҳ��
char Add_Gen_Password_Page_Init(void *param)
{
	if(addp_page_struc == RT_NULL)
	{
		addp_page_struc = (struct Add_Gen_Password_Page_Structure *)rt_malloc(sizeof(struct Add_Gen_Password_Page_Structure));
		addp_page_struc->display_flag=1;
		addp_page_struc->work_state=0;
		addp_page_struc->password0[0]='\0';
		addp_page_struc->password1[0]='\0';
		addp_page_struc->password0_len=0;
		addp_page_struc->password1_len=0;
		strcpy(addp_page_struc->display_buff,"������:\n");
	}else
	{
		addp_page_struc->display_flag=1;
		addp_page_struc->work_state=0;
		addp_page_struc->password0[0]='\0';
		addp_page_struc->password1[0]='\0';
		addp_page_struc->password0_len=0;
		addp_page_struc->password1_len=0;
		strcpy(addp_page_struc->display_buff,"������:\n");
	}
	return 0;
}
	
//���	
void Add_Gen_Password_Page_Clear(void *param)
{
	if(addp_page_struc != RT_NULL)
	{
		rt_free(addp_page_struc);
		addp_page_struc = RT_NULL;
	}
}

void Add_Gen_Password_Page_Load(void *param)
{
	addp_page_struc->display_flag=1;
}

//��ʾ
void Add_Gen_Password_Page_Display(void *param)
{
	if(addp_page_struc->display_flag == 1)
	{
		addp_page_struc->display_flag=0;
		OLED_GRAM_ClearScreen();
		OLED_GRAM_WriteStr(0,0,"�����ͨ����:");
		OLED_GRAM_WriteStr(0,16,addp_page_struc->display_buff);
		OLED_GRAM_Reflash();
	}
}
	
//��Ӧ����
void Add_Gen_Password_Page_Action(char value)
{
	if(value <= 9)
	{
		if(addp_page_struc->work_state==0)
		{
			addp_page_struc->password0[addp_page_struc->password0_len]=value+'0';
			addp_page_struc->password0_len++;
			addp_page_struc->password0[addp_page_struc->password0_len]='\0';
			strcat(addp_page_struc->display_buff,"*");
			addp_page_struc->work_state=1;
		}else if(addp_page_struc->work_state==1)
		{
			if(addp_page_struc->password0_len <= 10)
			{
				addp_page_struc->password0[addp_page_struc->password0_len]=value+'0';
				addp_page_struc->password0_len++;
				addp_page_struc->password0[addp_page_struc->password0_len]='\0';
				strcat(addp_page_struc->display_buff,"*");
			}else
			{
				addp_page_struc->password0[0]='\0';
				addp_page_struc->password1[0]='\0';
				addp_page_struc->password0_len=0;
				addp_page_struc->password1_len=0;
				addp_page_struc->work_state=9;
				strcpy(addp_page_struc->display_buff,"���볤�Ȳ��ܳ���10λ");
			}
		}else if(addp_page_struc->work_state==2)
		{
			if(addp_page_struc->password1_len <= 10)
			{
				addp_page_struc->password1[addp_page_struc->password1_len]=value+'0';
				addp_page_struc->password1_len++;
				addp_page_struc->password1[addp_page_struc->password1_len]='\0';
				strcat(addp_page_struc->display_buff,"*");
			}else
			{
				addp_page_struc->password0[0]='\0';
				addp_page_struc->password1[0]='\0';
				addp_page_struc->password0_len=0;
				addp_page_struc->password1_len=0;
				addp_page_struc->work_state=9;
				strcpy(addp_page_struc->display_buff,"���볤�Ȳ��ܳ���10λ");
			}
		}
		addp_page_struc->display_flag=1;
	}else if(value == 10)
	{
		UI_Page_Delete();
	}else if(value == 11)
	{
		if(addp_page_struc->work_state==1)
		{
			if(addp_page_struc->password0_len>0)
			{
				addp_page_struc->work_state=2;
				strcpy(addp_page_struc->display_buff,"��֤������:\n");
			}
		}else if(addp_page_struc->work_state==2)
		{
			if(addp_page_struc->password0_len>0)
			{
				if(strcmp(addp_page_struc->password0,addp_page_struc->password1) == 0)
				{
					if(Add_General_Password(addp_page_struc->password0,&UI_FILE)==0)
					{
						strcpy(addp_page_struc->display_buff,"��ӳɹ�");
						addp_page_struc->work_state=3;
					}else
					{
						strcpy(addp_page_struc->display_buff,"���ʧ��");
						addp_page_struc->work_state=9;
					}
				}else
				{
					strcpy(addp_page_struc->display_buff,"ǰ�����벻һ��");
					addp_page_struc->work_state=9;
				}
			}
		}else if(addp_page_struc->work_state==3)
		{
			UI_Page_Delete();
		}else if(addp_page_struc->work_state==9)
		{
			addp_page_struc->work_state=0;
			strcpy(addp_page_struc->display_buff,"������:\n");
			addp_page_struc->password0[0]='\0';
			addp_page_struc->password1[0]='\0';
			addp_page_struc->password0_len=0;
			addp_page_struc->password1_len=0;
		}
		addp_page_struc->display_flag=1;
	}else if(value == 12)
	{
		addp_page_struc->display_flag=1;
	}else if(value == 13)
	{
		UI_Page_Clear();
	}else if(value == 14)
	{
		addp_page_struc->display_flag=1;
	}else if(value == 15)
	{
		addp_page_struc->display_flag=1;
	}
}

