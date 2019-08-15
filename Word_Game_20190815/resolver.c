#include <stdio.h>
#include <ctype.h>
#include "resolver.h"
#include <assert.h>
#include <stdlib.h>

#define begin 0
#define inword 1 
#define outword 2


//�������е������������ļ���                   ������
void parse_word(const char* fname, PFNFOUNDWORD pfnFoundCallback)
{
	//���þ��ǣ��Դ�����ļ������е��ʵ��и���ֵ�Դ����
	FILE* pf = fopen(fname, "r");
	if (pf == NULL)
		return;

	char word_buff[20] = { 0 };//�����и������ĵ��ʵ�
	char* ptr = word_buff;

	char ch;//���������ļ����ַ�
	int flag = begin;//��ʼ���ÿһ���ַ�
	while (!feof(pf))//�ж�����ļ��Ƿ��ȡ����  ��ĩβ��Ϊ��
	{
		ch = fgetc(pf);
		switch (flag)
		{
		case begin:
			if (isalpha(ch))//�������ĸ
			{
				flag = inword;//�п��ܻ��ڵ�������
				*ptr = ch;
			}
			else//������ĸ
			{
				flag = outword;//���ǵ�����
				ptr--;//����-- ����Ϊ����ͳһ++
			}
			break;
		case inword:
			if (isalpha(ch))//�������ַ�����ĸ
			{
				*ptr = ch;//����
			}
			else//��Ȼ������ĸ�ˣ���ô�϶���һ�����ʽ�����
			{
				if (ch == ' ')//��ǰ�ַ��ǿո�����ǰ����һ������
				{
					flag = begin;//���¿�ʼ
					*ptr = '\0';//������ʽ�����

					if (pfnFoundCallback)
						pfnFoundCallback(word_buff);//���԰�������ʽ����ֵ�Դģ��

					//������һ������֮�󣬾��൱��Ҫ���¿�ʼ�и����
					ptr = word_buff;
					ptr--;//����-- ����Ϊ����ͳһ++
				}
				else//���ǿո� ������ĸ ����Ҳ��֪���Ǹ�ɶ
				{
					flag = outword;
					ptr = word_buff;
					ptr--;//����-- ����Ϊ����ͳһ++
				}
			}
			break;
		case outword:
			if (isalpha(ch))//˵������һ������������
			{
				flag = inword;
				*ptr = ch;
			}
			else
			{
				flag = outword;//���ڵ�������
				ptr--;
			}
			break;
		}
		ptr++;
	}
	fclose(pf);
}