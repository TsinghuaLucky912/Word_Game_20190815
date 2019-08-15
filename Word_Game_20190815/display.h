#pragma once
void view_init();
void view_release();

void view_show_appinfo();

void view_show_score(int killed, int missed);
void view_show_level(int level, int speed);

void view_show_popwords();

void view_show_input_prompt();
void view_show_input_word(const char* word);

int  view_emitter_winid();
void view_clear_emitwnd();

void view_do_killanim();