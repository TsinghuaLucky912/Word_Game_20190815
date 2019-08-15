#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

#include "diction.h"
#include "display.h"
#include "emitter.h"

#include "glConsole.h"

int time_to_speed(int time)
{
	int tab[6] = { 25, 20, 17, 14, 12, 10 };
	int speed = 1;

	for (int i = 0; i < 5; i++)
	{
		if (tab[i] == time)
		{
			speed = (i + 1);
			break;
		}
	}

	return speed;
}

int main()
{
	struct Dictionary* dict;        // 字典数据

	char input_buf[32] = { 0 };     // 单词输入缓冲区
	int  input_buf_pos = 0;         // 单词输入缓冲区索引
	bool input_pos_back = false;    // 输入位置是否回退

	int emit_speed = 45;            // 单词发射速度(每当前计数发射一次)
	int emit_speed_count = 0;       // 单词发射速度计数器

	int word_killed = 0;            // 命中单词计数
	int word_missed = 0;            // 丢失单词计数

	int game_level = 1;             // 游戏等级

	bool update_score = false;
	bool update_level = false;

	srand((unsigned int)time(0));

	// 载入字典
	dict = dict_load("words.txt");

	// 初始化控制台功能
	glmxConsole_Init();

	// 初始化视图
	view_init();

	// 初始化单词发射器
	int w, h;
	glmxConsole_GetWindowRect(view_emitter_winid(), NULL, NULL, &w, &h);
	emit_init(w, h - 1);

	// 显示应用程序信息
	view_show_appinfo();

	// 发射一组单词
	emit_words(dict);

	// 显示成绩与游戏信息
	view_show_score(word_killed, word_missed);
	view_show_level(game_level, time_to_speed(emit_speed));

	view_show_popwords();       // 显示发射的单词
	view_show_input_prompt();   // 显示输入提示符

	while (1)
	{
		// 如果分数有变化就更新显示
		if (update_score)
		{
			view_show_score(word_killed, word_missed);
			update_score = false;
		}

		if (update_level)
		{
			view_show_level(game_level, emit_speed);
			update_level = false;
		}

		// 计数到达下一轮发射时间后发射单词
		if (emit_speed_count >= emit_speed)
		{
			emit_words(dict);       // 发射一组单词
			view_clear_emitwnd();   // 清空发射窗口

			// 更新一次代表现有单词向下移动一行
			// 获取当前丢失的单词个数
			int missed = emit_update();
			if (missed > 0)
			{
				word_missed += missed;  // 丢失计数加一
				update_score = true;    // 表示需要更新成绩
			}

			view_show_popwords();   // 显示新发射单词
			emit_speed_count = 0;   // 重置发射器计数
		}
		else
		{
			// 累加用于下次发射单词
			emit_speed_count += 1;
		}

		// 拦截键盘输入
		if (_kbhit())
		{
			int ch = _getch();

			if (isalpha(ch))
			{
				input_buf[input_buf_pos++] = ch;    // 保存字符
				input_buf[input_buf_pos] = '\0';    // 结束以形成字符串
			}
			else if (ch == '\b')
			{
				// 输入一个字符后 [input_buf_pos] 在下一位置
				if ((input_buf_pos - 1) >= 0)
				{
					// 清空原输入最后一个字符
					input_buf[--input_buf_pos] = ' ';
					view_show_input_word(input_buf);

					// 更改结束位置(保证光标位置正确)
					input_buf[input_buf_pos] = '\0';
				}
			}
			else if (ch == '\r')
			{
				input_buf[input_buf_pos++] = '\0';  // 结束以形成字符串
				input_buf_pos = 0;                  // 重置输入缓冲索引

				// 输入单词命中性测试
				if (emit_hittest(input_buf))
				{
					word_killed += 1;               // 击杀了一个单词
					update_score = true;            // 需要更新成绩
				}

				// 提交(回车)后清空当前的输入
				int length = strlen(input_buf);
				memset(input_buf, ' ', sizeof(char) * 32);
				input_buf[length] = '\0';

				// 上面的清空导致插入符在指定长度字符串后面
				// 指示插入符回退到输入提示符后面
				input_pos_back = true;
			}
		}

		// 执行杀死单词动画
		view_do_killanim();

		// 显示用户输入的单词
		view_show_input_word(input_buf);

		// 提交单词后回退插入符
		if (input_pos_back)
		{
			input_buf[0] = '\0';
			input_pos_back = false;
		}

		// 每40毫秒接收一次用户输入
		glmxConsole_Sleep(40);
	}

	// 视图资源清理
	view_release();

	// 控制台清理
	glmxConsole_Release();

	// 字典清理
	dict_unload();

	return 0;
}