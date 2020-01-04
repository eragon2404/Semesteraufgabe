//
// Created by NoahB on 04.01.20.
//

#include "battleground.h"
#include "console.h"

#include <stdio.h>
#include <stdlib.h>

int getBattlegroundSize() /*Fragt den Spiele nach der gewünschten Feldgröße*/
{
    int n;
    do{
        printf("Waehlen sie eine Feldgroesse: (min 10, max 20): ");
        if (scanf("%i", &n) /* NOLINT(cert-err34-c) */ != 1) {
            printf("Keine gültige Eingabe!\n");
            n = 0;
            if (getchar() != '\n'){
                flush();
            }
            continue;
        }
        if (n < 10 || n > 20){
            printf("Keine gueltige Eingabe!\n");
            n = 0;
        } else {
            return n;
        }
    } while (!n);

    return 0;
}

int initBattleground(char **battleground, int size) /*Initalisiert die Matrizen mit 'w' als leere Felder*/
{
    int x, y;
    for (x = 0; x < size; x++){
        battleground[x] = malloc(size);
        for(y = 0; y < size; y++){
            battleground[x][y] = 'w';
        }
    }

}