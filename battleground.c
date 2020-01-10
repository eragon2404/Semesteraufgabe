#pragma clang diagnostic push
#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-narrowing-conversions"
#pragma ide diagnostic ignored "bugprone-branch-clone"
#include "battleground.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>






int init_battleground(char ***matrix, int size) /*Belegt den Speicher für die Matrize und setzt sie auf Anfangswerte*/
{
    int x;
    if ((*matrix = malloc(size * sizeof(char *))) == NULL) {
        return OUT_OF_MEMORY;
    }

    for (x = 0; x < size; x++) {
        if (((*(*matrix + x)) = malloc(size * sizeof(char))) == NULL) {
            /*TODO: Im Fehlerfall muss hier der reservierte Speicher gefreed werden!*/
            return OUT_OF_MEMORY;
        }
    }

    reset_battleground(*matrix, size);
    return 1;

}

int init_stats(int ***stats, int *ships, int ship_count)
{
    int ship_class_count, last, i, j;
    ship_class_count = last = 0;

    for (i = 0; i < ship_count; i++){
        if (last < ships[i]) {
            ship_class_count++;
            last = ships[i];
        }
    }

    if ((*stats = malloc(ship_class_count * sizeof(int*))) == NULL){
        return OUT_OF_MEMORY;
    }

    for (i = 0; i < ship_class_count; i++){
        if ((*(*stats + i) = malloc(2 * sizeof(int))) == NULL){
            free(*stats);
            return OUT_OF_MEMORY;
        }
    }

    set_ships_stats(*stats, ship_class_count, ships, ship_count);

    return ship_class_count;
}

void set_ships_stats(int **stats, int ship_class_count, int *ships, int ship_count)
{
    int last, i, j;
    last = j = 0;
    for (i = 0; i < ship_class_count; i++){
        for(j = j; j < ship_count; j++){
            if (last < ships[j]){
                last = stats[i][0] = ships[j];
                stats[i][1] = 0;
                break;
            }
        }
    }
}

void reset_battleground(char **matrix, int size) /*Setzt die Matrix zurueck*/
{
    int x, y;
    for (x = 0; x < size; x++) {
        for (y = 0; y < size; y++) {
            matrix[x][y] = 'w';
        }
    }
}

int rand_set_ships(char **matrix, int size, int *ships, int ship_count) /* Setzt die Schiffe zufaellig in die Matrix*/
{
    int i, j, done;
    done = 0;

    while (1) {
        for (i = 0; i < ship_count; i++) {

            for (j = 0; j < 1000; j++) {
                done = set_ship(matrix, size, rand() % size, rand() % size, rand() % 4, ships[i]);
                if (done) {
                    break;
                }
            }
            if (!done) {
                break;
            }

        }
        if (i == ship_count) {
            return 1;
        } else {
            reset_battleground(matrix, size);
        }
    }
}

int set_ship(char **matrix, int size, int y, int x, int direction, int ship_length) /*Setzt ein Schiff der Laenge ship_length nach den uebergebenen Koordinaten. Gibt 0 zurück falls nicht moeglich*/
{
    int i;

    if (matrix[y][x] != 'w') {
        return 0;
    }

    ship_length--;

    switch (direction) {
        case 0: /*Schiff soll nach oben gesetzt werden*/
            if ((y = y - ship_length) < 0) {
                return 0;
            }

            for (i = 0; i <= ship_length; i++) {
                if (matrix[y + i][x] != 'w') {
                    return 0;
                } else if (y + i + 1 < size && matrix[y + i + 1][x] != 'w') { /*Checkt, ob Index in erlaubtem Bereich und ob Feld belegt ist*/
                    return 0;
                } else if (y + i - 1 >= 0 && matrix[y + i - 1][x] != 'w') {
                    return 0;
                } else if (x - 1 >= 0 && matrix[y + i][x - 1] != 'w') {
                    return 0;
                } else if (x + 1 < size && matrix[y + i][x + 1] != 'w') {
                    return 0;
                }
            }

            for (i = 0; i <= ship_length; i++) {
                matrix[y + i][x] = '1' + ship_length;
            }
            break;

        case 1: /*Schiff soll nach rechts gesetzt werden*/
            if ((x = x + ship_length) > size - 1) {
                return 0;
            }

            for (i = 0; i <= ship_length; i++) {
                if (matrix[y][x - i] != 'w') {
                    return 0;
                } else if (y + 1 < size && matrix[y + 1][x - i] != 'w') { /*Checkt, ob Index in erlaubtem Bereich und ob Feld belegt ist*/
                    return 0;
                } else if (y - 1 >= 0 && matrix[y - 1][x - i] != 'w') {
                    return 0;
                } else if (x - i - 1 >= 0 && matrix[y][x - i - 1] != 'w') {
                    return 0;
                } else if (x - i + 1 < size && matrix[y][x - i + 1] != 'w') {
                    return 0;
                }
            }

            for (i = 0; i <= ship_length; i++) {
                matrix[y][x - i] = '1' + ship_length;
            }
            break;

        case 2: /*Schiff soll nach unten gesetzt werden*/
            if ((y = y + ship_length) > size - 1) {
                return 0;
            }

            for (i = 0; i <= ship_length; i++) {
                if (matrix[y - i][x] != 'w') {
                    return 0;
                } else if (y - i + 1 < size && matrix[y - i + 1][x] != 'w') { /*Checkt, ob Index in erlaubtem Bereich und ob Feld belegt ist*/
                    return 0;
                } else if (y - i - 1 >= 0 && matrix[y - i - 1][x] != 'w') {
                    return 0;
                } else if (x - 1 >= 0 && matrix[y - i][x - 1] != 'w') {
                    return 0;
                } else if (x + 1 < size && matrix[y - i][x + 1] != 'w') {
                    return 0;
                }
            }

            for (i = 0; i <= ship_length; i++) {
                matrix[y - i][x] = '1' + ship_length;
            }
            break;

        case 3: /*Schiff soll nach links gesetzt werden*/
            if ((x = x - ship_length) < 0) {
                return 0;
            }

            for (i = 0; i <= ship_length; i++) {
                if (matrix[y][x + i] != 'w') {
                    return 0;
                } else if (y + 1 < size && matrix[y + 1][x + i] != 'w') { /*Checkt, ob Index in erlaubtem Bereich und ob Feld belegt ist*/
                    return 0;
                } else if (y - 1 >= 0 && matrix[y - 1][x + i] != 'w') {
                    return 0;
                } else if (x + i - 1 >= 0 && matrix[y][x + i - 1] != 'w') {
                    return 0;
                } else if (x + i + 1 < size && matrix[y][x + i + 1] != 'w') {
                    return 0;
                }
            }

            for (i = 0; i <= ship_length; i++) {
                matrix[y][x + i] = '1' + ship_length;
            }
            break;

        default:
            return 0;
    }

    return 1;
}

int ship_mass_validation(int size, const int *ships, int ship_count) /*Stellt sicher, dass nicht zu viele Schiffen gesetzt werden*/
{
    int i;
    int mass;
    mass = 0;
    for (i = 0; i < ship_count; i++) {
        mass += ships[i];
    }
    mass *= 2;
    mass += ship_count;
    printf("%f", (float) mass / (float) (size * size));
    return ((float) mass / (float) (size * size) <= SHIP_MASS_THRESHOLD); /*das hier wird ein Bool*/
}

int shoot(char **matrix, int y, int x)
{
    int hit;
    if (isdigit(matrix[y][x])){
        hit = matrix[y][x] - '0';
        matrix[y][x] = 'X';
        return hit;
    } else if (matrix[y][x] == 'M' || matrix[y][x] == 'X'){
        printf("Diese Feld hatten sie schon. Schade!\n");
        return -1;
    } else {
        matrix[y][x] = 'M';
    }
    return 0;
}

int check_downed(char **matrix, int size, int y, int x)
{
    int count;
    count = 0;
    count += check_downed_helper(matrix, size, y - 1, x , -1, 0);
    count += check_downed_helper(matrix, size, y + 1, x , +1, 0);
    count += check_downed_helper(matrix, size, y, x - 1 , 0, -1);
    count += check_downed_helper(matrix, size, y, x + 1 , 0, +1);
    if(count > 0){
        return 0;
    }
    matrix[y][x] = 'D';
    downed_maker(matrix, size, y - 1, x, -1, 0);
    downed_maker(matrix, size, y + 1, x, +1, 0);
    downed_maker(matrix, size, y, x - 1, 0, -1);
    downed_maker(matrix, size, y, x + 1, 0, +1);
    return 1;
}

int check_downed_helper(char **matrix, int size, int y, int x, int dy, int dx)
{
    if (y < 0 || x < 0 || y >= size || x >= size){
        return 0;
    }
    if (matrix[y][x] == 'X'){
        return check_downed_helper(matrix, size, y + dy, x + dx, dy, dx);
    }
    if (isdigit(matrix[y][x])) {
        return 1;
    }
    return 0;
}

int downed_maker(char **matrix, int size, int y, int x, int dy, int dx)
{
    if (y < 0 || x < 0 || y >= size || x >= size){
        return 1;
    }
    if (matrix[y][x] != 'X'){
        return 1;
    }
    matrix[y][x] = 'D';
    downed_maker(matrix, size, y + dy, x + dx, dy, dx);
    return 1;
}

int is_end_game(char **matrix, int size)
{
    int x, y;
    for(x = 0; x < size; x++){
        for(y = 0; y < size; y++){
            if(isdigit(matrix[y][x])){
                return 0;
            }
        }
    }

    return 1;
}



int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}