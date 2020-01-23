#ifndef SEMESTERAUFGABE_KI_H
#define SEMESTERAUFGABE_KI_H

int *ai_diff1(int size);

int *ai_diff2(char **matrix, int size, int *ships);

int *ai_diff3(char **matrix, int size, int *ships);

int is_useful(char **matrix, int y, int x, int size, int difficulty, const int *ships);

int *get_ai_turn(char **battleground, int size, int difficulty, int *ships);


#endif
