#ifndef SEMESTERAUFGABE_KI_H
#define SEMESTERAUFGABE_KI_H

int *ai_diff3(char **matrix, int size, int difficulty);

int is_useful(char **matrix, int y, int x, int size, int difficulty);

int *get_from_solo(char **matrix, int y, int x, int difficulty);

int *get_from_double(char **matrix, int y, int x, int difficulty);


#endif
