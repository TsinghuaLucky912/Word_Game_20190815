#include <stdlib.h>
#include <string.h>
#include "emitter.h"
#include "diction.h"

struct WordEmitter
{
	struct Word words[5];
	int         win_width;
	int         win_height;
} g_emitter;

void emit_init(int winWidth, int winHeight)
{
	g_emitter.win_width = winWidth;
	g_emitter.win_height = winHeight;
}

void emit_release()
{
}

const char* emit_rand_word()
{
	return "hello";
}

void emit_words(struct Dictionary* wordbook)
{
}

bool emit_hittest(const char* word)
{
	return false;
}

int emit_update()
{
	return 0;
}

int emit_word_count()
{
	return 5;
}

struct Word* emit_get_word(int index)
{
	return &g_emitter.words[index];
}
