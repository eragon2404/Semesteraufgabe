#include "battleground.h"
#include "console.h"
#include <stdio.h>
#include <stdlib.h>

#define ship_mass_treshold 0.9



int get_battleground_size() /*Fragt den Spiele nach der gewünschten Feldgröße*/
{
    int n;
    do{
        printf("Waehlen sie eine Feldgroesse: (min 10, max 20): ");
        if (scanf("%i", &n) != 1) {
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

int init_battleground(char **matrix, int size) /*Initalisiert die Matrizen mit 'w' als leere Felder*/
{
    int x;
    for (x = 0; x < size; x++){
        if ((matrix[x] = malloc(size)) == NULL){
            return OUT_OF_MEMORY;
        }
    }

    reset_battleground(matrix, size);
    return 1;

}

void reset_battleground(char **matrix, int size){
    int x, y;
    for (x = 0; x < size; x++){
        for(y = 0; y < size; y++){
            matrix[x][y] = 'w';
        }
    }
}

int rand_set_ships(char **matrix, int size, int *ships, int ship_count)
{
    int i;

    printf("Das kann jetzt einen Moment dauern!\n");
    while (1){
        for (i = 0; i < ship_count; i++){
            if (!set_ship(matrix, size, rand() % size, rand() % size, rand() % 4, ships[i])){
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

int set_ship(char **matrix, int size, int y, int x, int direction, int ship_length){
    int i;

    if (matrix[y][x] != 'w'){
       return 0;
    }

    ship_length--;

    switch (direction){
        case 0: /*Schiff soll nach oben gesetzt werden*/
           if ((y = y - ship_length) < 0){
               return 0;
           }

           for (i = 0; i <= ship_length; i++){
               if (matrix[y + i][x] != 'w'){
                   return 0;
               } else if (y + i + 1 < size && matrix[y + i + 1][x] != 'w') { /*Checkt, ob Index in erlaubtem Bereich und ob Feld belegt ist*/
                   return 0;
               } else if (y + i - 1 >= 0 && matrix[y + i - 1][x] != 'w'){
                   return 0;
               } else if (x - 1 >= 0 && matrix[y + i][x - 1] != 'w'){
                   return 0;
               } else if (x + 1 < size && matrix[y + i][x + 1] != 'w'){
                   return 0;
               }
           }

            for (i = 0; i <= ship_length; i++){
                matrix[y + i][x] = 'u';
            }
            break;

        case 1: /*Schiff soll nach rechts gesetzt werden*/
            if ((x = x + ship_length) > size - 1){
                return 0;
            }

            for (i = 0; i <= ship_length; i++){
                if (matrix[y][x - i] != 'w'){
                    return 0;
                } else if (y + 1 < size && matrix[y + 1][x - i] != 'w') { /*Checkt, ob Index in erlaubtem Bereich und ob Feld belegt ist*/
                    return 0;
                } else if (y - 1 >= 0 && matrix[y - 1][x - i] != 'w'){
                    return 0;
                } else if (x - i - 1 >= 0 && matrix[y][x - i - 1] != 'w'){
                    return 0;
                } else if (x - i + 1 < size && matrix[y][x - i + 1] != 'w'){
                    return 0;
                }
            }

            for (i = 0; i <= ship_length; i++){
                matrix[y][x - i] = 'u';
            }
            break;

        case 2: /*Schiff soll nach unten gesetzt werden*/
            if ((y = y + ship_length) > size - 1){
                return 0;
            }

            for (i = 0; i <= ship_length; i++){
                if (matrix[y - i][x] != 'w'){
                    return 0;
                } else if (y - i + 1 < size && matrix[y - i + 1][x] != 'w') { /*Checkt, ob Index in erlaubtem Bereich und ob Feld belegt ist*/
                    return 0;
                } else if (y - i - 1 >= 0 && matrix[y - i - 1][x] != 'w'){
                    return 0;
                } else if (x - 1 >= 0 && matrix[y - i][x - 1] != 'w'){
                    return 0;
                } else if (x + 1 < size && matrix[y - i][x + 1] != 'w'){
                    return 0;
                }
            }

            for (i = 0; i <= ship_length; i++){
                matrix[y - i][x] = 'u';
            }
            break;

        case 3: /*Schiff soll nach links gesetzt werden*/
            if ((x = x - ship_length) < 0){
                return 0;
            }

            for (i = 0; i <= ship_length; i++){
                if (matrix[y][x + i] != 'w'){
                    return 0;
                } else if (y + 1 < size && matrix[y + 1][x + i] != 'w') { /*Checkt, ob Index in erlaubtem Bereich und ob Feld belegt ist*/
                    return 0;
                } else if (y - 1 >= 0 && matrix[y - 1][x + i] != 'w'){
                    return 0;
                } else if (x + i - 1 >= 0 && matrix[y][x + i - 1] != 'w'){
                    return 0;
                } else if (x + i + 1 < size && matrix[y][x + i + 1] != 'w'){
                    return 0;
                }
            }

            for (i = 0; i <= ship_length; i++){
                matrix[y][x + i] = 'u';
            }
            break;

        default:
            return 0;
    }

    return 1;
}

int ship_mass_validation(int size, int *ships, int ship_count){
    int i;
    int mass;
    mass = 0;
    for(i = 0; i < ship_count; i++){
        mass += ships[i];
    }
    mass *= 2;
    mass += ship_count;
    return (float)mass/(float)(size*size) <= ship_mass_treshold;
}