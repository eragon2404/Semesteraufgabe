#pragma clang diagnostic push
#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-narrowing-conversions"
#pragma ide diagnostic ignored "bugprone-branch-clone"

#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*Belegt den Speicher fuer die Matrize und setzt sie auf Anfangswerte*/
int init_battleground(char ***matrix, int size) {
        int x;
        if ((*matrix = malloc(size * sizeof(char *))) == NULL) {
                return OUT_OF_MEMORY;
        }

        for (x = 0; x < size; x++) {
                if (((*(*matrix + x)) = malloc(size * sizeof(char))) == NULL) {
                        x--;
                        while (x <= 0) {
                                free((*(*matrix + x)));
                                x--;
                        }
                        free(*matrix);
                        return OUT_OF_MEMORY;
                }
        }

        reset_battleground(*matrix, size);
        return 1;

}

/*Initalisiert eine Matrix zum Verfolgen der Treffer auf die vorhandenen Schiffstypen*/
int init_stats(int ***stats1, int ***stats2, const int *ships, int ship_count) {
        int ship_class_count, last, i;
        ship_class_count = last = 0;

        for (i = 0; i < ship_count; i++) {
                if (last < ships[i]) {
                        ship_class_count++;
                        last = ships[i];
                }
        }

        if ((*stats1 = malloc(ship_class_count * sizeof(int *))) == NULL) {
                return OUT_OF_MEMORY;
        }

        if ((*stats2 = malloc(ship_class_count * sizeof(int *))) == NULL) {
                free(stats1);
                return OUT_OF_MEMORY;
        }

        for (i = 0; i < ship_class_count; i++) {
                if ((*(*stats1 + i) = malloc(2 * sizeof(int))) == NULL) {
                        i--;
                        while (i <= 0) {
                                free((*(*stats1 + i)));
                                i--;
                        }
                        free(*stats1);
                        return OUT_OF_MEMORY;
                }
        }

        for (i = 0; i < ship_class_count; i++) {
                if ((*(*stats2 + i) = malloc(2 * sizeof(int))) == NULL) {
                        i--;

                        while (i <= 0) {
                                free((*(*stats2 + i)));
                                i--;
                        }

                        for (i = 0; i < ship_class_count; i++) {
                                free((*(*stats1 + i)));
                        }

                        free(*stats1);
                        free(*stats2);
                        return OUT_OF_MEMORY;
                }
        }

        set_ships_stats(*stats1, ship_class_count, ships, ship_count);
        set_ships_stats(*stats2, ship_class_count, ships, ship_count);
        return ship_class_count;
}

/*Initalisiert den Speicher fuer die Stats*/
void set_ships_stats(int **stats, int ship_class_count, const int *ships, int ship_count) {
        int last, i, j;
        last = j = 0;
        for (i = 0; i < ship_class_count; i++) {
                for (; j < ship_count; j++) {
                        if (last < ships[j]) {
                                last = stats[i][0] = ships[j];
                                stats[i][1] = 0;
                                break;
                        }
                }
        }
}

/*Aktualisiert die Stats abhaengig von der getroffenen Schiffsklasse*/
void updateStats(int **stats, int ship_class_count, int hit) {
        int i;
        for (i = 0; i < ship_class_count; i++) {
                if (stats[i][0] == hit) {
                        stats[i][1]++;
                }
        }
}

/*Setzt die Matrix zurueck*/
void reset_battleground(char **matrix, int size) {
        int x, y;
        for (x = 0; x < size; x++) {
                for (y = 0; y < size; y++) {
                        matrix[x][y] = 'w';
                }
        }
}

/*Setzt die Schiffe zufaellig in die Matrix*/
int rand_set_ships(char **matrix, int size, int *ships, int ship_count) {
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

/*Setzt ein Schiff der Laenge ship_length nach den uebergebenen Koordinaten. Gibt 0 zurueck falls nicht moeglich*/
int set_ship(char **matrix, int size, int y, int x, int direction, int ship_length) {
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
                                        /*Checkt, ob Index in erlaubtem Bereich und ob Feld belegt ist*/
                                } else if (y + i + 1 < size && matrix[y + i + 1][x] != 'w') {
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
                                        /*Checkt, ob Index in erlaubtem Bereich und ob Feld belegt ist*/
                                } else if (y + 1 < size && matrix[y + 1][x - i] != 'w') {
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
                                        /*Checkt, ob Index in erlaubtem Bereich und ob Feld belegt ist*/
                                } else if (y - i + 1 < size && matrix[y - i + 1][x] != 'w') {
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
                                        /*Checkt, ob Index in erlaubtem Bereich und ob Feld belegt ist*/
                                } else if (y + 1 < size && matrix[y + 1][x + i] != 'w') {
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

/*Stellt sicher, dass nicht zu viele Schiffen gesetzt werden*/
int ship_mass_validation(int size, const int *ships, int ship_count) {
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

/*Schiesst das Feld an den uebergebenen Koordinaten und gibt zurueck, welche Schiffsklasse getroffen wurde*/
int shoot(char **matrix, int y, int x) {
        int hit;
        if (isdigit(matrix[y][x])) {
                hit = matrix[y][x] - '0';
                matrix[y][x] = 'X';
                return hit;
        } else if (matrix[y][x] == 'M' || matrix[y][x] == 'X' || matrix[y][x] == 'D') {
                printf("Diese Feld hatten sie schon. Schade!\n");
                return -1;
        } else {
                matrix[y][x] = 'M';
        }
        return 0;
}

/*Prueft, ob ein Schiff versenkt wurde und setzt falls dies der Fall ist das Schiff auf 'D'*/
int check_downed(char **matrix, int size, int y, int x) {
        int count;
        count = 0;
        count += check_downed_helper(matrix, size, y - 1, x, -1, 0);
        count += check_downed_helper(matrix, size, y + 1, x, +1, 0);
        count += check_downed_helper(matrix, size, y, x - 1, 0, -1);
        count += check_downed_helper(matrix, size, y, x + 1, 0, +1);
        if (count > 0) {
                return 0;
        }
        matrix[y][x] = 'D';
        downed_maker(matrix, size, y - 1, x, -1, 0);
        downed_maker(matrix, size, y + 1, x, +1, 0);
        downed_maker(matrix, size, y, x - 1, 0, -1);
        downed_maker(matrix, size, y, x + 1, 0, +1);
        return 1;
}

/*Hilfsfunktion zu check_downed*/
int check_downed_helper(char **matrix, int size, int y, int x, int dy, int dx) {
        if (y < 0 || x < 0 || y >= size || x >= size) {
                return 0;
        }
        if (matrix[y][x] == 'X') {
                return check_downed_helper(matrix, size, y + dy, x + dx, dy, dx);
        }
        if (isdigit(matrix[y][x])) {
                return 1;
        }
        return 0;
}

int downed_maker(char **matrix, int size, int y, int x, int dy, int dx) {
        if (y < 0 || x < 0 || y >= size || x >= size) {
                return 1;
        }
        if (matrix[y][x] != 'X') {
                return 1;
        }
        matrix[y][x] = 'D';
        downed_maker(matrix, size, y + dy, x + dx, dy, dx);
        return 1;
}

/*Prueft ob das Spiel zuende ist*/
int is_end_game(char **matrix, int size) {
        int x, y;
        for (x = 0; x < size; x++) {
                for (y = 0; y < size; y++) {
                        if (isdigit(matrix[y][x])) {
                                return 0;
                        }
                }
        }

        return 1;
}

/*Vergleichsfunktion fuer qsort (vgl. http://www.cplusplus.com/reference/cstdlib/qsort/)*/
int compare(const void *a, const void *b) {
        return (*(int *) a - *(int *) b);
}