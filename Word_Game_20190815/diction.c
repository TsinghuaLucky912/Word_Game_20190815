#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "diction.h"
#include "resolver.h"

#define MAX_WORDS   256

struct Dictionary
{
	char* words[MAX_WORDS];
	char* fname;
	int   count;
};

void dict_addword(const char* word);
int  dict_findword(const char* word);

struct Dictionary g_dictionary;

struct Dictionary* dict_load(const char* file)
{
	return &g_dictionary;
}

void dict_addword(const char* word)
{
}

int dict_findword(const char* word)
{
	return -1;
}

void dict_unload()
{
}

int dict_word_count()
{
	return -1;
}

const char* dict_get_word(int index)
{
	return "hello";
}