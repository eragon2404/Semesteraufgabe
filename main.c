/*TODO: Spiel fertig machen*/

#include <stdio.h>
#include <stdlib.h>

#include "battleground.h"
#include "ki.h"
#include "console.h"

#include <time.h>

#ifndef OUT_OF_MEMORY
#define OUT_OF_MEMORY -69420
#endif

#define DEBUG 0


int main(void) {

    int i, player_turn, size, *ships, ship_count, single, diff, standart, win, *shot, hit;
    char **battleground0 /*Matrize Spieler 0*/, **battleground1; /*Matrize Spieler 1*/

    srand(time(NULL));
    battleground0 = NULL;
    battleground1 = NULL;
    ships = NULL;

    player_turn = win = 0;
    draw_intro();
    getSettings(&single, &diff, &standart);
    clear_screen();

    if (standart){
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

    } else {

        size = get_battleground_size();
        if (get_ships(&ships, &ship_count, size) == OUT_OF_MEMORY) {
            printf("Out of memory, abort!");
            return -1;
        }
        clear_screen();
    }

    if (DEBUG) {

        free(ships);
        ship_count = 10;
        if ((ships = malloc(ship_count * sizeof(int))) == NULL) {
            printf("Out of memory, abort!");
            return -1;
        }

        ships[0] = 2;
        ships[1] = 2;
        ships[2] = 3;
        ships[3] = 4;
        ships[4] = 5;
        ships[5] = 2;
        ships[6] = 3;
        ships[7] = 4;
        ships[8] = 5;
        ships[9] = 2;
    }

    if (init_battleground(&battleground0, size) == OUT_OF_MEMORY ||
        init_battleground(&battleground1, size) == OUT_OF_MEMORY) {
        printf("Out of memory, abort!");
        return -1;
    }

    printf("Spieler 1 muss nun seine Schiffe setzen!\n");
    player_set_ships(battleground0, size, ships, ship_count);

    if (single){
        rand_set_ships(battleground1, size, ships, ship_count);
    } else {
        clear_screen();
        printf("Spieler 2 muss nun seine Schiffe setzen!\n");
        player_set_ships(battleground1, size, ships, ship_count);
    }
    clear_screen();

    do{ /*Game Loop der erst dann verlassen wird, wenn es einen Gewinner gibt*/

        if (!player_turn){  /*Spieler 1*/
            shot = player_move(battleground1, size, player_turn);
            hit = shoot(battleground1, shot[0], shot[1]);
            response(battleground1, size, shot, hit, player_turn);

            if (is_end_game(battleground1, size)){
                win = 1;
            }

            if(hit < 1){
                player_turn = !player_turn;
            }


        } else { /*Spieler 2*/
            if (single){ /*KI*/
                shot = get_ai_turn(battleground0, size, diff, ships);
                hit = shoot(battleground0, shot[1], shot[0]);
                response(battleground0, size, shot, hit, player_turn);

                if (is_end_game(battleground0, size)){
                    win = 2;
                }

                if(hit < 1){
                    player_turn = !player_turn;
                }


            } else { /*Spieler*/
                shot = player_move(battleground0, size, player_turn);
                hit = shoot(battleground0, shot[0], shot[1]);
                response(battleground0, size, shot, hit, player_turn);

                if (is_end_game(battleground0, size)){
                    win = 2;
                }

                if(hit < 1){
                    player_turn = !player_turn;
                }
            }
        }
    } while (!win);

    clear_screen();
    draw_screen(battleground0, size);
    draw_screen(battleground1, size);
    printf("Spieler %i hat gewonnen!\n", win);


    /* Gibt reservierten Speicher wieder frei */

    free(ships);

    for (i = 0; i < size; i++) {
        free(battleground0[i]);
        free(battleground1[i]);
    }
    free(battleground0);
    free(battleground1);
    return 0;
}
