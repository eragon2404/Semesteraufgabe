#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
#include "battleground.h"
#include <stdio.h>
#include <stdlib.h>






int init_battleground(char ***matrix, int size) /*Belegt den Speicher für die Matrize und setzt sie auf Anfangswerte*/
{
    int x;
    if ((*matrix = malloc(size * sizeof(char *))) == NULL) {
        return OUT_OF_MEMORY;
    }

    for (x = 0; x < size; x++) {
        if (((*(*matrix + x)) = malloc(size)) == NULL) {
            return OUT_OF_MEMORY;
        }
    }

    reset_battleground(*matrix, size);
    return 1;

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