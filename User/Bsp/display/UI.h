#ifndef __UI_H
#define __UI_H

#include "ff.h"

extern FIL UI_FILE;

void UI_Thread_Entry(void *param);

char UI_Page_Add(char (*func_init)(void *param),
	void (*func_clear)(void *param),
		void (*func_display)(void *param),
			void (*func_load)(void *param),
				void (*func_action)(char param),
					void *init_param);

void UI_Page_Delete(void);
void UI_Page_Clear(void);

#endif

