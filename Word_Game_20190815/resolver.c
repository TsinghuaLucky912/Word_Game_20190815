#include <stdio.h>
#include <ctype.h>
#include "resolver.h"
#include <assert.h>
#include <stdlib.h>

#define begin 0
#define inword 1 
#define outword 2


//传入其中的两个参数：文件名                   函数名
void parse_word(const char* fname, PFNFOUNDWORD pfnFoundCallback)
{
	//作用就是：对传入的文件，进行单词的切割。供字典源调用
	FILE* pf = fopen(fname, "r");
	if (pf == NULL)
		return;

	char word_buff[20] = { 0 };//保存切割下来的单词的
	char* ptr = word_buff;

	char ch;//用来接收文件的字符
	int flag = begin;//开始检查每一个字符
	while (!feof(pf))//判断这个文件是否读取结束  到末尾则为真
	{
		ch = fgetc(pf);
		switch (flag)
		{
		case begin:
			if (isalpha(ch))//如果是字母
			{
				flag = inword;//有可能还在单词里面
				*ptr = ch;
			}
			else//不是字母
			{
				flag = outword;//还是单词外
				ptr--;//这里-- 是因为后面统一++
			}
			break;
		case inword:
			if (isalpha(ch))//如果这个字符是字母
			{
				*ptr = ch;//继续
			}
			else//既然不是字母了，那么肯定是一个单词结束了
			{
				if (ch == ' ')//当前字符是空格，正好前面是一个单词
				{
					flag = begin;//重新开始
					*ptr = '\0';//这个单词结束了

					if (pfnFoundCallback)
						pfnFoundCallback(word_buff);//可以把这个单词交给字典源模块

					//处理完一个单词之后，就相当于要重新开始切割单词了
					ptr = word_buff;
					ptr--;//这里-- 是因为后面统一++
				}
				else//不是空格 不是字母 那我也不知道是个啥
				{
					flag = outword;
					ptr = word_buff;
					ptr--;//这里-- 是因为后面统一++
				}
			}
			break;
		case outword:
			if (isalpha(ch))//说明进入一个单词里面了
			{
				flag = inword;
				*ptr = ch;
			}
			else
			{
				flag = outword;//还在单词外面
				ptr--;
			}
			break;
		}
		ptr++;
	}
	fclose(pf);
}