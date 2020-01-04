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



int main(void) {

    int i, playerTurn, size, *ships, ship_count;
    char **battleground0 /*Matrize Spieler 0*/, **battleground1; /*Matrize Spieler 1*/

    srand(time(NULL));

    playerTurn = 0;
    draw_intro();
    size = get_battleground_size();

    ships = malloc(6 * sizeof(int));

    ships[0] = 2;
    ships[1] = 2;
    ships[2] = 3;
    ships[3] = 3;
    ships[4] = 4;
    ships[5] = 4;
    ship_count = 6;





    /* TODO: Kann man das hier noch in die methode integrieren? Der Fehler, dass die beiden ptr nicht initalisiert sind muss halt vermieden werden */
    battleground0 = malloc(size * sizeof(char*));
    battleground1 = malloc(size * sizeof(char*));

    if (battleground0 == NULL || battleground1 == NULL){
        printf("Out of memory, abort!");
        return -1;
    }

    if (init_battleground(battleground0, size) == OUT_OF_MEMORY) {/*TODO: Das hier moechte in die setzeSchiffe Methode*/
        printf("Out of memory, abort!");
        return -1;
    }

    if (init_battleground(battleground1, size) == OUT_OF_MEMORY) {/*TODO: Das hier moechte in die setzeSchiffe Methode*/
        printf("Out of memory, abort!");
        return -1;
    }

    /*player_set_ships(battleground0, size, ships, ship_count);*/
    /*draw_screen(battleground0, size);*/
    rand_set_ships(battleground1, size, ships, ship_count);
    draw_screen(battleground1, size);


    /* Gibt reservierten Speicher wieder frei */
    free(ships);

    for (i = 0; i < size; i++){
        free(battleground0[i]);
        free(battleground1[i]);
    }
    free(battleground0);
    free(battleground1);
    return 0;
}
