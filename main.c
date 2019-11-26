/*TODO: Spiel fertig machen*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 20

/*Rund um das Spielfeld und seine Erstellung*/
int getBattlegroundSize();
void initBattleground(char (*battleground0)[], char (*battleground1)[], int size);

/*Alles, was das Spiel in die Konsole bringt*/
void drawIntro();
void drawScreen(char (*matrix)[], int size, int playerTurn);
void clearScreen();

/*Fuer die KI*/
int * ki(char (*matrix)[], int size, int difficulty);
int is_useful(char (*matrix)[], int y, int x, int difficulty);
int * get_from_solo(char (*matrix)[], int y, int x, int difficulty);
int * get_from_double(char (*matrix)[], int y, int x, int difficulty);


int main(void) {
    drawIntro();
    int playerTurn = 0;

    int size = getBattlegroundSize();
    char battleground0[ARRAY_SIZE][ARRAY_SIZE]; /*Matrize Spieler 0*/
    char battleground1[ARRAY_SIZE][ARRAY_SIZE]; /*Matrize Spieler 1*/

    initBattleground(battleground0, battleground1, size); /*TODO: Das hier moechte in die setzeSchiffe Methode*/
    drawScreen(battleground0, size, playerTurn);

    ki(battleground0,size,3);


    return 0;
}

int getBattlegroundSize() /*Fragt den Spiele nach der gewünschten Feldgröße TODO: Alles andere als Zahlen abfangen*/
{
    int n;
    do{
        printf("Waehlen sie eine Feldgroesse: (min 10, max 20): ");
        scanf("%i", &n); /* NOLINT(cert-err34-c) */
        if (n < 10 || n > 20){
            printf("Keine gueltige Eingabe!\n");
            n = 0;
        } else {
            return n;
        }
    } while (!n);
    return 0;
}

void initBattleground(char (*battleground0)[], char (*battleground1)[], int size) /*Initalisiert die Matrizen mit '~' als leere Felder*/
{
    int x, y;
    for (x = 0; x < size; x++){
        for(y = 0; y < size; y++){
            (*battleground0 + x)[y] = 'w';
            (*battleground1 + x)[y] = 'w';
        }
    }

}

void drawIntro()
{
    printf("--------------------------------------------------------------------------------\n"
           "                            Schiffe Versenken Deluxe                            \n"
           "--------------------------------------------------------------------------------\n"
           "--------------------------------------------------------------------------------\n");
}

void drawScreen(char (*matrix)[], int size, int playerTurn) /*Zeigt den Spieler, der an der Reihe ist, an und zeichnet dessen Matrize TODO: Ein Koordinatensystem zeichnen*/
{
    int x, y;

    clearScreen();
    for(x = 0; x < size; x++){
        for(y = 0; y < size; y++){
            printf("%c  ", (*matrix + x)[y]);
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


/*--------------KI---------------*/


int * ki(char (*matrix)[], int size, int difficulty)
{

    static int result[2];

    int iy;
    int ix;

    int count_useful;
    int count_hit;

    int first_hit[2];
    int last_hit[2];

    int random_num;
    int in;

    int vector[2];

    count_useful = 0;
    count_hit = 0;

    /*Matrix analysieren*/
    for (iy = 0; iy < size; iy++){
        for (ix = 0; ix < size; ix++){
            if ((*matrix + iy*size)[ix] == 'h'){
                if (count_hit == 0){
                    first_hit[0] = iy;
                    first_hit[1] = ix;
                } else {
                    last_hit[0] = iy;
                    last_hit[1] = ix;
                }
                count_hit++;
            } else if ((*matrix + iy*size)[ix] == 'w' || (*matrix + iy*size)[ix] == 'u'){
                if (is_useful(matrix, iy, ix, difficulty) == 1){
                    count_useful++;
                }
            }
        }
    }

    if (count_hit == 0){
        random_num = rand() % count_hit;
        in = 0;
        for (iy = 0; iy < size; iy++) {
            for (ix = 0; ix < size; ix++) {
                if ((*matrix + iy * size)[ix] == 'w' || (*matrix + iy * size)[ix] == 'u') {
                    if (is_useful(matrix, iy, ix, difficulty) == 1) {
                        if (in == random_num) {
                            result[0] = iy;
                            result[1] = ix;
                            return result;
                        }
                    }
                }
            }
        }
    } else if (count_hit == 1){
        if (is_useful(matrix, first_hit[0] + 1, first_hit[1] + 0, difficulty)){
            result[0] = first_hit[0] + 1;
            result[1] = first_hit[1] + 0;
        } else if (is_useful(matrix, first_hit[0] - 1, first_hit[1] + 0, difficulty)) {
            result[0] = first_hit[0] - 1;
            result[1] = first_hit[1] + 0;
        } else if (is_useful(matrix, first_hit[0] + 0, first_hit[1] + 1, difficulty)) {
            result[0] = first_hit[0] + 0;
            result[1] = first_hit[1] + 1;
        } else if (is_useful(matrix, first_hit[0] + 0, first_hit[1] - 1, difficulty)) {
            result[0] = first_hit[0] + 0;
            result[1] = first_hit[1] - 1;
        }
    } else if (count_hit > 1){
        vector[0] = last_hit[0] - first_hit[0];
        vector[1]
    }

    return result;
}

int is_useful(char (*matrix)[], int y, int x, int difficulty)
{
    return 1;
}
