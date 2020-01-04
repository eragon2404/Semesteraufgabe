/*TODO: Spiel fertig machen*/

#include <stdio.h>
#include <stdlib.h>

#include "battleground.h"
#include "ki.h"
#include "console.h"

#include <time.h>

#define OUT_OF_MEMORY -69420



int main(void) {

    int playerTurn, i;
    playerTurn = 0;
    drawIntro();


    int size = getBattlegroundSize();
    char **battleground0 /*Matrize Spieler 0*/, **battleground1; /*Matrize Spieler 1*/


    /* TODO: Kann man das hier noch in die methode integrieren? Der Fehler, dass die beiden ptr nicht initalisiert sind muss halt vermieden werden */
    battleground0 = malloc(size * sizeof(char*));
    battleground1 = malloc(size * sizeof(char*));

    if (battleground0 == NULL || battleground1 == NULL){
        printf("Out of memory, abort!");
        return -1;
    }

    if (initBattleground(battleground0, size) == OUT_OF_MEMORY) {/*TODO: Das hier moechte in die setzeSchiffe Methode*/
        printf("Out of memory, abort!");
        return -1;
    }

    if (initBattleground(battleground1, size) == OUT_OF_MEMORY) {/*TODO: Das hier moechte in die setzeSchiffe Methode*/
        printf("Out of memory, abort!");
        return -1;
    }

    drawScreen(battleground0, size, playerTurn);


    /* Gibt reservierten Speicher der Matrizen wieder frei */
    for (i = 0; i < size; i++){
        free(battleground0[i]);
        free(battleground1[i]);
    }
    free(battleground0);
    free(battleground1);
    return 0;
}
