#pragma once

#include <stdbool.h>

#ifndef GLCONSOLE_EXPORTS
#define GLMXAPI __declspec(dllimport)
#pragma comment(lib, "glConsole.lib")
#else
#define GLMXAPI __declspec(dllexport)
#endif

#define WND_SPLIT_HORIZONTAL    0
#define WND_SPLIT_VERTICAL      1

#define TEXT_ALIGN_LEFT         0
#define TEXT_ALIGN_CENTER       1
#define TEXT_ALIGN_RIGHT        2

// 控制台初始化
GLMXAPI bool glmxConsole_Init();
GLMXAPI void glmxConsole_Release();

// 窗口功能
GLMXAPI int  glmxConsole_CreateWindow(int width, int height, const char *title);
GLMXAPI bool glmxConsole_SplitWindow(int wid, int pos, int dir, char c, int color, int *id1, int *id2);
GLMXAPI bool glmxConsole_GetWindowRect(int wid, int *x, int *y, int *w, int *h);
GLMXAPI bool glmxConsole_GetDrawRect(int wid, int *x, int *y, int *w, int *h);
GLMXAPI void glmxConsole_WndDrawText(int wid, int x, int y, const char *text);
GLMXAPI void glmxConsole_WndDrawTextEx(int wid, int x, int y, int color, const char *text);
GLMXAPI void glmxConsole_WndDrawFormatText(int wid, int x, int y, int color, const char *text, int format);

// 控制台功能
GLMXAPI void glmxConsole_SetTitle(const char *title);
GLMXAPI void glmxConsole_SetTextColor(int color);
GLMXAPI void glmxConsole_SetCursorPosition(int x, int y);
GLMXAPI void glmxConsole_DrawChar(int x, int y, char c);
GLMXAPI void glmxConsole_DrawCharEx(int x, int y, int color, char c);
GLMXAPI void glmxConsole_DrawText(int x, int y, const char *text);
GLMXAPI void glmxConsole_DrawTextEx(int x, int y, int color, const char *text);

// 辅助函数
GLMXAPI int  glmxConsole_Rand(int base);
GLMXAPI void glmxConsole_Sleep(int ms);