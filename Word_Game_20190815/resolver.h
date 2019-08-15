#pragma once


typedef void (*PFNFOUNDWORD)(const char* word);//定义一个函数指针类型，作为函数的回调


/*
parse_word函数主要是为字典源模块进行调用的
作用就是：对传入的文件，进行单词的切割
*/
void parse_word(const char* fname, PFNFOUNDWORD pfnFoundCallback); 