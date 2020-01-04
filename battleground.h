//
// Created by NoahB on 04.01.20.
//

#ifndef SEMESTERAUFGABE_BATTLEGROUND_H
#define SEMESTERAUFGABE_BATTLEGROUND_H

int getBattlegroundSize();
int initBattleground(char **battleground, int size);
int set_ship(char **matrix, int size, int y, int x, int direction, int ship_lenght);

#endif //SEMESTERAUFGABE_BATTLEGROUND_H
