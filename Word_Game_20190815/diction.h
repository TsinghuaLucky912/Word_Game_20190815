#pragma once
#include "resolver.h" //�ֵ�ģ���� �ڵ��ý���ģ��


struct Dictionary;//֮���Խ��нṹ�����������Ƕ��� ���Ǳ����û������ֵ��ڲ���ʾ

struct Dictionary* dict_load(const char* file);//���ݴ��������ļ�����װ���ֵ�Դ
void               dict_unload();//�ͷ��ֵ�Դ
int                dict_word_count();//�������е��ʵĸ���
const char* dict_get_word(int index);//�����±귵�ض�Ӧ�ĵ���