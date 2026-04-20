// funkcje do redukcji kolorów i tworzenia palet
#ifndef GK2024_PALETA_H_INCLUDED
#define GK2024_PALETA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
using namespace std;
void paletaNarzucona();
void narysujPalete(int, int, SDL_Color[]);
void narysujPaleteSzarosci(int poczX, int poczY, SDL_Color pal8[]);
void paletaNarzuconaSzarosci();
void paletaNarzuconaDitteringKolor();
void paletaNarzuconaDitteringSzary();
void czyscPalete();
void paletaDedykowana();
#endif // GK2024_PALETA_H_INCLUDED
