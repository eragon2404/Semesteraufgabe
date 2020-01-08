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

    int i, playerTurn, size, *ships, ship_count, single, diff, standart;
    char **battleground0 /*Matrize Spieler 0*/, **battleground1; /*Matrize Spieler 1*/

    srand(time(NULL));
    battleground0 = NULL;
    battleground1 = NULL;
    ships = NULL;

    playerTurn = 0;
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



    draw_screen(battleground0, size);


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
