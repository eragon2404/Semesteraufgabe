#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

#include "console.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
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
void draw_screen(char **matrix, int size)
{
        int x, y;

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
}

/*Zeichnet die uebergebene Matrize ohne Schiffe preiszugeben*/
void player_draw_screen(char **matrix, int size)
{
        int x, y;

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
                        if (isdigit(matrix[y][x])){
                                printf("w  ");
                        } else {
                                printf("%c  ", matrix[y][x]);
                        }
                }
                printf("\n");
        }
        printf("\n");
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
void clear_screen()
{
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
               "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

/*--------------------------------Alles rund um die Eingabe von Daten-------------------------------------------------*/

/*Laesst den Spieler seine Schiffe setzen*/
void player_set_ships(char **matrix, int size, int *ships, int ship_count, int player_turn)
{
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
                                        draw_screen(matrix, size);
                                        printf("Ist das so in Ordnung? (j / n)\n");
                                        do{
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
                draw_screen(matrix, size);
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
void get_settings(int *single, int *diff, int *standart)
{
        *single = *diff = *standart = -1;

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

        printf("Wuenschen sie die Standarteinstellungen mit Feldgroesse 10 und 5 Schiffen? (j / n)\n");
        do {
                switch (getchar()) {
                        case 'j':
                                *standart = 1;
                                if (getchar() != '\n') {
                                        flush();
                                }
                                return;
                        case 'n':
                                *standart = 0;
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
        } while (*standart == -1);
}

/*Fragt den Spiele nach der gewuenschten Feldgroesse*/
int get_battleground_size()
{
        int n;
        do {
                printf("Waehlen sie eine Feldgroesse: (min 10, max 20):\n");
                if (scanf("%i", &n) != 1) {
                        printf("Keine gueltige Eingabe!\n");
                        n = 0;
                        if (getchar() != '\n') {
                                flush();
                        }
                        continue;
                }
                if (n < 10 || n > 20) {
                        printf("Keine gueltige Eingabe!\n");
                        n = 0;
                } else {
                        return n;
                }
        } while (1);
}

/*Fragt den Spiele wie viele Schiffe welcher Art es geben soll*/
int get_ships(int **ships, int *ship_count, int size)
{
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
                        printf("Welche Groesse soll Schiff %i haben? (Min %i, Max %i)\n", i + 1, MIN_SHIP_LENGTH, MAX_SHIP_LENGTH);
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
int *player_move(char **matrix, int size, int player_turn) {
        int x, y;
        static int result[2];

        clear_screen();
        printf("Spieler %i ist am Zug:\n", player_turn + 1);
        if (SHOW_FULL_BATTLEGROUND){
                draw_screen(matrix, size);
        } else {
                player_draw_screen(matrix, size);
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
void show_player_battleground(char **matrix, int size, int player_turn)
{
        printf("Spieler %i ist am Zug! Im naechsten Schritt wird ihr eigenes Spielfeld angezeigt!\n", player_turn + 1);
        printf("WEITER (enter)");
        if (getchar() != '\n') {
                flush();
        }
        printf("Das ist ihr momentanes Spielfeld:\n");

        draw_screen(matrix, size);

        printf("\nWEITER (enter)");
        if (getchar() != '\n') {
                flush();
        }
        printf("\n\n");
}

/*Antwort auf einen Spielzug*/
int response(char **matrix, int size, int *shot, int hit, int downed, int player) {
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
        if (SHOW_FULL_BATTLEGROUND){
                draw_screen(matrix, size);
        } else {
                player_draw_screen(matrix, size);
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