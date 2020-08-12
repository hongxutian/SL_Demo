#include "sysinit.h"
#include "ff.h"
#include "string.h"


FIL file;

FATFS fs;													/* FatFs文件系统对象 */
/**
  * @brief  挂载文件系统
  * @param  无
  * @retval 0挂载文件系统成功，1格式化文件系统失败,2挂载文件系统失败
  */
static uint8_t filesysinit(void)
{
	FRESULT res_flash = f_mount(&fs,"1:",1);         /* 文件操作结果 */
/*----------------------- 格式化测试 -----------------*/  
	/* 如果没有文件系统就格式化创建创建文件系统 */
	if(res_flash == FR_NO_FILESYSTEM)
	{
    /* 格式化 */
		res_flash=f_mkfs("1:",0,0);							
		if(res_flash == FR_OK)
		{
			//格式化文件系统成功 
      /* 格式化后，先取消挂载 */
			res_flash = f_mount(NULL,"1:",1);			
      /* 重新挂载	*/			
			res_flash = f_mount(&fs,"1:",1);
			return 0;
		}
		else
		{
			return 1;
			//格式化文件系统失败
		}
	}
  else if(res_flash!=FR_OK)
  {
    //挂载文件系统失败
		return 2;
  }
  else
  {
    //挂载文件系统成功
		return 0;
  }
}

static void fileinit(void)
{
	FIL *fo;
	FRESULT res;
	UINT resnum;
	char buff[20];
	
	fo = (FIL *) rt_malloc(sizeof(FIL));
	
	//初始化管理员密码文件
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
	
	//初始化普通密码文件
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
	
	//初始化用户信息文件
	res=f_stat("1:user_info.txt",RT_NULL);
	if(res != FR_OK)
	{
		res = f_open(fo,"1:user_info.txt",FA_OPEN_ALWAYS|FA_WRITE);
		if(res == FR_OK)
		{
			f_printf(fo,"张三 100\n");
			f_printf(fo,"李四 101\n");
			f_close(fo);
		}
	}
	rt_free(fo);
	
}

//解析用户信息
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

//根据用户号码删除用户
char Delete_User(char *number)
{
	FIL *fo;
	char buff[100];
	UINT resnum;
	FRESULT res;
	char *p;
	struct User_Info_Structure *t=RT_NULL;
	char back=0;
	DWORD  fpre,fnow;//文件的位置
	
	int len;
	
	fo = (FIL *)rt_malloc(sizeof(FIL));
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:user_info.txt",FA_READ|FA_WRITE);
	if(res != FR_OK)
	{
		rt_free(fo);
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
	rt_free(fo);
	return back;
}

//添加用户，格式为"zhangsan 123",返回0成功，1失败
char Add_User(char *user)
{
	FIL *fo;
	FRESULT res;
	
	fo = (FIL *)rt_malloc(sizeof(FIL));
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:user_info.txt",FA_WRITE);
	if(res != FR_OK)
	{
		rt_free(fo);
		return 1;
	}
	
	f_lseek(fo,f_size(fo));
	f_printf(fo,"%s\n",user);
	f_close(fo);
	rt_free(fo);
	return 0;
}

//获取用户的信息
struct User_Info_Structure * Get_User_Info(char *number)
{
	FIL *fo;
	char buff[100];
	FRESULT res;
	char *p;
	struct User_Info_Structure *t=RT_NULL;
	
	fo = (FIL *)rt_malloc(sizeof(FIL));
	if(fo == RT_NULL)
	{
		return RT_NULL;
	}
	
	res = f_open(fo,"1:user_info.txt",FA_READ);
	if(res != FR_OK)
	{
		rt_free(fo);
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
	rt_free(fo);
	return t;
}

//获取所有用户的信息
struct User_Info_Structure * Get_All_User_Info(void)
{
	FIL *fo;
	char buff[100];
	FRESULT res;
	char *p;
	struct User_Info_Structure *back=RT_NULL,*t,*s=RT_NULL;
	
	fo = (FIL *)rt_malloc(sizeof(FIL));
	if(fo == RT_NULL)
	{
		return RT_NULL;
	}
	
	res = f_open(fo,"1:user_info.txt",FA_READ);
	if(res != FR_OK)
	{
		rt_free(fo);
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
	rt_free(fo);
	return back;
}

//校对密码,0正确，1 系统错误 2验证错误
char Check_Manager_Password(char *password)
{
	FIL *fo;
	char buff[30];
	FRESULT res;
	char *p;
	char back;
//	fo = (FIL *)rt_malloc(sizeof(FIL));
//	if(fo == RT_NULL)
//	{
//		return 1;
//	}
	fo = &file;
	res = f_open(fo,"1:manager_password.txt",FA_READ);
	if(res != FR_OK)
	{
//		rt_free(fo);
		return 1;
	}
	p=f_gets(buff,30,fo);
	if(p != 0)
	{
		buff[strlen(p)-1]='\0';//去掉回车
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
//	rt_free(fo);
	return back;
}

//修改管理员密码，0成功，1系统错误，失败
char Modify_Manager_Password(char *password)
{
	FIL *fo;
	FRESULT res;
	char back;
	
	fo = (FIL *)rt_malloc(sizeof(FIL));
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:manager_password.txt",FA_READ|FA_WRITE);
	if(res != FR_OK)
	{
		rt_free(fo);
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
	rt_free(fo);
	return back;
}

//验证密码，0正确，1系统错误，2验证错误
char Check_General_Password(char *password)
{
	FIL *fo;
	char buff[30];
	FRESULT res;
	char *p;
	char back;
	
	fo = (FIL *)rt_malloc(sizeof(FIL));
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:general_password.txt",FA_READ);
	if(res != FR_OK)
	{
		rt_free(fo);
		return 1;
	}
	while(1)
	{
		p=f_gets(buff,30,fo);
		if(p != 0)
		{
			p[strlen(p)-1]='\0';//去掉回车
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
	rt_free(fo);
	return back;
}

//删除密码，0成功，1系统错误，2密码不存在
char Delete_General_Password(char *password)
{
	FIL *fo;
	char buff[30];
	FRESULT res;
	char *p;
	char back;
	DWORD  fpre,fnow,fp;//文件的位置
	
	fo = (FIL *)rt_malloc(sizeof(FIL));
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:general_password.txt",FA_READ|FA_WRITE);
	if(res != FR_OK)
	{
		rt_free(fo);
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
			p[strlen(p)-1]='\0';//去掉回车
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
	rt_free(fo);
	return back;
}

//添加一个密码，0成功，1系统错误，2密码存在
char Add_General_Password(char *password)
{
	FIL *fo;
	FRESULT res;
	char t;
	
	t = Check_General_Password(password);
	
	if(t == 0)
	{
		return 2;
	}
	
	if(t == 1)
	{
		return 1;
	}
	
	fo = (FIL *)rt_malloc(sizeof(FIL));
	if(fo == RT_NULL)
	{
		return 1;
	}
	
	res = f_open(fo,"1:general_password.txt",FA_WRITE);
	if(res != FR_OK)
	{
		rt_free(fo);
		return 1;
	}
	
	f_lseek(fo,f_size(fo));
	f_printf(fo,"%s\n",password);
	f_close(fo);
	rt_free(fo);
	return 0;
}

//查看所有的排普通密码
struct General_Password_Structure * Get_General_Password(void)
{
	FIL *fo;
	char buff[30];
	FRESULT res;
	char *p;
	struct General_Password_Structure *back=RT_NULL,*t,*s;
	
	fo = (FIL *)rt_malloc(sizeof(FIL));
	if(fo == RT_NULL)
	{
		return RT_NULL;
	}
	
	res = f_open(fo,"1:general_password.txt",FA_READ);
	if(res != FR_OK)
	{
		rt_free(fo);
		return RT_NULL;
	}
	while(1)
	{
		p=f_gets(buff,30,fo);
		if(p != 0)
		{
			p[strlen(p)-1]='\0';//去掉回车
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
	rt_free(fo);
	return back;
}

void systeminit(void)
{
	FIL *fo;
	char buff[100];
//	UINT resnum;
	FRESULT res;
//	
//	uint16_t i;
	uint8_t filsys_flag=0;
	char *p;
//	
//	struct User_Info_Structure *t;
	struct General_Password_Structure *s;
	
	OLED_GRAM_PrintLogo();
	OLED_GRAM_Reflash();
	rt_thread_delay(1000);
	
	//测试文件系统
	filsys_flag = filesysinit();
	if(filsys_flag == 0)
	{
		fileinit();
	}
////	Delete_General_Password("112233");
////	Add_General_Password("112233");
////	Add_General_Password("223344");
////	Delete_User("202");
////	Add_User("王1 200\n");
////	Add_User("王2 201\n");
////	Add_User("王3 202\n");
//	
	fo = (FIL *)rt_malloc(sizeof(FIL));
	res = f_open(fo,"1:manager_password.txt",FA_READ|FA_WRITE);
	while(1)
	{
		p=f_gets(buff,100,fo);
		if(p != 0)
		{
			rt_kprintf("manager password info:%s",p);
		}else
		{
			f_close(fo);
			break;
		}
	}
	rt_free(fo);
	
	s=Get_General_Password();
	while(s != RT_NULL)
	{
		rt_kprintf("\ngeneral password info: password=%s",s->password);
		s=s->next;
	}
//	
//	
//	t=Get_All_User_Info();
//	while(t != RT_NULL)
//	{
//		rt_kprintf("\nuser info: number=%s name=%s",t->number,t->name);
//		t=t->next;
//	}
//	
	rt_kprintf("\nmanager password check:%d",Check_Manager_Password("123456"));
	rt_kprintf("\ngeneral password check:%d",Check_General_Password("223344"));
////	rt_kprintf("\nmanager password modify:%d",modify_manager_password("123456"));
////	rt_kprintf("\nmanager password check:%d",check_manager_password("000000"));
//	
//	
//	
	
}



