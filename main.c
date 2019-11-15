#include <stdio.h>

int init();
int getBattlegroundSize();
void drawIntro();
void drawScreen(char (*matrix)[]);


int main(void) {
    drawIntro();
    int x = getBattlegroundSize();
    char battleground[x][x];
    return 0;
}

int init() /*Initalisiert die Daten TODO: was auch immer erledigt werden muss */
{

}

void drawIntro()
{
    printf("--------------------------------------------------------------------------------\n"
           "                            Schiffe Versenken Deluxe                            \n"
           "--------------------------------------------------------------------------------\n"
           "--------------------------------------------------------------------------------\n");
}

int getBattlegroundSize() //Fragt den Spiele nach der gewünschten Feldgröße
{
    int n;
    do{
        printf("Waehlen sie eine Feldgroesse: (min 10, max 20): ");
        scanf("%i", &n);
        if (n < 10 || n > 20){
            printf("Keine gueltige Eingabe!\n");
            n = 0;
        } else {
            return n;
        }
    } while (!n);
}

