/*TODO: Spiel fertig machen*/

#include <stdio.h>
#define ARRAY_SIZE 20

/*Rund um das Spielfeld und seine Erstellung*/
int getBattlegroundSize();
void initBattleground(char (*battleground0)[], char (*battleground1)[], int size);

/*Alles, was das Spiel in die Konsole bringt*/
void drawIntro();
void drawScreen(char (*matrix)[], int size, int playerTurn);
void clearScreen();


int main(void) {
    drawIntro();
    int playerTurn = 0;

    int size = getBattlegroundSize();
    char battleground0[ARRAY_SIZE][ARRAY_SIZE]; /*Matrize Spieler 0*/
    char battleground1[ARRAY_SIZE][ARRAY_SIZE]; /*Matrize Spieler 1*/

    initBattleground(battleground0, battleground1, size); /*TODO: Das hier moechte in die setzeSchiffe Methode*/
    drawScreen(battleground0, size, playerTurn);


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
    return 1;
}

int is_useful(char (*matrix)[], int y, int x, int difficulty)
{
    return 1;
}

int * get_from_solo(char (*matrix)[], int y, int x, int difficulty)
{
    return 1;
}

int * get_from_double(char (*matrix)[], int y, int x, int difficulty)
{
    return 1;
}