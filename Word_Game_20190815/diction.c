#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "diction.h"
#include "resolver.h"//Ҫʹ�ý���ģ��

#define MAX_WORDS   256


struct Dictionary
{
	char* words[MAX_WORDS];//�ײ����ݽṹΪһ����
	char* fname;
	int   count;
};
struct Dictionary g_dictionary;//��������ṹ�����Ϊȫ�ֱ���
bool dict_findword(const char* word);
void dict_addword(const char* word)//ͨ������ָ�� ����������������кõĵ��ʼ����ֵ�
{
	if (dict_findword(word))
		//��parse_word�����е���,��һ���и�õĵ��ʴ�ŵ��ֵ���
		g_dictionary.words[g_dictionary.count++] = strdup(word);
}
bool dict_findword(const char* word)//����ֵ�Դ���������������word ��û��Ҫ�ټ�һ��
{
	//����������������þ��ǲ鿴һ������ֵ����������������
	for (int i = 0; i < g_dictionary.count; ++i)
	{
		if (stricmp(g_dictionary.words[i], word)==0)
			return false;//˵�����������
	}
	return true;//�ֵ�����û�� ���Բ����ֵ�
}



struct Dictionary* dict_load(const char* file)//���ݴ��������ļ�����װ���ֵ�Դ
{
	dict_unload();//ÿ��װ��һ��������Ҫ��ǰ����� �ͷ�һ��
	parse_word(file, dict_addword);
	g_dictionary.fname = strdup(file);//���������ԴҲ������һ��
	return &g_dictionary;
}


void dict_unload()//�ͷ��ֵ�Դ
{
	if (g_dictionary.count!=0)//��Ϊ0  �ͷŲ�������
	{
		for (int i = 0; i < g_dictionary.count; ++i)
		{
			free(g_dictionary.words[i]);//�ղ���add��ʱ�����������
			g_dictionary.words[i] = NULL;//Ԥ��Ұָ��
		}

		//�ղ�����Ҳ�ѵ���Դ��strdup��һ��
		free(g_dictionary.fname);
		g_dictionary.fname = NULL;
		g_dictionary.count = 0;//��ʱ�ֵ�Դ�Ѿ����ͷ�
	}
}

int dict_word_count()//�������е��ʵĸ���
{
	return g_dictionary.count;
}

const char* dict_get_word(int index)//�����±귵�ض�Ӧ�ĵ���
{
	return g_dictionary.words[index];
}