#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "diction.h"
#include "resolver.h"//要使用解析模块

#define MAX_WORDS   256


struct Dictionary
{
	char* words[MAX_WORDS];//底层数据结构为一数组
	char* fname;
	int   count;
};
struct Dictionary g_dictionary;//定义这个结构体变量为全局变量
bool dict_findword(const char* word);
void dict_addword(const char* word)//通过函数指针 调用这个方法，将切好的单词加入字典
{
	if (dict_findword(word))
		//在parse_word函数中调用,将一个切割好的单词存放到字典中
		g_dictionary.words[g_dictionary.count++] = strdup(word);
}
bool dict_findword(const char* word)//如果字典源里面已有这个单词word 就没必要再加一次
{
	//所以这个函数的作用就是查看一下这个字典里面有无这个单词
	for (int i = 0; i < g_dictionary.count; ++i)
	{
		if (stricmp(g_dictionary.words[i], word)==0)
			return false;//说明有这个单词
	}
	return true;//字典里面没有 可以插入字典
}



struct Dictionary* dict_load(const char* file)//根据传入的这个文件名，装载字典源
{
	dict_unload();//每次装载一个，就需要提前把这个 释放一下
	parse_word(file, dict_addword);
	g_dictionary.fname = strdup(file);//把这个单词源也给保存一份
	return &g_dictionary;
}


void dict_unload()//释放字典源
{
	if (g_dictionary.count!=0)//不为0  释放才有意义
	{
		for (int i = 0; i < g_dictionary.count; ++i)
		{
			free(g_dictionary.words[i]);//刚才在add的时候做的是深拷贝
			g_dictionary.words[i] = NULL;//预防野指针
		}

		//刚才我们也把单词源给strdup了一份
		free(g_dictionary.fname);
		g_dictionary.fname = NULL;
		g_dictionary.count = 0;//此时字典源已经被释放
	}
}

int dict_word_count()//返回其中单词的个数
{
	return g_dictionary.count;
}

const char* dict_get_word(int index)//根据下标返回对应的单词
{
	return g_dictionary.words[index];
}