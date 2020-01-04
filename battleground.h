#ifndef SEMESTERAUFGABE_BATTLEGROUND_H
#define SEMESTERAUFGABE_BATTLEGROUND_H

#ifndef OUT_OF_MEMORY
#define OUT_OF_MEMORY -69420
#endif

int get_battleground_size();
int init_battleground(char **battleground, int size);
int rand_set_ships(char **matrix, int size, int *ships, int ship_count);
int set_ship(char **matrix, int size, int y, int x, int direction, int ship_length);

#endif
