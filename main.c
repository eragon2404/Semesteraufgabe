#include <stdio.h>

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
    /*TODO: Die variable Länge des Arrays muss umgangen werden (Methode mit "switch case" oder so?)*/
    char battleground0[size][size]; /*Matrize Spieler 0*/
    char battleground1[size][size]; /*Matrize Spieler 1*/

    initBattleground(battleground0, battleground1, size);

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
}

void initBattleground(char (*battleground0)[], char (*battleground1)[], int size) /*Initalisiert die Matrizen mit '~' als leere Felder*/
{
    int x, y;
    for (x = 0; x < size; x++){
        for(y = 0; y < size; y++){
            (*battleground0 + x)[y] = '~';
            (*battleground1 + x)[y] = '~';
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

void drawScreen(char (*matrix)[], int size, int playerTurn) /*Zeigt den Spieler, der an der Reihe ist, an und zeichnet dessen Matrize*/
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

