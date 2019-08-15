#pragma once

#include <stdbool.h>

//struct Dictionary;

struct Word
{
	const char* word;
	int color;
	int killAnim;//0��ʱ�� ��������
	int x, y;
};

void emit_init(int winWidth, int winHeight);
void emit_release();

void emit_words();
bool emit_hittest(const char* word);
int  emit_update();

int emit_word_count();//����ʾģ���ṩ�ĵ��ʸ���
struct Word* emit_get_word(int index);//Ҳ�Ǹ���ʾģ���õ�
