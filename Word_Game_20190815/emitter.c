#include <stdlib.h>
#include <string.h>
#include "emitter.h"
#include "diction.h"
#include <time.h>


static int times = 0;//ʹ����ĵ��ʶ���ʼ���ڵ�һ��
struct WordEmitter
{
	struct Word words[5];
	int         win_width;
	int         win_height;
} g_emitter;

void emit_init(int winWidth, int winHeight)//�����Ҫ�ǹ��췢�����Ĵ��ڰ��
{
	g_emitter.win_width = winWidth;
	g_emitter.win_height = winHeight;
}

void emit_release()
{
}


void emit_words()//���ֵ�Դ��ȡĬ����Ŀ�ĵ���
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
				//�����Ѿ�Խ��,�����ƶ�һ��
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

bool emit_hittest(const char* word)//�ж�������ַ� �Ƿ���ƥ���
{
	for (int i = 0; i < emit_word_count(); ++i)
	{
		if (g_emitter.words[i].word != NULL && strcmp(g_emitter.words[i].word, word)==0)
		{
			g_emitter.words[i].killAnim = 10;//��˸����
			return true;//�ɹ�ƥ��
		}
			
	}
	return false;
}

int emit_update()//����������,�������µ� miss����
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
	return 5;//�����Ĭ��5������
}

struct Word* emit_get_word(int index)
{
	return &g_emitter.words[index];//���ظ����±������
}
