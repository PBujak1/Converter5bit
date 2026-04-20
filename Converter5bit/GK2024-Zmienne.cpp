// zmienne globalne
#include "GK2024-Zmienne.h"

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

SDL_Color paleta8[szerokosc*wysokosc];
int ileKolorow = 0;

SDL_Color paleta8k[256];
SDL_Color paleta8s[256];
int tablicaBayera4[4][4] = {{6, 14, 8, 16},
                            {10, 2, 12, 4},
                            {7, 15, 5, 13},
                            {11, 3, 9, 1}
                            };
float zaktualizowanaTablicaBayera4[4][4]{};
float zaktualizowanaTablicaBayera4_1[4][4]{};

//MedianCut
int ileKubelkow;
Uint8 obrazekSzarosc[320*200];
SDL_Color obrazekKolor[320*200];
