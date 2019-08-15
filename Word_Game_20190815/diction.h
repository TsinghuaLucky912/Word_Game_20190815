#pragma once

struct Dictionary;

struct Dictionary* dict_load(const char* file);
void               dict_unload();
int                dict_word_count();
const char* dict_get_word(int index);