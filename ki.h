//
// Created by NoahB on 04.01.20.
//

#ifndef SEMESTERAUFGABE_KI_H
#define SEMESTERAUFGABE_KI_H

int * ai_diff3(char **matrix, int size, int difficulty);
int is_useful(char **matrix, int y, int x, int size, int difficulty);
int * get_from_solo(char **matrix, int y, int x, int difficulty);
int * get_from_double(char **matrix, int y, int x, int difficulty);
int ai_set_ships(char **matrix, int size, int *ships, int ship_count);


#endif //SEMESTERAUFGABE_KI_H
