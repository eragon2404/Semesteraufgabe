//
// Created by NoahB on 04.01.20.
//

#include "console.h"
#include <stdio.h>

void drawIntro()
{
    printf("--------------------------------------------------------------------------------\n"
           "                            Schiffe Versenken Deluxe                            \n"
           "--------------------------------------------------------------------------------\n"
           "--------------------------------------------------------------------------------\n");
}

void drawScreen(char **matrix, int size, int playerTurn) /*Zeigt den Spieler, der an der Reihe ist, an und zeichnet dessen Matrize TODO: Ein Koordinatensystem zeichnen*/
{
    int x, y;

    clearScreen();
    for(x = 0; x < size; x++){
        for(y = 0; y < size; y++){
            printf("%c  ", matrix[x][y]);
        }
        printf("\n");
    }

    printf("Spieler %i ist an der Reihe\n", playerTurn);

}

void clearScreen() /*Ein wunderschöner Weg um den Screen sauber zu bekommen*/
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
           "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void flush(){
    while(getchar() != '\n');
}