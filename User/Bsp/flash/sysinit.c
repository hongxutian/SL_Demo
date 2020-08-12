#include "sysinit.h"
#include "ff.h"
#include "string.h"
FIL T_FILE;
FATFS fs;													/* FatFs�ļ�ϵͳ���� */
/**
  * @brief  �����ļ�ϵͳ
  * @param  ��
  * @retval 0�����ļ�ϵͳ�ɹ���1��ʽ���ļ�ϵͳʧ��,2�����ļ�ϵͳʧ��
  */
static uint8_t filesysinit(void)
{
	FRESULT res_flash = f_mount(&fs,"1:",1);         /* �ļ�������� */
/*----------------------- ��ʽ������ -----------------*/  
	/* ���û���ļ�ϵͳ�͸�ʽ�����������ļ�ϵͳ */
	if(res_flash == FR_NO_FILESYSTEM)
	{
    /* ��ʽ�� */
		res_flash=f_mkfs("1:",0,0);							
		if(res_flash == FR_OK)
		{
			//��ʽ���ļ�ϵͳ�ɹ� 
      /* ��ʽ������ȡ������ */
			res_flash = f_mount(NULL,"1:",1);			
      /* ���¹���	*/			
			res_flash = f_mount(&fs,"1:",1);
			return 0;
		}
		else
		{
			return 1;
			//��ʽ���ļ�ϵͳʧ��
		}
	}
  else if(res_flash!=FR_OK)
  {
    //�����ļ�ϵͳʧ��
		return 2;
  }
  else
  {
    //�����ļ�ϵͳ�ɹ�
		return 0;
  }
}

static void fileinit(void)
{
	FIL *fo;
	FRESULT res;
	UINT resnum;
	
	fo = (FIL *) rt_malloc(sizeof(FIL));
	
	//��ʼ������Ա�����ļ�
	res=f_stat("1:manager_password.txt",RT_NULL);
	if(res != FR_OK)
	{
		res = f_open(fo,"1:manager_password.txt",FA_OPEN_ALWAYS|FA_WRITE);
		if(res == FR_OK)
		{
			res = f_write(fo,"000000\n",7,&resnum);
			f_close(fo);
		}
	}
	
	//��ʼ����ͨ�����ļ�
	res=f_stat("1:general_password.txt",RT_NULL);
	if(res != FR_OK)
	{
		res = f_open(fo,"1:general_password.txt",FA_OPEN_ALWAYS|FA_WRITE);
		if(res == FR_OK)
		{
			res = f_write(fo,"111111\n",7,&resnum);
			res = f_write(fo,"222222\n",7,&resnum);
			f_close(fo);
		}
	}
	
	//��ʼ���û���Ϣ�ļ�
	res=f_stat("1:user_info.txt",RT_NULL);
	if(res != FR_OK)
	{
		res = f_open(fo,"1:user_info.txt",FA_OPEN_ALWAYS|FA_WRITE);
		if(res == FR_OK)
		{
			f_printf(fo,"���� 100\n");
			f_printf(fo,"���� 101\n");
			f_close(fo);
		}
	}
	
	//��ʼ����ʱ�����ļ�
	res=f_stat("1:temporary_password.txt",RT_NULL);
	if(res != FR_OK)
	{
		res = f_open(fo,"1:temporary_password.txt",FA_OPEN_ALWAYS|FA_WRITE);
		if(res == FR_OK)
		{
			f_close(fo);
		}
	}
	
	rt_free(fo);
	
}

//�����û���Ϣ
struct User_Info_Structure * Parse_User_Info(char *data)
{
	char *p;
	char i;
	struct User_Info_Structure *res;
	p = data;
	res =(struct User_Info_Structure *) rt_malloc(sizeof(struct User_Info_Structure));
	if(res == RT_NULL)
	{
		return RT_NULL;
	}
	i=0;
	while(*p != ' ')
	{
		res->name[i++]=*p;
		p++;
	}
	p++;
	res->name[i]='\0';
	i=0;
	while(*p != '\n')
	{
		res->number[i++]=*p;
		p++;
	}
	res->number[i]='\0';
	res->next=RT_NULL;
	res->prev=RT_NULL;
	return res;
}

//�����û�����ɾ���û�
char Delete_User(char *number,FIL *file)
{
	FIL *fo;
	char buff[100];
	FRESULT res;
	char *p;
	struct User_Info_Structure *t=RT_NULL;
	char back=0;
	DWORD  fpre,fnow;//�ļ���λ��
	
	
	fo = file;
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:user_info.txt",FA_READ|FA_WRITE);
	if(res != FR_OK)
	{
		return 1;
	}
	while(1)
	{
		fpre = f_tell(fo);
		p=f_gets(buff,100,fo);
		fnow = f_tell(fo);
		if(p != 0)
		{
			t = Parse_User_Info(p);
			if(t != RT_NULL)
			{
				if(strcmp(number,t->number)==0)
				{
					back = 0;
					rt_free(t);
					break;
				}else
				{
					rt_free(t);
				}
			}else
			{
				back = 1;
				break;
			}
		}else
		{
			back = 1;
			break;
		}
	}
	if(back == 0)
	{
		while(1)
		{
			f_lseek(fo,fnow);
			p=f_gets(buff,100,fo);
			if(p != 0)
			{
				fnow = f_tell(fo);
				f_lseek(fo,fpre);
				f_printf(fo,p);
				fpre = f_tell(fo);
			}else
			{
				f_lseek(fo,fpre);
				f_truncate(fo);
				break;
			}
		}
	}
	f_close(fo);
	return back;
}

//����û�����ʽΪ"zhangsan 123",����0�ɹ���1ʧ��
char Add_User(char *user,FIL *file)
{
	FIL *fo;
	FRESULT res;
	
	fo = file;
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:user_info.txt",FA_WRITE);
	if(res != FR_OK)
	{
		return 1;
	}
	
	f_lseek(fo,f_size(fo));
	f_printf(fo,"%s\n",user);
	f_close(fo);
	return 0;
}

//��ȡ�û�����Ϣ
struct User_Info_Structure * Get_User_Info(char *number,FIL *file)
{
	FIL *fo;
	char buff[100];
	FRESULT res;
	char *p;
	struct User_Info_Structure *t=RT_NULL;
	
	fo = file;
	if(fo == RT_NULL)
	{
		return RT_NULL;
	}
	
	res = f_open(fo,"1:user_info.txt",FA_READ);
	if(res != FR_OK)
	{
		return RT_NULL;
	}
	while(1)
	{
		p=f_gets(buff,100,fo);
		if(p != 0)
		{
			t = Parse_User_Info(p);
			if(t != RT_NULL)
			{
				if(strcmp(number,t->number)==0)
				{
					break;
				}else
				{
					rt_free(t);
					t=RT_NULL;
				}
			}else
			{
				break;
			}
		}else
		{
			break;
		}
	}
	
	f_close(fo);
	return t;
}

//��ȡ�����û�����Ϣ
struct User_Info_Structure * Get_All_User_Info(FIL *file)
{
	FIL *fo;
	char buff[100];
	FRESULT res;
	char *p;
	struct User_Info_Structure *back=RT_NULL,*t,*s=RT_NULL;
	
	fo = file;
	if(fo == RT_NULL)
	{
		return RT_NULL;
	}
	
	res = f_open(fo,"1:user_info.txt",FA_READ);
	if(res != FR_OK)
	{
		return RT_NULL;
	}
	while(1)
	{
		p=f_gets(buff,100,fo);
		if(p != 0)
		{
			t = Parse_User_Info(p);
			if(t != RT_NULL)
			{
				if(back == RT_NULL)
				{
					back = t;
					s = back;
				}else
				{
					s->next=t;
					t->prev=s;
					s=s->next;
				}
			}else
			{
				break;
			}
		}else
		{
			break;
		}
	}
	
	f_close(fo);
	return back;
}

//У������,0��ȷ��1 ϵͳ���� 2��֤����
char Check_Manager_Password(char *password,FIL *file)
{
	FIL *fo;
	char buff[30];
	FRESULT res;
	char *p;
	char back;
	fo = file;
	res = f_open(fo,"1:manager_password.txt",FA_READ);
	if(res != FR_OK)
	{
		return 1;
	}
	p=f_gets(buff,30,fo);
	if(p != 0)
	{
		buff[strlen(p)-1]='\0';//ȥ���س�
		if(strcmp(buff,password)==0)
		{
			back = 0;
		}else
		{
			back = 2;
		}
	}else
	{
		back = 2;
	}
	
	f_close(fo);
	return back;
}

//�޸Ĺ���Ա���룬0�ɹ���1ϵͳ����ʧ��
char Modify_Manager_Password(char *password,FIL *file)
{
	FIL *fo;
	FRESULT res;
	char back;
	
	fo = file;
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:manager_password.txt",FA_READ|FA_WRITE);
	if(res != FR_OK)
	{
		return 1;
	}
	res = f_truncate(fo);
	if(res != FR_OK)
	{
		back = 1;
	}else
	{
		f_printf(fo,"%s\n",password);
		back = 0;
	}
	
	f_close(fo);
	return back;
}

//��֤���룬0��ȷ��1ϵͳ����2��֤����
char Check_General_Password(char *password,FIL *file)
{
	FIL *fo;
	char buff[30];
	FRESULT res;
	char *p;
	char back;
	
	fo = file;
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:general_password.txt",FA_READ);
	if(res != FR_OK)
	{
		return 1;
	}
	while(1)
	{
		p=f_gets(buff,30,fo);
		if(p != 0)
		{
			p[strlen(p)-1]='\0';//ȥ���س�
			if(strcmp(buff,password)==0)
			{
				back = 0;
				break;
			}
		}else
		{
			back = 2;
			break;
		}
		
	}
	
	f_close(fo);
	return back;
}

//ɾ�����룬0�ɹ���1ϵͳ����2���벻����
char Delete_General_Password(char *password,FIL *file)
{
	FIL *fo;
	char buff[30];
	FRESULT res;
	char *p;
	char back;
	DWORD  fpre,fnow,fp;//�ļ���λ��
	
	fo = file;
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:general_password.txt",FA_READ|FA_WRITE);
	if(res != FR_OK)
	{
		return 1;
	}
	back = 2;
	while(1)
	{
		fpre = f_tell(fo);
		p=f_gets(buff,30,fo);
		fnow = f_tell(fo);
		if(p != 0)
		{
			p[strlen(p)-1]='\0';//ȥ���س�
			if(strcmp(buff,password)==0)
			{
				fp = fpre;
				while(1)
				{
					f_lseek(fo,fnow);
					p=f_gets(buff,30,fo);
					if(p != 0)
					{
						fnow = f_tell(fo);
						f_lseek(fo,fpre);
						f_printf(fo,p);
						fpre = f_tell(fo);
					}else
					{
						f_lseek(fo,fpre);
						f_truncate(fo);
						break;
					}
				}
				f_lseek(fo,fp);
				back = 0;
			}
		}else
		{
			break;
		}
		
	}
	
	f_close(fo);
	return back;
}

//���һ�����룬0�ɹ���1ϵͳ����2�������
char Add_General_Password(char *password,FIL *file)
{
	FIL *fo;
	FRESULT res;
	char t;
	
	fo = file;
	
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	t = Check_General_Password(password,fo);
	
	if(t == 0)
	{
		return 2;
	}
	
	if(t == 1)
	{
		return 1;
	}
	
	res = f_open(fo,"1:general_password.txt",FA_WRITE);
	if(res != FR_OK)
	{
		return 1;
	}
	
	f_lseek(fo,f_size(fo));
	f_printf(fo,"%s\n",password);
	f_close(fo);
	return 0;
}

//�鿴���е�����ͨ����
struct General_Password_Structure * Get_General_Password(FIL *file)
{
	FIL *fo;
	char buff[30];
	FRESULT res;
	char *p;
	struct General_Password_Structure *back=RT_NULL,*t,*s;
	
	fo = file;
	if(fo == RT_NULL)
	{
		return RT_NULL;
	}
	
	res = f_open(fo,"1:general_password.txt",FA_READ);
	if(res != FR_OK)
	{
		return RT_NULL;
	}
	while(1)
	{
		p=f_gets(buff,30,fo);
		if(p != 0)
		{
			p[strlen(p)-1]='\0';//ȥ���س�
			if(back == RT_NULL)
			{
				back = (struct General_Password_Structure *)rt_malloc(sizeof(struct General_Password_Structure));
				strcpy(back->password,p);
				back->next=RT_NULL;
				back->prev=RT_NULL;
				s = back;
			}else
			{
				t = (struct General_Password_Structure *)rt_malloc(sizeof(struct General_Password_Structure));
				strcpy(t->password,p);
				t->next=RT_NULL;
				s->next=t;
				t->prev=s;
				s=s->next;
			}
		}else
		{
			break;
		}
	}
	
	f_close(fo);
	return back;
}


struct Temporary_Password_Structure * Parse_Temporary_Password(char *password)
{
	struct Temporary_Password_Structure *res;
	char *p;
	uint8_t i;
	
	res = (struct Temporary_Password_Structure *) rt_malloc(sizeof(struct Temporary_Password_Structure));
	p = password;
	i=0;
	
	if(res == RT_NULL)
	{
		return RT_NULL;
	}
	
	res->password[0]='\0';
	res->next=RT_NULL;
	res->prev=RT_NULL;
	res->effective_time=0;
	res->write_time=0;
	
	//ȡ������
	while(*p != ';')
	{
		res->password[i++]=*p;
		p++;
	}
	p++;
	res->password[i]='\0';
	
	//ȡ������
	while(*p != ';')
	{
		res->type=*p-'0';
		p++;
	}
	p++;
	
	//ȡ����Чʱ��
	while(*p != ';')
	{
		res->effective_time = res->effective_time*10 + (*p - '0');
		p++;
	}
	p++;
	
	//ȡ��д��ʱ��
	while(*p != '\n' && *p != '\0')
	{
		res->write_time = res->write_time*10 + (*p - '0');
		p++;
	}
	return res;
}

char Check_Temporary_Password(char *password,FIL *file)
{
	FIL *fo;
	char buff[50];
	FRESULT res;
	char *p;
	char back;
	struct Temporary_Password_Structure *t;
	
	fo = file;
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:temporary_password.txt",FA_READ);
	if(res != FR_OK)
	{
		return 1;
	}
	
	while(1)
	{
		p=f_gets(buff,50,fo);
		if(p != 0)
		{
			t = Parse_Temporary_Password(p);
			if(t != RT_NULL)
			{
				if(strcmp(t->password,password)==0)
				{
					back = 0;
					rt_free(t);
					break;
				}else
				{
					rt_free(t);
				}
			}else
			{
				back = 1;
				break;
			}
		}else
		{
			back = 2;
			break;
		}
		
	}
	
	f_close(fo);
	return back;
}

char Add_Temporary_Password(char *password,uint8_t type,uint32_t effective_time,uint32_t write_time,FIL *file)
{
	FIL *fo;
	FRESULT res;
	
	fo = file;
	
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:temporary_password.txt",FA_WRITE);
	if(res != FR_OK)
	{
		return 1;
	}
	
	f_lseek(fo,f_size(fo));
	f_printf(fo,"%s;%d;%d;%d\n",password,type,effective_time,write_time);
	f_close(fo);
	return 0;
}

void systeminit(void)
{
//	FIL fo;
//	char buff[100];
//	UINT resnum;
//	FRESULT res;
//	
//	uint16_t i;
	uint8_t filsys_flag=0;
//	char *p;
//	
//	struct User_Info_Structure *t;
//	struct General_Password_Structure *s;
	
	OLED_GRAM_PrintLogo();
	OLED_GRAM_Reflash();
	rt_thread_delay(1000);
	
	//�����ļ�ϵͳ
	filsys_flag = filesysinit();
	if(filsys_flag == 0)
	{
		fileinit();
	}
////	Delete_General_Password("112233");
////	Add_General_Password("112233");
////	Add_General_Password("223344");
////	Delete_User("202");
////	Add_User("��1 200\n");
////	Add_User("��2 201\n");
////	Add_User("��3 202\n");
//	
//	res = f_open(&fo,"1:manager_password.txt",FA_READ|FA_WRITE);
//	while(1)
//	{
//		p=f_gets(buff,100,&fo);
//		if(p != 0)
//		{
//			rt_kprintf("manager password info:%s",p);
//		}else
//		{
//			f_close(&fo);
//			break;
//		}
//	}
//	
//	s=Get_General_Password(&fo);
//	while(s != RT_NULL)
//	{
//		rt_kprintf("\ngeneral password info: password=%s",s->password);
//		s=s->next;
//	}
////	
////	
////	t=Get_All_User_Info();
////	while(t != RT_NULL)
////	{
////		rt_kprintf("\nuser info: number=%s name=%s",t->number,t->name);
////		t=t->next;
////	}
////	
//	rt_kprintf("\nmanager password check:%d",Check_Manager_Password("123456",&fo));
//	rt_kprintf("\ngeneral password check:%d",Check_General_Password("223344",&fo));
//////	rt_kprintf("\nmanager password modify:%d",modify_manager_password("123456"));
//////	rt_kprintf("\nmanager password check:%d",check_manager_password("000000"));
////	
////	
////	
	
}



