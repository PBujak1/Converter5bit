// podstawowe funkcje
#ifndef GK2024_FUNKCJE_H_INCLUDED
#define GK2024_FUNKCJE_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();
void Funkcja6();
void Funkcja7();
void Funkcja8();
void Funkcja9();
void narzuconaV1();
void narzuconaV2();
void narzuconaV3();
int sprawdzKolor(SDL_Color kolor);
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);
void zaktualizujTabliceBayera4_2bit();
void zaktualizujTabliceBayera4_5bit();
void zaktualizujTabliceBayera4_1bit();
int dodajKolor(SDL_Color kolor);
Uint8 z24Kdo8K(SDL_Color kolor);
SDL_Color z8Kdo24K(Uint8 kolor);
Uint8 porownajZTablicaBayera(Uint8 kanal, int x, int y);
SDL_Color z8Kdo24KSzarosci(Uint8 kolor);
void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel(int x, int y);
void czyscEkran(Uint8 R, Uint8 G, Uint8 B);
void ladujBMP(char const* nazwa, int x, int y);

#endif // GK2024_FUNKCJE_H_INCLUDED
