#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

#include "console.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*---------------------------------Methoden die das Spiel zeichnen----------------------------------------------------*/

void draw_intro() {
        setbuf(stdout, 0);
        printf("--------------------------------------------------------------------------------\n"
               "                            Schiffe Versenken Deluxe                            \n"
               "--------------------------------------------------------------------------------\n"
               "--------------------------------------------------------------------------------\n");
}

/*Zeichnet die uebergebene Matrize*/
void draw_screen(char **matrix, int size, tiles *t) {
        int x, y, i;
        if (!SHOW_ASCII_ART) {

                printf("\t");
                for (x = 0; x < size; x++) {
                        if (x < 9) {
                                printf("%i  ", x + 1);
                        } else {
                                printf("%i ", x + 1);
                        }

                }
                printf("\n");

                for (y = 0; y < size; y++) {
                        printf("%i:\t", y + 1);
                        for (x = 0; x < size; x++) {
                                printf("%c  ", matrix[y][x]);
                        }
                        printf("\n");
                }
                printf("\n");
        } else {

                printf("\t");
                for (i = 0; i < size - 1; i++) {
                        if (i < 10) {
                                printf("  %i   ", i + 1);
                        } else {
                                printf(" %i   ", i + 1);
                        }
                }
                printf(" %i\n", size);

                for (y = 0; y < size; y++) {
                        printf("%i:\t", y + 1);
                        for (i = 0; i < 2; i++) {
                                if (i) {
                                        printf("|______ ");
                                }
                                for (x = 0; x < size; x++) {
                                        switch (matrix[y][x]) {
                                                case 'w':
                                                        printf("%s", t->water[i]);
                                                        break;

                                                case 'D':
                                                        switch (check_tile_orientation(matrix, size, x, y)) {
                                                                case 0:
                                                                        printf("%s", t->dwn_front_vert[i]);
                                                                        break;

                                                                case 1:
                                                                        printf("%s", t->dwn_mid_vert[i]);
                                                                        break;

                                                                case 2:
                                                                        printf("%s", t->dwn_end_vert[i]);
                                                                        break;

                                                                case 3:
                                                                        printf("%s", t->dwn_front_hor[i]);
                                                                        break;

                                                                case 4:
                                                                        printf("%s", t->dwn_mid_hor[i]);
                                                                        break;

                                                                case 5:
                                                                        printf("%s", t->dwn_end_hor[i]);
                                                                        break;
                                                        }
                                                        break;

                                                case 'X':
                                                        printf("%s", t->hit[i]);
                                                        break;

                                                case 'M':
                                                        printf("%s", t->miss[i]);
                                                        break;

                                                default:
                                                        switch (check_tile_orientation(matrix, size, x, y)) {
                                                                case 0:
                                                                        printf("%s", t->front_vert[i]);
                                                                        break;

                                                                case 1:
                                                                        printf("%s", t->mid_vert[i]);
                                                                        break;

                                                                case 2:
                                                                        printf("%s", t->end_vert[i]);
                                                                        break;

                                                                case 3:
                                                                        printf("%s", t->front_hor[i]);
                                                                        break;

                                                                case 4:
                                                                        printf("%s", t->mid_hor[i]);
                                                                        break;

                                                                case 5:
                                                                        printf("%s", t->end_hor[i]);
                                                                        break;
                                                        }
                                        }
                                }

                                printf("\n");
                        }
                }
                printf("\n");
        }
}

/*Zeichnet die uebergebene Matrize ohne Schiffe preiszugeben*/
void player_draw_screen(char **matrix, int size, tiles *t) {
        int x, y, i;

        if (!SHOW_ASCII_ART) {
                printf("\t");
                for (x = 0; x < size; x++) {
                        if (x < 9) {
                                printf("%i  ", x + 1);
                        } else {
                                printf("%i ", x + 1);
                        }

                }
                printf("\n");

                for (y = 0; y < size; y++) {
                        printf("%i:\t", y + 1);
                        for (x = 0; x < size; x++) {
                                if (isdigit(matrix[y][x])) {
                                        printf("w  ");
                                } else {
                                        printf("%c  ", matrix[y][x]);
                                }
                        }
                        printf("\n");
                }
                printf("\n");
        } else {
                printf("\t");
                for (i = 0; i < size - 1; i++) {
                        if (i < 10) {
                                printf("  %i   ", i + 1);
                        } else {
                                printf(" %i   ", i + 1);
                        }
                }
                printf(" %i\n", size);

                for (y = 0; y < size; y++) {
                        printf("%i:\t", y + 1);
                        for (i = 0; i < 2; i++) {
                                if (i) {
                                        printf("|______ ");
                                }
                                for (x = 0; x < size; x++) {
                                        switch (matrix[y][x]) {
                                                case 'D':
                                                        switch (check_tile_orientation(matrix, size, x, y)) {
                                                                case 0:
                                                                        printf("%s", t->dwn_front_vert[i]);
                                                                        break;

                                                                case 1:
                                                                        printf("%s", t->dwn_mid_vert[i]);
                                                                        break;

                                                                case 2:
                                                                        printf("%s", t->dwn_end_vert[i]);
                                                                        break;

                                                                case 3:
                                                                        printf("%s", t->dwn_front_hor[i]);
                                                                        break;

                                                                case 4:
                                                                        printf("%s", t->dwn_mid_hor[i]);
                                                                        break;

                                                                case 5:
                                                                        printf("%s", t->dwn_end_hor[i]);
                                                                        break;
                                                        }
                                                        break;

                                                case 'X':
                                                        printf("%s", t->hit[i]);
                                                        break;

                                                case 'M':
                                                        printf("%s", t->miss[i]);
                                                        break;

                                                default:
                                                        printf("%s", t->water[i]);
                                                        break;
                                        }


                                }

                                printf("\n");
                        }
                }
                printf("\n");
        }

}

int check_tile_orientation(char **matrix, int size, int x, int y) {
        unsigned short status = 0;

        if (y - 1 < 0 || (y - 1 >= 0 && (matrix[y - 1][x] == 'w' || matrix[y - 1][x] == 'M'))) {
                status = status + 1;
        }

        status = status << 1;
        if (x + 1 >= size || (x + 1 < size && (matrix[y][x + 1] == 'w' || matrix[y][x + 1] == 'M'))) {

                status = status + 1;
        }

        status = status << 1;
        if (y + 1 >= size || (y + 1 < size && (matrix[y + 1][x] == 'w' || matrix[y + 1][x] == 'M'))) {

                status = status + 1;
        }

        status = status << 1;
        if (x - 1 < 0 || (x - 1 >= 0 && (matrix[y][x - 1] == 'w' || matrix[y][x - 1] == 'M'))) {

                status = status + 1;
        }

        switch (status) {
                case 13:
                        return 0;

                case 5:
                        return 1;

                case 7:
                        return 2;

                case 11:
                        return 3;

                case 10:
                        return 4;

                case 14:
                        return 5;

                default:
                        return -1;
        }
}

/*Bereitet das Struct mit den Tiles vor*/
void set_tiles(tiles *t) {
        strcpy(t->front_vert[0], "~~/\\~~");
        strcpy(t->front_vert[1], "~/__\\~");

        strcpy(t->mid_vert[0], "~|  |~");
        strcpy(t->mid_vert[1], "~|__|~");

        strcpy(t->end_vert[0], "~|__|~");
        strcpy(t->end_vert[1], "~\\__/~");

        strcpy(t->front_hor[0], " _____");
        strcpy(t->front_hor[1], "\\_o_o_");

        strcpy(t->mid_hor[0], "______");
        strcpy(t->mid_hor[1], "o_o_o_");

        strcpy(t->end_hor[0], "__[^]_");
        strcpy(t->end_hor[1], "o_o_o/");

        strcpy(t->dwn_front_vert[0], "~~X\\~~");
        strcpy(t->dwn_front_vert[1], "~/_X\\~");

        strcpy(t->dwn_mid_vert[0], "~| X|~");
        strcpy(t->dwn_mid_vert[1], "~|X_|~");

        strcpy(t->dwn_end_vert[0], "~|X_|~");
        strcpy(t->dwn_end_vert[1], "~\\_X/~");

        strcpy(t->dwn_front_hor[0], " _____");
        strcpy(t->dwn_front_hor[1], "\\_x_x_");

        strcpy(t->dwn_mid_hor[0], "______");
        strcpy(t->dwn_mid_hor[1], "x_x_x_");

        strcpy(t->dwn_end_hor[0], "__[^]_");
        strcpy(t->dwn_end_hor[1], "x_x_x/");

        strcpy(t->hit[0], " \\  / ");
        strcpy(t->hit[1], " /  \\ ");

        strcpy(t->miss[0], " oOoO ");
        strcpy(t->miss[1], " OoOo ");

        strcpy(t->water[0], " ~~~~ ");
        strcpy(t->water[1], " ~~~~ ");

        strcpy(t->downed[0], "__[x]_");
        strcpy(t->downed[1], "x_x_x/");

}

/*Gibt die Statistiken aus*/
void print_stats(int **stats1, int **stats2, int ship_class_count) {
        int i;
        printf("\nSpieler 1 hat folgende Schiffsklassen versenkt / nicht versenkte Schiffe getroffen:\n");
        for (i = 0; i < ship_class_count - 1; i++) {
                printf("%i Felder lange Schiffe: %i / %i || ", stats1[i][0], stats1[i][1] / stats1[i][0],
                       stats1[i][1] % stats1[i][0]);
        }
        printf("%i Felder lange Schiffe: %i / %i\n\n", stats1[ship_class_count - 1][0],
               stats1[ship_class_count - 1][1] / stats1[ship_class_count - 1][0],
               stats1[ship_class_count - 1][1] % stats1[ship_class_count - 1][0]);

        printf("\nSpieler 2 hat folgende Schiffsklassen versenkt / nicht versenkte Schiffe getroffen:\n");
        for (i = 0; i < ship_class_count - 1; i++) {
                printf("%i Felder lange Schiffe: %i / %i || ", stats2[i][0], stats2[i][1] / stats2[i][0],
                       stats2[i][1] % stats2[i][0]);
        }
        printf("%i Felder lange Schiffe: %i / %i\n\n", stats2[ship_class_count - 1][0],
               stats2[ship_class_count - 1][1] / stats2[ship_class_count - 1][0],
               stats2[ship_class_count - 1][1] % stats2[ship_class_count - 1][0]);
}

/*Ein wunderschoener Weg um den Screen sauber zu bekommen*/
void clear_screen() {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
               "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

/*--------------------------------Alles rund um die Eingabe von Daten-------------------------------------------------*/

/*Laesst den Spieler seine Schiffe setzen*/
void player_set_ships(char **matrix, int size, int *ships, int ship_count, int player_turn, tiles *t) {
        int i, current_ship, x, y, direction;
        i = 1;
        current_ship = 0;
        direction = 0;

        printf("Spieler %i muss nun seine Schiffe setzen!\n", player_turn + 1);
        printf("Moechten sie die Schiffe zufaellig setzen lassen? (j / n)\n");
        do {
                switch (getchar()) {
                        case 'j':
                                rand_set_ships(matrix, size, ships, ship_count);
                                if (getchar() != '\n') {
                                        flush();
                                }

                                do { /*Wiederholt das zufaellige Setzen solange, bis der Spieler zufrieden ist*/
                                        clear_screen();
                                        draw_screen(matrix, size, t);
                                        printf("Ist das so in Ordnung? (j / n)\n");
                                        do {
                                                switch (getchar()) {
                                                        case 'j':
                                                                if (getchar() != '\n') {
                                                                        flush();
                                                                }
                                                                return;
                                                        case 'n':
                                                                reset_battleground(matrix, size);
                                                                rand_set_ships(matrix, size, ships, ship_count);
                                                                if (getchar() != '\n') {
                                                                        flush();
                                                                }
                                                                i = 0;
                                                                break;
                                                        case '\n':
                                                                printf("Keine gueltige Antwort, erneut versuchen!\n");
                                                                break;
                                                        default:
                                                                printf("Keine gueltige Antwort, erneut versuchen!\n");
                                                                if (getchar() != '\n') {
                                                                        flush();
                                                                }
                                                                break;
                                                }
                                        } while (i);

                                } while (1);

                        case 'n':
                                if (getchar() != '\n') {
                                        flush();
                                }
                                i = 0;
                                break;
                        case '\n':
                                printf("Keine gueltige Antwort, erneut versuchen!\n");
                                break;
                        default:
                                printf("Keine gueltige Antwort, erneut versuchen!\n");
                                if (getchar() != '\n') {
                                        flush();
                                }
                                break;

                }
        } while (i);

        while (current_ship < ship_count) {

                clear_screen();
                draw_screen(matrix, size, t);
                printf("Es stehen folgende Schiffe zur Auswahl (Die Zahl gibt die Laenge an):\n");
                for (i = 0; i < ship_count - 1; i++) {
                        printf("%i ", ships[i]);
                }
                printf("%i\n", ships[ship_count - 1]);

                printf("Wohin soll das Schiff %i (von %i) mit Laenge %i? (Eingabe: \"x.y.richtung\" (oben = 0, rechts = 1, unten = 2, links = 3))\n",
                       current_ship + 1, ship_count, ships[current_ship]);
                do {
                        if (scanf("%i.%i.%i", &x, &y, &direction) != 3) {
                                printf("Ungueltige Eingabe! (Format: x.y.richtung)\n");
                                if (getchar() != '\n') {
                                        flush();
                                }
                                continue;
                        }
                        if (x - 1 < 0 || y - 1 < 0 || x > size || y > size) {
                                printf("Ungueltige Koordinate! (Format: x.y.richtung)\n");
                                if (getchar() != '\n') {
                                        flush();
                                }
                                continue;
                        }
                        if (direction < 0 || direction > 3) {
                                printf("Ungueltige Richtungsangabe! (oben = 0, rechts = 1, unten = 2, links = 3)\n");
                                if (getchar() != '\n') {
                                        flush();
                                }
                                continue;
                        }

                        if (getchar() != '\n') {
                                flush();
                        }

                        if (!set_ship(matrix, size, y - 1, x - 1, direction, ships[current_ship])) {
                                printf("Diese Position ist leider nicht moeglich!\n");
                                continue;
                        }
                        break;
                } while (1);

                current_ship++;
        }
}

/*Fragt Spieler nach den Spieleinstellungen*/
void get_settings(int *single, int *diff, int *standard) {
        *single = *diff = *standard = -1;

        printf("Moechten sie allein oder zu zweit spielen? (1 / 2)\n");
        do {
                switch (getchar()) {
                        case '1':
                                *single = 1;
                                if (getchar() != '\n') {
                                        flush();
                                }
                                break;
                        case '2':
                                *single = 0;
                                if (getchar() != '\n') {
                                        flush();
                                }
                                break;
                        case '\n':
                                printf("Keine gueltige Antwort, erneut versuchen!\n");
                                break;
                        default:
                                printf("Keine gueltige Antwort, erneut versuchen!\n");
                                if (getchar() != '\n') {
                                        flush();
                                }
                                break;

                }
        } while (*single == -1);

        if (*single) {
                printf("Welchen Schwierigkeitsgrad des Computers wuenschen sie? (1, 2, 3)\n");
                do {
                        switch (getchar()) {
                                case '1':
                                        *diff = 1;
                                        if (getchar() != '\n') {
                                                flush();
                                        }
                                        break;
                                case '2':
                                        *diff = 2;
                                        if (getchar() != '\n') {
                                                flush();
                                        }
                                        break;
                                case '3':
                                        *diff = 3;
                                        if (getchar() != '\n') {
                                                flush();
                                        }
                                        break;
                                case '\n':
                                        printf("Keine gueltige Antwort, erneut versuchen!\n");
                                        break;
                                default:
                                        printf("Keine gueltige Antwort, erneut versuchen!\n");
                                        if (getchar() != '\n') {
                                                flush();
                                        }
                                        break;

                        }
                } while (*diff == -1);
        }

        printf("Wuenschen sie die Standardeinstellungen mit Feldgroesse 10 und 5 Schiffen? (j / n)\n");
        do {
                switch (getchar()) {
                        case 'j':
                                *standard = 1;
                                if (getchar() != '\n') {
                                        flush();
                                }
                                return;
                        case 'n':
                                *standard = 0;
                                if (getchar() != '\n') {
                                        flush();
                                }
                                break;
                        case '\n':
                                printf("Keine gueltige Antwort, erneut versuchen!\n");
                                break;
                        default:
                                printf("Keine gueltige Antwort, erneut versuchen!\n");
                                if (getchar() != '\n') {
                                        flush();
                                }
                                break;
                }
        } while (*standard == -1);
}

/*Fragt den Spiele nach der gewuenschten Feldgroesse*/
int get_battleground_size() {
        int n;
        do {
                printf("Waehlen sie eine Feldgroesse: (min %i, max %i):\n", MIN_BATTLEGROUND_SIZE,
                       MAX_BATTLEGROUND_SIZE);
                if (scanf("%i", &n) != 1) {
                        printf("Keine gueltige Eingabe!\n");
                        n = 0;
                        if (getchar() != '\n') {
                                flush();
                        }
                        continue;
                }
                if (n < MIN_BATTLEGROUND_SIZE || n > MAX_BATTLEGROUND_SIZE) {
                        printf("Keine gueltige Eingabe!\n");
                        n = 0;
                } else {
                        return n;
                }
        } while (1);
}

/*Fragt den Spiele wie viele Schiffe welcher Art es geben soll*/
int get_ships(int **ships, int *ship_count, int size) {
        int length, i;
        do {
                printf("Wie viele Schiffe soll es geben? (Min 1, Max %i)\n", SHIPS_LIMIT);
                do {
                        printf("Eingabe:\n");
                        if (scanf("%i", ship_count) != 1) {
                                printf("Keine gueltige Eingabe!\n");
                                if (getchar() != '\n') {
                                        flush();
                                }
                                continue;
                        }
                        if (!(*ship_count < 1 || *ship_count > SHIPS_LIMIT)) {
                                break;
                        }
                } while (1);

                if (getchar() != '\n') {
                        flush();
                }

                if ((*ships = malloc(*ship_count * sizeof(int))) == NULL) {
                        return OUT_OF_MEMORY;
                }

                for (i = 0; i < *ship_count; i++) {
                        printf("Welche Groesse soll Schiff %i haben? (Min %i, Max %i)\n", i + 1, MIN_SHIP_LENGTH,
                               MAX_SHIP_LENGTH);
                        do {
                                printf("Eingabe:\n");
                                if (scanf("%i", &length) != 1) {
                                        printf("Keine gueltige Eingabe!\n");
                                        if (getchar() != '\n') {
                                                flush();
                                        }
                                        continue;
                                }
                                if (length < MIN_SHIP_LENGTH || length > MAX_SHIP_LENGTH) {
                                        printf("Keine gueltige Eingabe!\n");
                                        if (getchar() != '\n') {
                                                flush();
                                        }
                                } else {
                                        break;
                                }
                        } while (1);

                        *(*ships + i) = length;
                }
        } while (!ship_mass_validation(size, *ships, *ship_count));
        if (getchar() != '\n') {
                flush();
        }
        return 1;
}

/*Fragt den Spieler wohin er schiessen moechte*/
int *player_move(char **matrix, int size, int player_turn, tiles *t) {
        int x, y;
        static int result[2];

        clear_screen();
        printf("Spieler %i ist am Zug:\n", player_turn + 1);
        if (SHOW_FULL_BATTLEGROUND) {
                draw_screen(matrix, size, t);
        } else {
                player_draw_screen(matrix, size, t);
        }
        printf("Wohin moechten sie schiessen? (Format: x.y)\n");

        do {
                if (scanf("%i.%i", &x, &y) != 2) {
                        printf("Ungueltige Eingabe! (Format: x.y)\n");
                        if (getchar() != '\n') {
                                flush();
                        }
                } else if (x < 1 || x > size || y < 1 || y > size) {
                        printf("Ungueltige Koordinate! (Format: x.y)\n");
                } else {
                        break;
                }
        } while (1);

        if (getchar() != '\n') {
                flush();
        }

        x--;
        y--;

        result[1] = x;
        result[0] = y;

        return result;
}

/*Zeigt dem Spieler seinen eigenes Spielfeld*/
void show_player_battleground(char **matrix, int size, int player_turn, tiles *t) {
        printf("Spieler %i ist am Zug! Im naechsten Schritt wird ihr eigenes Spielfeld angezeigt!\n", player_turn + 1);
        printf("WEITER (enter)");
        if (getchar() != '\n') {
                flush();
        }
        printf("Das ist ihr momentanes Spielfeld:\n");

        draw_screen(matrix, size, t);

        printf("\nWEITER (enter)");
        if (getchar() != '\n') {
                flush();
        }
        printf("\n\n");
}

/*Antwort auf einen Spielzug*/
int response(char **matrix, int size, int *shot, int hit, int downed, int player, tiles *t) {
        clear_screen();
        printf("Spieler %i hat auf %i.%i geschossen!\n", player + 1, shot[1] + 1, shot[0] + 1);
        switch (hit) {
                case -1:
                        printf("Auf dieses Feld wurde aber bereits geschossen.\n");
                        break;
                case 0:
                        printf("Ein Schuss ins Wasser.\n");
                        break;
                default:
                        printf("TREFFER\n");
                        break;
        }
        if (downed) {
                printf("VERSENKT\n");
        }
        printf("\n");
        if (SHOW_FULL_BATTLEGROUND) {
                draw_screen(matrix, size, t);
        } else {
                player_draw_screen(matrix, size, t);
        }

        printf("\nWEITER (enter)");
        if (getchar() != '\n') {
                flush();
        }
        clear_screen();
        return 1;
}

/*Leert den Eingabepuffer*/
void flush() {
        while (getchar() != '\n');
}