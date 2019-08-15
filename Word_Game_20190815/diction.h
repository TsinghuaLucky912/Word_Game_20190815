#pragma once
#include "resolver.h" //字典模块是 在调用解析模块


struct Dictionary;//之所以进行结构体声明，而非定义 就是避免用户看见字典内部表示

struct Dictionary* dict_load(const char* file);//根据传入的这个文件名，装载字典源
void               dict_unload();//释放字典源
int                dict_word_count();//返回其中单词的个数
const char* dict_get_word(int index);//根据下标返回对应的单词