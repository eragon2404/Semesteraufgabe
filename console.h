#ifndef SEMESTERAUFGABE_CONSOLE_H
#define SEMESTERAUFGABE_CONSOLE_H

void draw_intro();

void draw_screen(char **matrix, int size);

void player_set_ships(char **matrix, int size, int *ships, int ship_count);

void getSettings(int *single, int *diff, int *standart);

int get_battleground_size();

int get_ships(int **ships, int *ship_count, int size);

int * player_move(char **matrix, int size, int  player_turn);

int response(char **matrix, int size, int *shot, int hit, int player);

int check_move(char **matrix, int size, int x, int y);

void clear_screen();

void flush();

#endif
