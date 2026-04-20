// zmienne globalne
#ifndef GK2024_ZMIENNE_H_INCLUDED
#define GK2024_ZMIENNE_H_INCLUDED

#include <SDL2/SDL.h>

#define szerokosc 640
#define wysokosc 400

#define tytul "GK2024 - Projekt - Zespol 23"

extern SDL_Window* window;
extern SDL_Surface* screen;

extern SDL_Color paleta8[szerokosc*wysokosc];
extern int ileKolorow;

extern SDL_Color paleta8k[256];
extern SDL_Color paleta8s[256];
extern int tablicaBayera4[4][4];
extern float zaktualizowanaTablicaBayera4[4][4];
extern float zaktualizowanaTablicaBayera4_1[4][4];


//MedianCut
extern int ileKubelkow;
extern Uint8 obrazekSzarosc[320*200];
extern SDL_Color obrazekKolor[320*200];
#endif // GK2024_ZMIENNE_H_INCLUDED
