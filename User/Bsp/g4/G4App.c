#include "G4.h"
#include "G4App.h"
#include "board.h"
#include "string.h"
#include "cJSON.h" 
#include "base64.h"
#include "myaes.h"
#include "CRC.h"
#include "UI.h"
#include "msg_page.h"
#include "sysinit.h"
#include "add_user_page.h"

uint8_t cmdflag = 0;
struct G4_CMD_LINK
{
	G4_UART_BUFF *cmdres;
	struct G4_CMD_LINK *next;
	struct G4_CMD_LINK *prev;
};

struct G4_CMD_LINK cmdbuff={RT_NULL,RT_NULL,RT_NULL};

uint8_t CONNECT_SERVER = 0;//连接服务器的标志1表示成功连接

//认证信息，这个认证信息只能用于dev00001
uint8_t token[]={
	0x02,0x00,0x42,0x7b,0x22,0x64,0x65,0x76,0x69,0x63,0x65,0x4e,0x75,0x6d,0x62,
	0x65,0x72,0x22,0x3a,0x22,0x64,0x65,0x76,0x30,0x30,0x30,0x30,0x31,0x22,0x2c,
	0x22,0x73,0x69,0x67,0x6e,0x61,0x74,0x75,0x72,0x65,0x22,0x3a,0x22,0x6f,0x4a,
	0x72,0x32,0x38,0x31,0x53,0x39,0x51,0x77,0x36,0x48,0x78,0x6f,0x62,0x74,0x38,
	0x73,0x34,0x34,0x74,0x77,0x3d,0x3d,0x22,0x7d,0x76,0x06
};

uint8_t auth_key[16]={0xc6,0xa5,0x7c,0x8c,0xa0,0xc6,0x4e,0x5d,0xd6,0x0c,0xb2,0x3e,0x4f,0x62,0x62,0xe0};//认证密钥
uint8_t comm_key[16];//通信密钥

/**
	*@brief
	*@parameter
	****cmd:命令
	****reply1:可能的结果1
	****reply2:可能的结果2
	****waittime:等待结果返回的时间
	****prewaittime:发送命令前需要延迟的时间
	*@return 0 success,1 busy,2 out of time,3 fail
	*/
uint8_t G4_Cmd ( char * cmd, char * reply1, char * reply2,uint32_t waittime, uint32_t prewaittime)
{    
	uint32_t delayTime=0;
	uint16_t i;
	uint8_t sure = 0;
	G4_UART_BUFF *cmdp;
	struct G4_CMD_LINK *linp,*linp1;;
	if(cmdflag == 1)
	{
		i=10;
		do
		{
			rt_thread_delay(100);
			i--;
		}while(cmdflag == 1 && i > 0);
		if(cmdflag == 1)
		{
			return 1;
		}
	}
	cmdflag = 1;
	if(prewaittime > 0)
	{
		rt_thread_delay(prewaittime);		
	}
	G4_Usart_SendString (cmd);
	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                    
	{
		sure = 0;
	}else
	{
		sure = 0;
		i = 0;//标志是否有返回
		while(delayTime<waittime)
		{
			do
			{
				rt_thread_delay(100);						 
				delayTime=delayTime+100;
			}while((delayTime<waittime)&&(cmdbuff.next==RT_NULL));
			linp = cmdbuff.next;
			cmdbuff.next = RT_NULL;
			while(linp != RT_NULL)
			{
				i = 1;//表示有返回
				cmdp = linp->cmdres;
				cmdp->buff[cmdp->num] = '\0';
				//rt_kprintf( "%s", cmdp->buff );
				if(reply1 != 0 )
				{
					
					if((sure & 0x01) == 0)
					{
						if(strstr( (char *)(cmdp->buff), reply1 )!=0)
						{
							sure = sure | 0x01;
						} 
					}
				}else
				{
					sure = sure | 0x01;
				}
			
				if(reply2 != 0 )
				{
					
					if((sure & 0x02) == 0)
					{
						if(strstr( (char *)(cmdp->buff), reply2 )!=0)
						{
							sure = sure | 0x02;
						}
					}
				}else
				{
					sure = sure | 0x02;
				}
				linp1 = linp;
				linp = linp->next;
				rt_free(linp1);
				
				if((sure & 0x03) == 3)
				{
					break;
				}
			}
			if((sure & 0x03) == 3)
			{
				break;
			}
		}
		if(i == 0)
		{
			sure = 2;
		}else
		{
			sure = ((sure & 0x03) == 3) ? 0 : 3;
		}
	}
	cmdflag = 0;
	cmdbuff.next = RT_NULL;
	return sure;
	
}

uint8_t G4_Cmd_ResAndOr ( char * cmd, char * reply1, char * reply2,uint32_t waittime,uint8_t andor)
{    
	uint32_t delayTime=0;
	uint16_t i;
	uint8_t sure = 0;
	G4_UART_BUFF *cmdp;
	struct G4_CMD_LINK *linp,*linp1;;
	if(cmdflag == 1)
	{
		i=10;
		do
		{
			rt_thread_delay(100);
			i--;
		}while(cmdflag == 1 && i > 0);
		if(cmdflag == 1)
		{
			return 1;
		}
	}
	cmdflag = 1;
	G4_Usart_SendString (cmd);
	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                    
	{
		sure = 0;
	}else
	{
		sure = 0;
		i = 0;
		while(delayTime<waittime)
		{
			do
			{
				rt_thread_delay(100);						 
				delayTime=delayTime+100;
			}while((delayTime<waittime)&&(cmdbuff.next==RT_NULL));
			linp = cmdbuff.next;
			cmdbuff.next = RT_NULL;
			while(linp != RT_NULL)
			{
				i = 1;
				cmdp = linp->cmdres;
				cmdp->buff[cmdp->num] = '\0';
				//rt_kprintf( "%s", cmdp->buff );
				if(reply1 != 0 )
				{
					if((sure & 0x01) == 0)
					{
						if(strstr( (char *)(cmdp->buff), reply1 )!=0)
						{
							sure = sure | 0x01;
						} 
					}
				}else
				{
					sure = sure | 0x01;
				}
				if(reply2 != 0 )
				{
					
					if((sure & 0x02) == 0)
					{
						if(strstr( (char *)(cmdp->buff), reply2 )!=0)
						{
							sure = sure | 0x02;
						}
					}
				}else
				{
					sure = sure | 0x02;
				}
				linp1 = linp;
				linp = linp->next;
				rt_free(linp1);
				
				if(andor == 1) //结果与
				{
					if((sure & 0x03) == 3)
					{
						break;
					}
				}else if((sure & 0x03) > 0)
				{
					sure = 0x03;
					break; 
				}
			}
			if((sure & 0x03) == 3)
			{
				break;
			}
		}
		if(i == 0)
		{
			sure = 2;
		}else
		{
			sure = ((sure & 0x03) == 3) ? 0 : 3;
		}
	}
	cmdflag = 0;
	cmdbuff.next = RT_NULL;
	return sure;
}

uint8_t G4_Cmd_Repeat ( char * cmd, char * reply1, char * reply2, uint32_t waittime, uint32_t prewaittime,uint8_t repeattime)
{
	uint8_t i;
	uint8_t res = 3;
	for(i=0;i<repeattime;i++)
	{
		res = G4_Cmd( cmd, reply1, reply2, waittime, prewaittime);
		if(res == 0)
		{
			break;
		}
	}
	return res;
}

/**
	*@brief 进入AT命令模式
	*@parameter 无
	*@return 0 success,1 fail
	*/
uint8_t G4_EnterATMode(void)
{
	uint8_t i=0;
	
	while(i<5 && G4_Cmd_ResAndOr ( "+++", "OK", "+++",1000,0) != 0)
	{
		i++;
	}
	if(i >= 5)
	{
		return 1;
	}else
	{
		return 0;
	}
}

uint8_t G4_TestATCmd(void)
{
	return G4_Cmd ( "AT\r\n", "OK", 0, 1000, 1000);
}

uint8_t G4_Init(void)
{                                                    
	
	G4_EnterATMode();
	//检查模块是否能正常通信
	if(G4_Cmd_Repeat ( "AT\r\n", "OK", 0, 1000, 0,5) != 0)
	{
		return 1;
	}
	
		//关闭模块回显功能
	if(G4_Cmd_Repeat ( "ATE0\r\n", "OK", 0, 1000, 0,5) != 0)
	{
		return 2;
	}
	
		//检查是否插入手机卡
	if(G4_Cmd_Repeat ( "AT+CPIN?\r\n", "+CPIN: READY", 0, 1000, 0,5) != 0)
	{
		return 3;
	}
	
		//检查网络注册
	if(G4_Cmd_Repeat ( "AT+CEREG?\r\n", "+CEREG: 0,1", 0, 1000, 0,5) != 0)
	{
		return 4;
	}
	
			//检查网络附着
	if(G4_Cmd_Repeat ( "AT+CGATT?\r\n", "+CGATT: 1", 0, 1000, 0,5) != 0)
	{
		return 5;
	}
	
  return 0;
}
//AT+CIPSTART="TCP","47.97.165.179","10010"

uint8_t G4_Net_Config(void)
{                                                    
	char t[]="AT+CIPSTART=\"TCP\",\"47.97.165.179\",\"9920\"\r\n";
	uint8_t res;
	res = G4_Cmd_Repeat( "AT+CIPSTATUS\r\n", "CONNECT OK", 0, 500, 0,5);
	
	if( res == 0)
	{
		res = G4_Cmd_Repeat( "AT+CIPCLOSE=1\r\n", "CLOSE OK", 0, 500, 0,5);
		if(res != 0)
		{
			return 1;
		}
	}else if(res == 2)
	{
		return 2;
	}
	
	res = G4_Cmd_Repeat( "AT+CIPMODE?\r\n", "+CIPMODE: 1", 0, 500, 0,5);
	if(res == 2)
	{
		return 3;
	}else if(res == 3)
	{
		res = G4_Cmd_Repeat( "AT+CIPMODE=1\r\n", "OK", 0, 500, 0,5); 
		if(res != 0)
		{
			return 4;
		}
	}

	if(G4_Cmd_Repeat( t, "CONNECT", 0, 5000, 0,5) != 0)
	{
		return 6;
	}
	
  return 0;
}

uint8_t G4_Net_Connect(char *ip,char *port)
{
	return 0;
}

//组装发送的数据，匹配数据包的格式
void assembleWebMsg(char *msg,int16_t msglen,char *res,int16_t *reslen)
{
	int16_t i;
	uint16_t crc;
	char *p;
	p = res + 3;
	//加密数据
	myaes_encrypt(comm_key,(uint8_t *)msg,msglen,(uint8_t *)p,&i);
	//填充数据包头
	res[0] = 0x02;
	res[1] = 0xff&(i>>8);
	res[2] = 0xff&(i);
	i = i + 3;
	//计算crc值
	crc = crc16tablefast((uint8_t *)res,i);
	//填充crc
	res[i++] = 0xff&(crc>>8);
	res[i++] = 0xff&(crc);
	*reslen = i;
}

void G4_Thread_Entry(void *parameter)
{
	rt_err_t err;
	G4_UART_BUFF *G4_MSG;
	while(1)
	{
		err=rt_mb_recv(g4mb,(rt_uint32_t *)&G4_MSG,RT_WAITING_FOREVER);
		if(err != RT_EOK)
		{
			continue;
		}
//		rt_kprintf( "\ng4 thread get:\n%s",G4_MSG->buff);
//		rt_kprintf( "\nlen=%d",G4_MSG->num);
		if(cmdflag == 1)
		{
			struct G4_CMD_LINK *p = (struct G4_CMD_LINK *)rt_malloc(sizeof(struct G4_CMD_LINK));
			p->cmdres = G4_MSG;
			p->next = cmdbuff.next;
			cmdbuff.next = p;
		}else if(CONNECT_SERVER > 0)
		{
//			rt_kprintf( "\nlen=%d",G4_MSG->num);
			rt_mb_send(g4appmb,(rt_uint32_t)G4_MSG);
		}
	}
}
//发送数据和心跳包
void G4APP_Send_Thread_Entry(void *parameter)
{
	rt_err_t err;
	int16_t caclen;
	char cache[1024];
	char cache2[1024];
	uint8_t heart[3] = {0x01,0x80,0x7e};
	while(1)
	{
		err = rt_mq_recv(g4msgmq,cache,1024,60000);
		if(CONNECT_SERVER != 2)
		{
			continue;
		}
		if(err == RT_EOK)
		{
			//计算待发送的数据长度，因为发送的数据为JSON格式，是字符串，所以可以用strlen计算长度
			caclen = rt_strlen(cache);
			if(caclen > 0)
			{
				assembleWebMsg(cache,caclen,cache2,&caclen);//组装发送的数据
				G4_Usart_SendArray((uint8_t *)cache2,caclen);//发送数据
			}
		}else if(err == -RT_ETIMEOUT)
		{
			G4_Usart_SendArray(heart,3);
		}
	}
}
//数据接收和连接服务器
void G4APP_Rece_Thread_Entry(void *parameter)
{
	rt_err_t err;
	G4_UART_BUFF *G4_MSG;
	uint8_t i,j;
	uint8_t * recp;
	char *out;
	int16_t reclen;
	cJSON *json,*jitem1,*jitem2,*jitem3,*jsend;
	uint8_t cache[1024];
	int16_t caclen;
	uint8_t len;
	while(1)
	{
		//网查网络状态G4_Cmd ( "AT+RESET\r\n", "OK", 0,1000, 0);
		while(1)
		{
			for(i=0;i<10;i++)
			{
				rt_kprintf("\n检查网络状况\n");
				j = G4_Init();
				if(j != 0)
				{
					rt_thread_delay(10000);
				}else
				{
					break;
				}
			}
			if(i >= 10)
			{
				G4_Cmd ( "AT+RESET\r\n", "OK", 0,1000, 0);
				rt_thread_delay(10000);
			}else
			{
				break;
			}
		}
		//连接服务器
		for(i=0;i<10;i++)
		{
			rt_kprintf("\n连接服务器......\n");
			if(G4_Net_Config() == 0)
			{
				break;
			}else
			{
				rt_thread_delay(10000);
			}
		}
		if(i >= 10)
		{
			continue;
		}
		rt_kprintf("\n连接到服务器\n");
		CONNECT_SERVER = 1;
		//验证信息
		for(i=0;i<5;i++)
		{
			G4_Usart_SendArray(token,71);
			for(j=0;j<5;j++)
			{
				err=rt_mb_recv(g4appmb,(rt_uint32_t *)&G4_MSG,5000);
				if(err == RT_EOK)
				{
					reclen = G4_MSG->num - 5;
					recp = G4_MSG->buff + 3;
					recp[reclen] = '\0';
					//rt_kprintf("\nserver back:%s",recp);
					json = cJSON_Parse((char *)recp);
					if(json != RT_NULL)
					{
						jitem1 = cJSON_GetObjectItem(json,"res");
						if((rt_strstr(jitem1->valuestring,"success")))
						{
							jitem2 = cJSON_GetObjectItem(json,"commkey");
							Base64_DecodeToUChArr(jitem2->valuestring,rt_strlen(jitem2->valuestring),(uint8_t *)cache,&caclen);
							myaes_decrypt(auth_key,(uint8_t *)cache,caclen,cache,&caclen);
							for(reclen=0;reclen<caclen;reclen++)
							{
								comm_key[reclen] = cache[reclen];
							}
							CONNECT_SERVER = 2;
							cJSON_Delete(json);
							break;
						}
						cJSON_Delete(json);
					}
				}
			}
			if(CONNECT_SERVER == 2)
			{
				break;
			}
		}
		if(i >= 5)
		{
			continue;
		}
		rt_kprintf("\n服务器验证成功\n");
		while(1)
		{
			//接收数据
			err=rt_mb_recv(g4appmb,(rt_uint32_t *)&G4_MSG,RT_WAITING_FOREVER);
			if(err != RT_EOK)
			{
				continue;
			}
			//传输的数据加密且有数据头和尾，数据头尾总共5个字节，实际内容为16字节的整数倍，不符合的为4G模块返回的网络状态信息
			if((G4_MSG->num > 16 && ((G4_MSG->num - 5)%16 != 0)) || G4_MSG->num < 16)
			{
				rt_kprintf("\n与服务器连接断开\n");
				G4_Cmd ( "AT+RESET\r\n", "OK", 0,1000, 0);
				rt_thread_delay(10000);
				G4_MSG->buff[G4_MSG->num] = '\0';
				if(strstr((char *)G4_MSG->buff,"CLOSED") != 0)
				{
					CONNECT_SERVER = 0;
					break;
				}else
				{
					CONNECT_SERVER = 0;
					break;
				}
			}else
			{
				reclen = G4_MSG->num - 5;
				recp = G4_MSG->buff + 3;
				myaes_decrypt(comm_key,(uint8_t *)recp,reclen,cache,&caclen);
				cache[caclen] = '\0';
				rt_kprintf("\nreceive:\n%s\n",cache);
				json = cJSON_Parse((char *)cache);
				if(json!=RT_NULL)
				{
					jitem1 = cJSON_GetObjectItem(json,"type");
					if(rt_strcmp(jitem1->valuestring,"unlock")==0)
					{
						jsend=cJSON_CreateObject();
						cJSON_AddStringToObject(jsend,"type","unlock");
						cJSON_AddStringToObject(jsend,"result","success");
						out=cJSON_PrintUnformatted(jsend);
						len=rt_strlen(out);
						len++;
						rt_mq_send(g4msgmq,out,len);
						rt_free(out);
						cJSON_Delete(jsend);
						UI_Page_Add(Msg_Page_Init,Msg_Page_Clear,Msg_Page_Display,Msg_Page_Load,Msg_Page_Action,"解锁成功");						
					}else if(rt_strcmp(jitem1->valuestring,"setTemporaryCode")==0)
					{//temporaryCode
						jitem2 = cJSON_GetObjectItem(json,"temporaryCode");//取出临时密码
						jsend=cJSON_CreateObject();
						cJSON_AddStringToObject(jsend,"type","setTemporaryCode");
						if(Add_Temporary_Password(jitem2->valuestring,0,60*5,Get_RTC_Current_Time(),&T_FILE)==0)
						{
							cJSON_AddStringToObject(jsend,"result","success");
						}else
						{
							cJSON_AddStringToObject(jsend,"result","fail");
						}
						out=cJSON_PrintUnformatted(jsend);
						len=rt_strlen(out);
						len++;
						rt_mq_send(g4msgmq,out,len);
						rt_free(out);
						cJSON_Delete(jsend);	
					}else if(rt_strcmp(jitem1->valuestring,"deleteUser")==0)
					{
						jitem2 = cJSON_GetObjectItem(json,"number");//
						jsend=cJSON_CreateObject();
						cJSON_AddStringToObject(jsend,"type","deleteUser");
						if(Delete_User(jitem2->valuestring,&T_FILE)==0)
						{
							cJSON_AddStringToObject(jsend,"result","success");
						}else
						{
							cJSON_AddStringToObject(jsend,"result","fail");
						}
						out=cJSON_PrintUnformatted(jsend);
						len=rt_strlen(out);
						len++;
						rt_mq_send(g4msgmq,out,len);
						rt_free(out);
						cJSON_Delete(jsend);	
					}else if(rt_strcmp(jitem1->valuestring,"modifyPassword")==0)
					{
						jitem2 = cJSON_GetObjectItem(json,"password");//
						jsend=cJSON_CreateObject();
						cJSON_AddStringToObject(jsend,"type","modifyPassword");
						if(Modify_Manager_Password(jitem2->valuestring,&T_FILE)==0)
						{
							cJSON_AddStringToObject(jsend,"result","success");
						}else
						{
							cJSON_AddStringToObject(jsend,"result","fail");
						}
						out=cJSON_PrintUnformatted(jsend);
						len=rt_strlen(out);
						len++;
						rt_mq_send(g4msgmq,out,len);
						rt_free(out);
						cJSON_Delete(jsend);	
					}else if(rt_strcmp(jitem1->valuestring,"addUser")==0)
					{
						jitem2 = cJSON_GetObjectItem(json,"name");//
						if(UI_Page_Add(Add_User_Page_Init,Add_User_Page_Clear,Add_User_Page_Display,Add_User_Page_Load,Add_User_Page_Action,jitem2->valuestring) != 0)
						{
							jsend=cJSON_CreateObject();
							cJSON_AddStringToObject(jsend,"type","addUser");
							cJSON_AddStringToObject(jsend,"result","fail");
							out=cJSON_PrintUnformatted(jsend);
							len=rt_strlen(out);
							len++;
							rt_mq_send(g4msgmq,out,len);
							rt_free(out);
							cJSON_Delete(jsend);
						}							
					}else if(rt_strcmp(jitem1->valuestring,"modifyUserName")==0)
					{
						jitem2 = cJSON_GetObjectItem(json,"number");
						jitem3 = cJSON_GetObjectItem(json,"name");
						jsend=cJSON_CreateObject();
						cJSON_AddStringToObject(jsend,"type","modifyUserName");
						sprintf(cache,"%s %s",jitem3->valuestring,jitem2->valuestring);
						if(Delete_User(jitem2->valuestring,&T_FILE)==0)
						{
							if(Add_User(cache,&T_FILE) == 0)
							{
								cJSON_AddStringToObject(jsend,"result","success");
							}else
							{
								cJSON_AddStringToObject(jsend,"result","fail");
							}
						}else
						{
							cJSON_AddStringToObject(jsend,"result","fail");
						}
						out=cJSON_PrintUnformatted(jsend);
						len=rt_strlen(out);
						len++;
						rt_mq_send(g4msgmq,out,len);
						rt_free(out);
						cJSON_Delete(jsend);	
					}
					cJSON_Delete(json);
				}
			}
		}
	}
}

