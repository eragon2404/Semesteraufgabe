#include "ki.h"
#include "battleground.h"
#include <stdlib.h>


int * get_ai_turn(char **battleground, int size, int difficulty)
{
    switch (difficulty) {
        case 1:
            return NULL;
        case 2:
            return NULL;
        case 3:
            return ai_diff3(battleground, size);
        default:
            return 0;
    }
}

int * ai_diff3(char **matrix, int size)
{

    static int result[2];

    int iy;
    int ix;

    int count_useful;
    int count_hit;

    int first_hit[2];
    int last_hit[2];

    int random_num;
    int in;

    int vector[2];

    count_useful = 0;
    count_hit = 0;

    /*Matrix analysieren*/
    for (iy = 0; iy < size; iy++){
        for (ix = 0; ix < size; ix++){
            if ((*matrix + iy*size)[ix] == 'h'){
                if (count_hit == 0){
                    first_hit[0] = iy;
                    first_hit[1] = ix;
                } else {
                    last_hit[0] = iy;
                    last_hit[1] = ix;
                }
                count_hit++;
            } else if (is_useful(matrix, iy, ix, size, 3) == 1) {
                count_useful++;
            }
        }
    }
    /* Kein getroffenes Schiff -> Zufaelliges Feld im Muster nehmen */
    if (count_hit == 0){
        random_num = rand() % count_hit;
        in = 0;
        for (iy = 0; iy < size; iy++) {
            for (ix = 0; ix < size; ix++) {
                if (is_useful(matrix, iy, ix, size, 3) == 1) {
                    if (in == random_num) {
                        result[0] = iy;
                        result[1] = ix;
                        return result;
                    }
                }
            }
        }
        /* Ein getroffenes Schiff - Feld -> sinvolles anliegendes Feld nehmen */
    } else if (count_hit == 1){
        if (is_useful(matrix, first_hit[0] + 1, first_hit[1] + 0, size, 2)) {
            result[0] = first_hit[0] + 1;
            result[1] = first_hit[1] + 0;
        } else if (is_useful(matrix, first_hit[0] - 1, first_hit[1] + 0, size, 2)) {
            result[0] = first_hit[0] - 1;
            result[1] = first_hit[1] + 0;
        } else if (is_useful(matrix, first_hit[0] + 0, first_hit[1] + 1, size, 2)) {
            result[0] = first_hit[0] + 0;
            result[1] = first_hit[1] + 1;
        } else if (is_useful(matrix, first_hit[0] + 0, first_hit[1] - 1, size, 2)) {
            result[0] = first_hit[0] + 0;
            result[1] = first_hit[1] - 1;
        }
        return result;

        /* Zwei getroffenes Schiff - Felder -> sinvolles ende des Schiifs nehmen */
    } else if (count_hit > 1){
        vector[0] = last_hit[0] - first_hit[0];
        vector[1] = last_hit[1] - first_hit[1];

        if (vector[0] != 0) {
            vector[0] /= abs(vector[0]);
        }
        if (vector[1] != 0) {
            vector[1] /= abs(vector[1]);
        }

        result[0] = last_hit[0] + vector[0];
        result[1] = last_hit[1] + vector[1];

        if (is_useful(matrix, result[0], result[1], size, 2)) {
            return result;
        } else {
            result[0] = first_hit[0] - vector[0];
            result[1] = first_hit[1] - vector[1];
            return result;
        }
    }
    return NULL;
}

int is_useful(char **matrix, int y, int x, int size, int difficulty)
{
    if (y < 0 || y >= size || x < 0 || x >= size) {
        return 0;
    }
    if (!((*matrix + y*size)[x] == 'u' || (*matrix + y*size)[x] == 'w'))  {
        return 0;
    }
    if (difficulty >= 2) {
        if (y+1 < size) {
            if ((*matrix + (y + 1)*size)[(x + 0)] == 'd') {
                return 0;
            }
        }
        if (y-1 >= 0) {
            if ((*matrix + (y - 1)*size)[(x + 0)] == 'd') {
                return 0;
            }
        }
        if (x+1 < size) {
            if ((*matrix + (y + 0)*size)[(x + 1)] == 'd') {
                return 0;
            }
        }
        if (x-1 >= 0) {
            if ((*matrix + (y + 0)*size)[(x - 1)] == 'd') {
                return 0;
            }
        }
    }
    if (difficulty >= 3) {
        if ((y + 1) % 2 != (x + 1) % 2){
            return 0;
        }
    }
    return 1;
}



