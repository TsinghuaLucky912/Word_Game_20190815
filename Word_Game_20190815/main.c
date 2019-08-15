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
	struct Dictionary* dict;        // �ֵ�����

	char input_buf[32] = { 0 };     // �������뻺����
	int  input_buf_pos = 0;         // �������뻺��������
	bool input_pos_back = false;    // ����λ���Ƿ����

	int emit_speed = 45;            // ���ʷ����ٶ�(ÿ��ǰ��������һ��)
	int emit_speed_count = 0;       // ���ʷ����ٶȼ�����

	int word_killed = 0;            // ���е��ʼ���
	int word_missed = 0;            // ��ʧ���ʼ���

	int game_level = 1;             // ��Ϸ�ȼ�

	bool update_score = false;
	bool update_level = false;

	srand((unsigned int)time(0));

	// �����ֵ�
	dict = dict_load("words.txt");

	// ��ʼ������̨����
	glmxConsole_Init();

	// ��ʼ����ͼ
	view_init();

	// ��ʼ�����ʷ�����
	int w, h;
	glmxConsole_GetWindowRect(view_emitter_winid(), NULL, NULL, &w, &h);
	emit_init(w, h - 1);

	// ��ʾӦ�ó�����Ϣ
	view_show_appinfo();

	// ����һ�鵥��
	emit_words(dict);

	// ��ʾ�ɼ�����Ϸ��Ϣ
	view_show_score(word_killed, word_missed);
	view_show_level(game_level, time_to_speed(emit_speed));

	view_show_popwords();       // ��ʾ����ĵ���
	view_show_input_prompt();   // ��ʾ������ʾ��

	while (1)
	{
		// ��������б仯�͸�����ʾ
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

		// ����������һ�ַ���ʱ����䵥��
		if (emit_speed_count >= emit_speed)
		{
			emit_words(dict);       // ����һ�鵥��
			view_clear_emitwnd();   // ��շ��䴰��

			// ����һ�δ������е��������ƶ�һ��
			// ��ȡ��ǰ��ʧ�ĵ��ʸ���
			int missed = emit_update();
			if (missed > 0)
			{
				word_missed += missed;  // ��ʧ������һ
				update_score = true;    // ��ʾ��Ҫ���³ɼ�
			}

			view_show_popwords();   // ��ʾ�·��䵥��
			emit_speed_count = 0;   // ���÷���������
		}
		else
		{
			// �ۼ������´η��䵥��
			emit_speed_count += 1;
		}

		// ���ؼ�������
		if (_kbhit())
		{
			int ch = _getch();

			if (isalpha(ch))
			{
				input_buf[input_buf_pos++] = ch;    // �����ַ�
				input_buf[input_buf_pos] = '\0';    // �������γ��ַ���
			}
			else if (ch == '\b')
			{
				// ����һ���ַ��� [input_buf_pos] ����һλ��
				if ((input_buf_pos - 1) >= 0)
				{
					// ���ԭ�������һ���ַ�
					input_buf[--input_buf_pos] = ' ';
					view_show_input_word(input_buf);

					// ���Ľ���λ��(��֤���λ����ȷ)
					input_buf[input_buf_pos] = '\0';
				}
			}
			else if (ch == '\r')
			{
				input_buf[input_buf_pos++] = '\0';  // �������γ��ַ���
				input_buf_pos = 0;                  // �������뻺������

				// ���뵥�������Բ���
				if (emit_hittest(input_buf))
				{
					word_killed += 1;               // ��ɱ��һ������
					update_score = true;            // ��Ҫ���³ɼ�
				}

				// �ύ(�س�)����յ�ǰ������
				int length = strlen(input_buf);
				memset(input_buf, ' ', sizeof(char) * 32);
				input_buf[length] = '\0';

				// �������յ��²������ָ�������ַ�������
				// ָʾ��������˵�������ʾ������
				input_pos_back = true;
			}
		}

		// ִ��ɱ�����ʶ���
		view_do_killanim();

		// ��ʾ�û�����ĵ���
		view_show_input_word(input_buf);

		// �ύ���ʺ���˲����
		if (input_pos_back)
		{
			input_buf[0] = '\0';
			input_pos_back = false;
		}

		// ÿ40�������һ���û�����
		glmxConsole_Sleep(40);
	}

	// ��ͼ��Դ����
	view_release();

	// ����̨����
	glmxConsole_Release();

	// �ֵ�����
	dict_unload();

	return 0;
}