#pragma once


typedef void (*PFNFOUNDWORD)(const char* word);//����һ������ָ�����ͣ���Ϊ�����Ļص�


/*
parse_word������Ҫ��Ϊ�ֵ�Դģ����е��õ�
���þ��ǣ��Դ�����ļ������е��ʵ��и�
*/
void parse_word(const char* fname, PFNFOUNDWORD pfnFoundCallback); 