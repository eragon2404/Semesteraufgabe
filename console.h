#ifndef SEMESTERAUFGABE_CONSOLE_H
#define SEMESTERAUFGABE_CONSOLE_H

void draw_intro();
void draw_screen(char **matrix, int size);
void player_set_ships(char **matrix, int size, int *ships, int ship_count);

void clear_screen();
void flush();

#endif
