#ifndef SEMESTERAUFGABE_CONSOLE_H
#define SEMESTERAUFGABE_CONSOLE_H

#define SHOW_FULL_BATTLEGROUND 0
#define MIN_SHIP_LENGTH 1 /*Das Standartspiel wird hiervon nicht beeinflusst*/
#define MAX_SHIP_LENGTH 7

void draw_intro();

void draw_screen(char **matrix, int size);

void player_draw_screen(char **matrix, int size);

void print_stats(int **stats1, int **stats2, int ship_class_count);

void player_set_ships(char **matrix, int size, int *ships, int ship_count, int player_turn);

void get_settings(int *single, int *diff, int *standart);

int get_battleground_size();

int get_ships(int **ships, int *ship_count, int size);

void show_player_battleground(char **matrix, int size, int player_turn);

int *player_move(char **matrix, int size, int player_turn);

int response(char **matrix, int size, int *shot, int hit, int downed, int player);

void clear_screen();

void flush();

#endif
