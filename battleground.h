#ifndef SEMESTERAUFGABE_BATTLEGROUND_H
#define SEMESTERAUFGABE_BATTLEGROUND_H

#ifndef OUT_OF_MEMORY
#define OUT_OF_MEMORY -69420
#endif

#define SHIP_MASS_THRESHOLD 1/*0.69*/

#define SHIPS_LIMIT 15

int init_battleground(char ***battleground, int size);

void reset_battleground(char **matrix, int size);

int rand_set_ships(char **matrix, int size, int *ships, int ship_count);

int set_ship(char **matrix, int size, int y, int x, int direction, int ship_length);

int ship_mass_validation(int size, const int *ships, int ship_count);

#endif
