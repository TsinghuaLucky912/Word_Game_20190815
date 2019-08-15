#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glConsole.h"
#include "display.h"
#include "emitter.h"

int about_window = -1;
int score_window = -1;
int emitter_window = -1;
int input_window = -1;

void view_init()
{
	int main_window;
	int bottom_window1, bottom_window2;

	main_window = glmxConsole_CreateWindow(45, 30, "word-pop");
	glmxConsole_SplitWindow(main_window, 4, WND_SPLIT_HORIZONTAL, '-', 7, &about_window, &bottom_window1);
	glmxConsole_SplitWindow(bottom_window1, 2, WND_SPLIT_HORIZONTAL, '-', 6, &score_window, &bottom_window2);
	glmxConsole_SplitWindow(bottom_window2, 19, WND_SPLIT_HORIZONTAL, '-', 5, &emitter_window, &input_window);
}

void view_release()
{
}

void view_show_appinfo()
{
	glmxConsole_WndDrawFormatText(about_window, 0, 1, 12, "WORD-POP", TEXT_ALIGN_CENTER);
	glmxConsole_WndDrawFormatText(about_window, 0, 2, 12, "> GLIMIX STUDIO <", TEXT_ALIGN_CENTER);
	glmxConsole_WndDrawFormatText(about_window, 0, 2, 12, "ZYF", TEXT_ALIGN_RIGHT);
}

void view_show_score(int killed, int missed)
{
	char buffer[64];

	sprintf_s(buffer, 64, "KILLED: %d", killed);
	glmxConsole_WndDrawTextEx(score_window, 0, 0, 13, buffer);

	sprintf_s(buffer, 64, "MISSED: %d", missed);
	glmxConsole_WndDrawTextEx(score_window, 0, 1, 13, buffer);
}

void view_show_level(int level, int speed)
{
	char buffer[64];

	sprintf_s(buffer, 64, "LEVEL: %d", level);
	glmxConsole_WndDrawFormatText(score_window, 0, 0, 13, buffer, TEXT_ALIGN_RIGHT);

	sprintf_s(buffer, 64, "SPEED: %d", speed);
	glmxConsole_WndDrawFormatText(score_window, 0, 1, 13, buffer, TEXT_ALIGN_RIGHT);
}

void view_show_input_prompt()
{
	glmxConsole_WndDrawTextEx(input_window, 0, 0, 9, ">>");
}

void view_show_input_word(const char* word)
{
	glmxConsole_WndDrawTextEx(input_window, 2, 0, 9, word);
}

int view_emitter_winid()
{
	return emitter_window;
}

void view_show_popwords()//��ʾ ����������ʾģ��ĵ���
{
	for (int i = 0; i < emit_word_count(); ++i)
	{
		if (emit_get_word(i)->word != NULL && emit_get_word(i)!=NULL)
			glmxConsole_WndDrawTextEx(emitter_window, emit_get_word(i)->x,
				emit_get_word(i)->y, emit_get_word(i)->color, emit_get_word(i)->word);
	}
}

void view_clear_emitwnd()// ��շ��䴰��
{
	for (int i = 0; i < emit_word_count(); ++i)
	{
		if (emit_get_word(i)->word != NULL && emit_get_word(i) != NULL)
		{
			char word_buff[20];//�������ʵ��ı���ʾ
			memset(word_buff, ' ', 20);//ȫ����Ϊ�ո�
			word_buff[strlen(emit_get_word(i)->word)] = '\0';//�ѵ��ʳ����ı��ض�
			glmxConsole_WndDrawTextEx(emitter_window, emit_get_word(i)->x,
				emit_get_word(i)->y, emit_get_word(i)->color, word_buff);
		}
	}
}

/*
������������Ŀ�ģ���������Ч��

�ٶ�killAnim �趨һ����Ϊ0�ĳ�ֵ��Ȼ���Լ�

һֱ������0 ��ʱ�򣬾���Ҫ�������clear���и���

*/

void view_do_killanim()
{
	for (int i = 0; i < emit_word_count(); ++i)
	{
		if (emit_get_word(i)->killAnim != 0)
		{
			if (emit_get_word(i)->killAnim % 2 == 0)
				glmxConsole_WndDrawTextEx(emitter_window, emit_get_word(i)->x,
					emit_get_word(i)->y, emit_get_word(i)->color, emit_get_word(i)->word);
			else glmxConsole_WndDrawTextEx(emitter_window, emit_get_word(i)->x,
				emit_get_word(i)->y, emit_get_word(i)->color + 1, emit_get_word(i)->word);

			emit_get_word(i)->killAnim--;
			if (emit_get_word(i)->killAnim == 0)
			{
				char word_buff[20];//�������ʵ��ı���ʾ
				memset(word_buff, ' ', 20);//ȫ����Ϊ�ո�
				word_buff[strlen(emit_get_word(i)->word)] = '\0';//�ѵ��ʳ����ı��ض�
				glmxConsole_WndDrawTextEx(emitter_window, emit_get_word(i)->x,
					emit_get_word(i)->y, emit_get_word(i)->color, word_buff);
				emit_get_word(i)->word = NULL;
			}
		} 
	}
}