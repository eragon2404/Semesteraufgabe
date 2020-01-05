#include "console.h"
#include "battleground.h"
#include <stdio.h>

void draw_intro()
{
    printf("--------------------------------------------------------------------------------\n"
           "                            Schiffe Versenken Deluxe                            \n"
           "--------------------------------------------------------------------------------\n"
           "--------------------------------------------------------------------------------\n");
}

void draw_screen(char **matrix, int size) /*Zeigt den Spieler, der an der Reihe ist, an und zeichnet dessen Matrize */
{
    int x, y;

    clear_screen();

    printf("\t");
    for(x = 0; x < size; x++){
        if (x < 9){
            printf("%i  ", x + 1);
        } else {
            printf("%i ", x + 1);
        }

    }
    printf("\n");

    for(y = 0; y < size; y++){
        printf("%i:\t", y + 1);
        for(x = 0; x < size; x++){
            printf("%c  ", matrix[y][x]);
        }
        printf("\n");
    }
}

void player_set_ships(char **matrix, int size, int *ships, int ship_count){
    int i, current_ship, x, y, direction;
    current_ship = 0;
    direction = 0;


    while (current_ship < ship_count) {

        draw_screen(matrix, size);
        printf("Es stehen folgende Schiffe zur Auswahl:\n");
        for (i = 0; i < ship_count - 1; i++) {
            printf("%i", ships[i]);
        }
        printf("%i\n", ships[ship_count - 1]);

        printf("Wohin soll das Schiff %i mit Laenge %i? (Eingabe: x.y.richtung (o = 0, r = 1, u = 2, l = 3)\n", current_ship + 1, ships[current_ship]);
        do {
            if (scanf("%i.%i.%i", &x, &y, &direction) != 3) {
                printf("Ungueltige Eingabe! (Format: x.y.richtung)\n");
                if (getchar() != '\n'){
                    flush();
                }
                continue;
            }
            if (x - 1 < 0 || y - 1 < 0 || x > size || y > size) {
                printf("Ungueltige Koordinate! (Format: x.y.richtung)\n");
                if (getchar() != '\n'){
                    flush();
                }
                continue;
            }
            if (direction < 0 || direction > 3) {
                printf("Ungueltige Richtungsangabe! (o = 0, r = 1, u = 2, l = 3)\n");
                if (getchar() != '\n'){
                    flush();
                }
                continue;
            }

            if (getchar() != '\n'){
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

void clear_screen() /*Ein wunderschöner Weg um den Screen sauber zu bekommen*/
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
           "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void flush(){
    while(getchar() != '\n');
}