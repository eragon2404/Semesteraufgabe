#ifndef SEMESTERAUFGABE_CONSOLE_H
#define SEMESTERAUFGABE_CONSOLE_H

#define SHOW_FULL_BATTLEGROUND 0 /*Schalter um stets alle Schiffe anzuzeigen*/
#define SHOW_ASCII_ART 1 /*Schalter um Ausgabeart der Matrix einzustellen*/

#define TILE_SIZE_VERT 2 /*Hoehe und Breite der Tiles im ASCII Modus, nicht verändern ohne Code anzupassen!*/
#define TILE_SIZE_HOR 7


typedef struct _tiles {
        char front_vert[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char mid_vert[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char end_vert[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char front_hor[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char mid_hor[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char end_hor[TILE_SIZE_VERT][TILE_SIZE_HOR];

        char dwn_front_vert[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char dwn_mid_vert[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char dwn_end_vert[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char dwn_front_hor[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char dwn_mid_hor[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char dwn_end_hor[TILE_SIZE_VERT][TILE_SIZE_HOR];

        char water[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char downed[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char hit[TILE_SIZE_VERT][TILE_SIZE_HOR];
        char miss[TILE_SIZE_VERT][TILE_SIZE_HOR];
} tiles;

void draw_intro();

void draw_screen(char **matrix, int size, tiles *t);

void player_draw_screen(char **matrix, int size, tiles *t);

int check_tile_orientation(char **matrix, int size, int x, int y);

void set_tiles(tiles *t);

void print_stats(int **stats1, int **stats2, int ship_class_count);

void player_set_ships(char **matrix, int size, int *ships, int ship_count, int player_turn, tiles *t);

void get_settings(int *single, int *diff, int *standart);

int get_battleground_size();

int get_ships(int **ships, int *ship_count, int size);

void show_player_battleground(char **matrix, int size, int player_turn, tiles *t);

int *player_move(char **matrix, int size, int player_turn, tiles *t);

int response(char **matrix, int size, int *shot, int hit, int downed, int player, tiles *t);

void clear_screen();

void flush();

#endif
