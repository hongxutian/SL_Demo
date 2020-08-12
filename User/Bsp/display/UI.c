#include "UI.h"
#include "main_page.h"
#include "board.h"

FIL UI_FILE;

struct UI_Stack
{
	char (*init)(void *param);
	void (*clear)(void *param);
	void (*display)(void *param);
	void (*action)(char param);
	void (*load)(void *param);
	struct UI_Stack *next;
};

struct UI_Stack *ui_stack;

char UI_Page_Add(char (*func_init)(void *param),
	void (*func_clear)(void *param),
		void (*func_display)(void *param),
			void (*func_load)(void *param),
				void (*func_action)(char param),
					void *init_param)
{
	struct UI_Stack *p;
	
	if(func_init(init_param)!=0)
	{
		return 1;
	}
	
	p = (struct UI_Stack *)rt_malloc(sizeof(struct UI_Stack));
	p->init=func_init;
	p->clear=func_clear;
	p->display=func_display;
	p->action=func_action;
	p->next=ui_stack;
	p->load=func_load;
	ui_stack=p;
	return 0;
}

void UI_Page_Delete(void)
{
	if(ui_stack->next != RT_NULL)
	{
		ui_stack=ui_stack->next;
	}
}

void UI_Page_Clear(void)
{
	while(ui_stack->next != RT_NULL)
	{
		ui_stack=ui_stack->next;
	}
}


void UI_Thread_Entry(void *param)
{
	rt_err_t uwRet = RT_EOK;
	char msg;
	struct UI_Stack *p,*t;
	uint16_t noinput=0;//表示多久没有输入
	
	ui_stack = (struct UI_Stack *)rt_malloc(sizeof(struct UI_Stack));
	ui_stack->init = Main_Page_Init;
	ui_stack->clear = Main_Page_Clear;
	ui_stack->display = Main_Page_Display;
	ui_stack->action = Main_Page_Action;
	ui_stack->load = Main_Page_Load;
	ui_stack->next=RT_NULL;
	
	p = ui_stack;
	
	p->init(RT_NULL);
	while(1)
	{
		if(p != ui_stack)
		{
			if(noinput == 1001)
			{
				noinput = 1002;
			}else if(noinput == 1002)
			{
				noinput = 1002;
			}else if(noinput <= 1000)
			{
				noinput = 0;
			}
			//处理新增界面或者删除不需要的界面
			while(1)
			{
				t = ui_stack;
				while(t != RT_NULL)
				{
					if(t == p)
					{
						break;
					}else
					{
						t = t->next;
					}
				}
				if(t == RT_NULL)
				{
					p->clear(RT_NULL);
					t=p;
					p=p->next;
					rt_free(t);
				}else
				{
					p=ui_stack;
				}
				if(p==ui_stack)
				{
					p->load(RT_NULL);
					break;
				}
			}
		}
		//显示
		if(noinput == 1000)
		{
			noinput++;
			OLED_GRAM_ClearScreen();
			OLED_GRAM_Reflash();
			OLED_OFF();
			t = ui_stack;
			while(ui_stack->next!=RT_NULL)
			{
				ui_stack->clear(RT_NULL);
				t = ui_stack;
				ui_stack=ui_stack->next;
				rt_free(t);
			}
			ui_stack->load(RT_NULL);
			p=ui_stack;
		}else if(noinput == 1002)
		{
			noinput=0;
			OLED_ON();
			OLED_GRAM_ClearScreen();
			p->display(RT_NULL);
		}else if(noinput < 1000)
		{
			p->display(RT_NULL);
		}
		//等待按键输入
		uwRet = rt_mq_recv(inputsig_mq,&msg,1,0);
		if(uwRet == RT_EOK)
		{
			p->action(msg);
			if(noinput == 1001)
			{
				noinput++;
			}else
			{
				noinput=0;
			}
		}else
		{
			if(noinput < 1000)
			{
				noinput++;
			}
		}
		rt_thread_delay(10);
	}
}

