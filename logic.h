#ifndef SEMESTERAUFGABE_LOGIC_H
#define SEMESTERAUFGABE_LOGIC_H

#ifndef OUT_OF_MEMORY
#define OUT_OF_MEMORY (-69420)
#endif

/*Das Standartspiel wird hiervon nicht beeinflusst*/
#define MIN_BATTLEGROUND_SIZE 10 /*Darf nicht < 3 sein*/
#define MAX_BATTLEGROUND_SIZE 20 /*Ein Wert größer als 99 fuehrt zu UI Problemen (wenn es ueberhaupt passt)*/

#define MIN_SHIP_LENGTH 2 /*Darf nicht < 2 sein*/
#define MAX_SHIP_LENGTH 7
#define SHIPS_LIMIT 20

#define SHIP_MASS_THRESHOLD 0.95 /*Verhindert ueberladen der Matrix*/

int init_battleground(char ***battleground, int size);

int init_stats(int ***stats1, int ***stats2, const int *ships, int ship_count);

void updateStats(int **stats, int ship_class_count, int hit);

void set_ships_stats(int **stats, int ship_class_count, const int *ships, int ship_count);

void reset_battleground(char **matrix, int size);

int rand_set_ships(char **matrix, int size, int *ships, int ship_count);

int set_ship(char **matrix, int size, int y, int x, int direction, int ship_length);

int ship_mass_validation(int size, const int *ships, int ship_count);

int shoot(char **matrix, int y, int x);

int check_downed(char **matrix, int size, int y, int x);

int downed_maker(char **matrix, int size, int y, int x, int dy, int dx);

int check_downed_helper(char **matrix, int size, int y, int x, int dy, int dx);

int is_end_game(char **matrix, int size);

int compare(const void *a, const void *b);

#endif
