#pragma once

#include <stdbool.h>

//struct Dictionary;

struct Word
{
	const char* word;
	int color;
	int killAnim;//0的时候 并不消除
	int x, y;
};

void emit_init(int winWidth, int winHeight);
void emit_release();

void emit_words();
bool emit_hittest(const char* word);
int  emit_update();

int emit_word_count();//给显示模块提供的单词个数
struct Word* emit_get_word(int index);//也是给显示模块用的
