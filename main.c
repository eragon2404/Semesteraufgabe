/*TODO: Spiel fertig machen*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OUT_OF_MEMORY -69420

/*Rund um das Spielfeld und seine Erstellung*/
int getBattlegroundSize();
int initBattleground(char **battleground, int size);

/*Alles, was das Spiel in die Konsole bringt*/
void drawIntro();
void drawScreen(char **matrix, int size, int playerTurn);
void clearScreen();
void flush();

/*Fuer die KI*/
int * ai_diff3(char **matrix, int size, int difficulty);
int is_useful(char **matrix, int y, int x, int size, int difficulty);
int * get_from_solo(char **matrix, int y, int x, int difficulty);
int * get_from_double(char **matrix, int y, int x, int difficulty);
int ai_set_ships(char **matrix, int size, int *ships, int ship_count);


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


/*--------------KI---------------*/


int * ai_diif3(char **matrix, int size)
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
            } else if (is_useful(matrix, iy, ix, size, 3) == 1) {
                    count_useful++;
            }
        }
    }
    /* Kein getroffenes Schiff -> Zufaelliges Feld im Muster nehmen */
    if (count_hit == 0){
        random_num = rand() % count_hit;
        in = 0;
        for (iy = 0; iy < size; iy++) {
            for (ix = 0; ix < size; ix++) {
                if (is_useful(matrix, iy, ix, size, 3) == 1) {
                    if (in == random_num) {
                        result[0] = iy;
                        result[1] = ix;
                        return result;
                    }
                }
            }
        }
        /* Ein getroffenes Schiff - Feld -> sinvolles anliegendes Feld nehmen */
    } else if (count_hit == 1){
        if (is_useful(matrix, first_hit[0] + 1, first_hit[1] + 0, size, 2)) {
            result[0] = first_hit[0] + 1;
            result[1] = first_hit[1] + 0;
        } else if (is_useful(matrix, first_hit[0] - 1, first_hit[1] + 0, size, 2)) {
            result[0] = first_hit[0] - 1;
            result[1] = first_hit[1] + 0;
        } else if (is_useful(matrix, first_hit[0] + 0, first_hit[1] + 1, size, 2)) {
            result[0] = first_hit[0] + 0;
            result[1] = first_hit[1] + 1;
        } else if (is_useful(matrix, first_hit[0] + 0, first_hit[1] - 1, size, 2)) {
            result[0] = first_hit[0] + 0;
            result[1] = first_hit[1] - 1;
        }
        return result;

        /* Zwei getroffenes Schiff - Felder -> sinvolles ende des Schiifs nehmen */
    } else if (count_hit > 1){
        vector[0] = last_hit[0] - first_hit[0];
        vector[1] = last_hit[1] - first_hit[1];

        if (vector[0] != 0) {
            vector[0] /= abs(vector[0]);
        }
        if (vector[1] != 0) {
            vector[1] /= abs(vector[1]);
        }

        result[0] = last_hit[0] + vector[0];
        result[1] = last_hit[1] + vector[1];

        if (is_useful(matrix, result[0], result[1], size, 2)) {
            return result;
        } else {
            result[0] = first_hit[0] - vector[0];
            result[1] = first_hit[1] - vector[1];
            return result;
        }
    }
}

int is_useful(char **matrix, int y, int x, int size, int difficulty)
{
    if (y < 0 || y >= size || x < 0 || x >= size) {
        return 0;
    }
    if (!((*matrix + y*size)[x] == 'u' || (*matrix + y*size)[x] == 'w'))  {
        return 0;
    }
    if (difficulty >= 2) {
        if (y+1 < size) {
            if ((*matrix + (y + 1)*size)[(x + 0)] == 'd') {
                return 0;
            }
        }
        if (y-1 >= 0) {
            if ((*matrix + (y - 1)*size)[(x + 0)] == 'd') {
                return 0;
            }
        }
        if (x+1 < size) {
            if ((*matrix + (y + 0)*size)[(x + 1)] == 'd') {
                return 0;
            }
        }
        if (x-1 >= 0) {
            if ((*matrix + (y + 0)*size)[(x - 1)] == 'd') {
                return 0;
            }
        }
    }
    if (difficulty >= 3) {
        if ((y + 1) % 2 != (x + 1) % 2){
            return 0;
        }
    }
    return 1;
}

int ai_set_ships(char **matrix, int size, int *ships, int ship_count)
{
    int i;
    while (1){
        for (i = 0; i < ship_count; i++){
            if (!set_ship(matrix, size, rand() % size, rand() % size, rand() % 4, ships[i])){
                break;
            }
        }
        if (i == ship_count - 1) {
            return 1;
        } else {
            initBattleground(matrix, size);
        }
    }
}
