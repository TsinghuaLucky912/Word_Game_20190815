#pragma once


typedef void (*PFNFOUNDWORD)(const char* word);

int parse_word(const char* fname, PFNFOUNDWORD pfnFoundCallback);