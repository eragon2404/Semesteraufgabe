/*TODO: Spiel fertig machen*/

#include <stdio.h>
#include <stdlib.h>

#include "logic.h"
#include "glorifiedifstatements(ai).h"
#include "console.h"

#include <time.h>

#ifndef OUT_OF_MEMORY
#define OUT_OF_MEMORY (-69420)
#endif

int main(void) {

        int i, player_turn, win, *shot, hit, downed, first; /*Hilfsvariablen*/
        int size, *ships, ship_count, single, diff, standart; /*Settings*/
        int **stats0, **stats1, ship_class_count; /*Statistikspeicher*/

        char **battleground0 /*Matrize Spieler 0*/, **battleground1; /*Matrize Spieler 1*/

        srand(time(NULL));
        battleground0 = NULL;
        battleground1 = NULL;
        ships = NULL;

        player_turn = win = 0;
        first = 1;
        draw_intro();
        get_settings(&single, &diff, &standart);
        clear_screen();

        if (standart) { /*Setzt Standartwerte für ein Standartspiel*/
                size = 10;
                ship_count = 5;
                if ((ships = malloc(ship_count * sizeof(int))) == NULL) {
                        printf("Out of memory, abort!");
                        return -1;
                }

                ships[0] = 2;
                ships[1] = 2;
                ships[2] = 3;
                ships[3] = 4;
                ships[4] = 5;

                if ((ship_class_count = init_stats(&stats0, &stats1, ships, ship_count)) == OUT_OF_MEMORY) {
                        free(ships);
                        printf("Out of memory, abort!");
                        return -1;
                }

        } else { /*Spiel mit benutzerdefinierten Werten*/

                size = get_battleground_size();
                if (get_ships(&ships, &ship_count, size) == OUT_OF_MEMORY) {
                        printf("Out of memory, abort!");
                        return -1;
                }
                if (ship_count > 1) { /*Sortiert das Feld der verfügbaren Schiffe*/
                        qsort(ships, ship_count, sizeof(int), compare);
                }

                if ((ship_class_count = init_stats(&stats0, &stats1, ships, ship_count)) == OUT_OF_MEMORY) {
                        free(ships);
                        printf("Out of memory, abort!");
                        return -1;
                }

                clear_screen();
        }

        /*Initalisiert die Matrizen für das Spiel*/

        if (init_battleground(&battleground0, size) == OUT_OF_MEMORY) {
                free(ships);
                for (i = 0; i < ship_class_count; i++) {
                        free(stats0[i]);
                }
                free(stats0);
                printf("Out of memory, abort!");
                return -1;
        }

        if (init_battleground(&battleground1, size) == OUT_OF_MEMORY) {
                free(ships);
                for (i = 0; i < ship_class_count; i++) {
                        free(stats0[i]);
                }
                free(stats0);

                for (i = 0; i < size; i++) {
                        free(battleground0[i]);
                }
                free(battleground0);

                printf("Out of memory, abort!");
                return -1;
        }

        /*Setzen der Schiffe*/
        player_set_ships(battleground0, size, ships, ship_count, 0);

        if (single) {
                rand_set_ships(battleground1, size, ships, ship_count);
        } else {
                clear_screen();
                player_set_ships(battleground1, size, ships, ship_count, 1);
        }
        clear_screen();

        do { /*Game Loop der erst dann verlassen wird, wenn es einen Gewinner gibt*/
                downed = 0;
                if (!player_turn) {  /*Spieler 1*/
                        if (first){
                                show_player_battleground(battleground0, size, player_turn);
                                first = 0;
                        }
                        shot = player_move(battleground1, size, player_turn);
                        hit = shoot(battleground1, shot[0], shot[1]);
                        if (hit > 0) {
                                downed = check_downed(battleground1, size, shot[0], shot[1]);
                        }
                        updateStats(stats0, ship_class_count, hit);
                        response(battleground1, size, shot, hit, downed, player_turn);

                        if (is_end_game(battleground1, size)) {
                                win = 1;
                        }

                        if (hit < 1) {
                                player_turn = !player_turn;
                                first = 1;
                        }


                } else { /*Spieler 2*/
                        if (single) { /*KI Spieler 2*/
                                shot = get_ai_turn(battleground0, size, diff, ships);
                                hit = shoot(battleground0, shot[0], shot[1]);
                                if (hit > 0) {
                                        downed = check_downed(battleground0, size, shot[0], shot[1]);
                                }

                                updateStats(stats1, ship_class_count, hit);
                                response(battleground0, size, shot, hit, downed, player_turn);

                                if (is_end_game(battleground0, size)) {
                                        win = 2;
                                }

                                if (hit < 1) {
                                        player_turn = !player_turn;
                                }


                        } else { /*Menschlicher Spieler 2*/
                                if (first){
                                        show_player_battleground(battleground1, size, player_turn);
                                        first = 0;
                                }

                                shot = player_move(battleground0, size, player_turn);
                                hit = shoot(battleground0, shot[0], shot[1]);
                                if (hit > 0) {
                                        downed = check_downed(battleground0, size, shot[0], shot[1]);
                                }

                                updateStats(stats1, ship_class_count, hit);
                                response(battleground0, size, shot, hit, downed, player_turn);

                                if (is_end_game(battleground0, size)) {
                                        win = 2;
                                }

                                if (hit < 1) {
                                        player_turn = !player_turn;
                                        first = 1;
                                }
                        }
                }
        } while (!win);

        clear_screen();
        draw_screen(battleground0, size);
        draw_screen(battleground1, size);
        printf("Spieler %i hat gewonnen!\n", win);
        print_stats(stats0, stats1, ship_class_count);


        /* Gibt reservierten Speicher wieder frei */
        free(ships);
        for (i = 0; i < ship_class_count; i++) {
                free(stats0[i]);
                free(stats1[i]);
        }
        free(stats0);
        free(stats1);

        for (i = 0; i < size; i++) {
                free(battleground0[i]);
                free(battleground1[i]);
        }
        free(battleground0);
        free(battleground1);
        return 0;
}
