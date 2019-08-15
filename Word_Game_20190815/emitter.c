#include <stdlib.h>
#include <string.h>
#include "emitter.h"
#include "diction.h"
#include <time.h>


static int times = 0;//使后面的单词都初始化在第一行
struct WordEmitter
{
	struct Word words[5];
	int         win_width;
	int         win_height;
} g_emitter;

void emit_init(int winWidth, int winHeight)//这个主要是构造发射器的窗口板块
{
	g_emitter.win_width = winWidth;
	g_emitter.win_height = winHeight;
}

void emit_release()
{
}


void emit_words()//从字典源获取默认数目的单词
{
	srand((unsigned)time(NULL));
	int num = emit_word_count();
	for (int i = 0; i < num; ++i)
	{
		if (g_emitter.words[i].word == NULL)
		{
			g_emitter.words[i].word = dict_get_word(rand() % dict_word_count());
			g_emitter.words[i].color = rand() % 8 + 1;
			g_emitter.words[i].killAnim = 0;
			g_emitter.words[i].x = rand() % g_emitter.win_width;
			

			if (g_emitter.words[i].x + strlen(g_emitter.words[i].word) > g_emitter.win_width)
			{
				//单词已经越界,向左移动一点
				g_emitter.words[i].x -=
					(g_emitter.words[i].x + strlen(g_emitter.words[i].word) - g_emitter.win_width);
			}			
			if (times == 0)
			{
				g_emitter.words[i].y = i;
			}
			else g_emitter.words[i].y = 0;
		}
	}
	times++;
}

bool emit_hittest(const char* word)//判断输入的字符 是否有匹配的
{
	for (int i = 0; i < emit_word_count(); ++i)
	{
		if (g_emitter.words[i].word != NULL && strcmp(g_emitter.words[i].word, word)==0)
		{
			g_emitter.words[i].killAnim = 10;//闪烁次数
			return true;//成功匹配
		}
			
	}
	return false;
}

int emit_update()//单词向下落,计算落下的 miss个数
{
	int miss_word = 0;
	for (int i = 0; i < emit_word_count(); ++i)
	{
		struct Word* word = &g_emitter.words[i];
		if ( word->word != NULL && word->killAnim==0)
		{
			g_emitter.words[i].y++;
			if (word->y >= g_emitter.win_height)
			{
				g_emitter.words[i].word = NULL;
				miss_word++;
			}			
		}
	}
	return miss_word;
}

int emit_word_count()
{
	return 5;//这里就默认5个数据
}

struct Word* emit_get_word(int index)
{
	return &g_emitter.words[index];//返回给定下标的数据
}
