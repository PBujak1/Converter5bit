// podstawowe funkcje
#include "GK2024-Funkcje.h"
#include "GK2024-Zmienne.h"
#include "GK2024-Paleta.h"
#include "GK2024-MedianCut.h"
#include "GK2024-Pliki.h"


void Funkcja1() {
    narzuconaV1();
    narzuconaV2();
    narzuconaV3();
    SDL_UpdateWindowSurface(window);
}

void Funkcja2() {
    paletaMedianCutBW();
    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {
    paletaMedianCutKolor();
    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {
    paletaNarzucona();
    SDL_UpdateWindowSurface(window);
}

void Funkcja5() {
    paletaNarzuconaSzarosci();
    SDL_UpdateWindowSurface(window);
}

void Funkcja6() {
    paletaDedykowana();
    narysujPalete(0, 200, paleta8);
    SDL_UpdateWindowSurface(window);
}

void Funkcja7() {
    paletaNarzuconaDitteringKolor();
    SDL_UpdateWindowSurface(window);
}

void Funkcja8() {
    paletaNarzuconaDitteringSzary();
    SDL_UpdateWindowSurface(window);
}

void Funkcja9() {
    zapiszPlik8();
    odczytajPlik8();
    SDL_UpdateWindowSurface(window);

    SDL_UpdateWindowSurface(window);
}
void narzuconaV1() //konwersja na 5bit, ucina LSB i nie przetwarza na nową skalę
{
    SDL_Color kolor;
    int R, G, B;
    int newR, newG, newB;
    for(int y = 0; y < wysokosc / 2; y++)
    {
        for(int x = 0; x < szerokosc / 2; x++)
        {
            kolor=getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;
            newR = R>>6; // kasuje 6 ostatnich bitów (RRXXXXXX)
            newG = G>>6; // kasuje 6 ostatnich bitów (GGXXXXXX)
            newB = B>>7; // kasuje 7 ostatnich bitów (BXXXXXXX)
            R = newR<<6; //oddaje skasowane bity uzupełniając zerami (RR000000)
            G = newG<<6;
            B = newB<<7;
            setPixel(x + szerokosc / 2, y, R, G, B);
        }

    }
}
void narzuconaV2() //konwersja na 5bit, ucina LSB ale przetwarza na nową skalę
{
    SDL_Color kolor;
    int R, G, B;
    int newR, newG, newB;
    for(int y = 0; y < wysokosc / 2; y++)
    {
        for(int x = 0; x < szerokosc / 2; x++)
        {
            kolor=getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;
            newR = R>>6;
            newG = G>>6;
            newB = B>>7;
            R = newR * 255.0/3.0; //odtworzenie na podstawie nowej skali
            G = newG * 255.0/3.0;
            B = newB * 255.0/1.0;
            setPixel(x, y + wysokosc / 2, R, G, B);
        }

    }
}
void narzuconaV3() //konwersja na 5bit, konwertuje zarówno z 8bit na 5 bit jak i na nową skalę z 5bit na 8bit
{
    SDL_Color kolor;
    int R, G, B;
    int newR, newG, newB;
    for(int y = 0; y < wysokosc / 2; y++)
    {
        for(int x = 0; x < szerokosc / 2; x++)
        {
            kolor=getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;
            newR = round(R*3.0/255.0);
            newG = round(G*3.0/255.0);
            newB = round(B*1.0/255.0);
            R = newR * 255.0/3.0;
            G = newG * 255.0/3.0;
            B = newB * 255.0/1.0;
            setPixel(x + szerokosc / 2, y + wysokosc / 2, R, G, B);
        }

    }
}
Uint8 z24Kdo8K(SDL_Color kolor) //odczytuje piksel i zamienia poszczególne składowe na liczbę 5bit w której bity odpowiadają kolejno: RRGGB
{
    int R, G, B;
    Uint8 kolor5bit;
    R = kolor.r;
    G = kolor.g;
    B = kolor.b;
    int newR = round(R*3.0/255.0);
    int newG = round(G*3.0/255.0);
    int newB = round(B*1.0/255.0);
    kolor5bit = (newR<<3) | (newG<<1) | newB;
    return kolor5bit;
}

SDL_Color z8Kdo24K(Uint8 kolor) //konwertuje liczbę 5bit na obiekt klasy SDL_Color
{
    SDL_Color kolor24bit;
    int newR, newG, newB;
    newR = (kolor  & (0b11000)) >> 3; //czerwony, (11000)
    newG = (kolor  & (0b00110)) >> 1;    //zielony, (00110)
    newB = (kolor  & (0b00001));         // niebieski, (00001)

    kolor24bit.r = newR * 255.0/3.0; //odtworzenie zakresu
    kolor24bit.g = newG * 255.0/3.0;
    kolor24bit.b = newB * 255.0/1.0;
    return kolor24bit;
}
SDL_Color z8Kdo24KSzarosci(Uint8 kolor) //konwertuje liczbę 5bit na obiekt klasy SDL_Color, gdzie cała liczba opisuje jedynie odcienie szarości
{
    SDL_Color kolor24bit;
    Uint8 szary8bit = kolor / 32.0 * 255.0; //konwersja z 5bit na 8 bit
    kolor24bit.r = szary8bit;
    kolor24bit.g = szary8bit;
    kolor24bit.b = szary8bit;
    return kolor24bit;
}
int sprawdzKolor(SDL_Color kolor)
{
    if(ileKolorow > 0)
    {
        for(int i = 0; i < ileKolorow; i++)
        {
            if(porownajKolory(kolor, paleta8[i]))
            {
                return i;
            }
        }
    }
    return dodajKolor(kolor);
}
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2)
{
    if(kolor1.r != kolor2.r)
    {
        return false;
    }
    if(kolor1.g != kolor2.g)
    {
        return false;
    }
    if(kolor1.b != kolor2.b)
    {
        return false;
    }
    return true;
}
int dodajKolor(SDL_Color kolor)
{
    int aktualnyKolor = ileKolorow;
    paleta8[aktualnyKolor] = kolor;
    if(ileKolorow < 256)
    {
        cout << aktualnyKolor << ": [" << (int)kolor.r << ", ";
        cout << (int)kolor.g << ", " << (int)kolor.b << "]\n";
    }
    ileKolorow++;
    return aktualnyKolor;
}
void zaktualizujTabliceBayera4_2bit()
{
    int zakresWartosci{85}; // 1/3 z 255 dla 2 bitow
    float zakres = zakresWartosci; //dla 2 bitów koloru R i G
    int rozmiar{4};
    float podzial = zakres*1.0/(rozmiar*rozmiar);
    for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            zaktualizowanaTablicaBayera4[i][j] = (tablicaBayera4[i][j]*podzial)-podzial/2;
        }
    }
        for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            std::cout << zaktualizowanaTablicaBayera4[i][j] << " ";
        }
        std::cout << endl;
    }
}
void zaktualizujTabliceBayera4_5bit()
{
    int zakresWartosci{255};
    float zakres = zakresWartosci / 32.0; //dla 5 bitów szarych
    int rozmiar{4};
    float podzial = zakres*1.0/(rozmiar*rozmiar);
    for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            zaktualizowanaTablicaBayera4[i][j] = (tablicaBayera4[i][j]*podzial)-podzial/2;
        }
    }
        for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            std::cout << zaktualizowanaTablicaBayera4[i][j] << " ";
        }
        std::cout << endl;
    }
}

void zaktualizujTabliceBayera4_1bit()
{
    int zakresWartosci{255};
    float zakres = zakresWartosci / 1.0; //dla 1 bitu koloru B
    int rozmiar{4};
    float podzial = zakres*1.0/(rozmiar*rozmiar);
    for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            zaktualizowanaTablicaBayera4_1[i][j] = (tablicaBayera4[i][j]*podzial)-podzial/2;
        }
    }
        for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            std::cout << zaktualizowanaTablicaBayera4_1[i][j] << " ";
        }
        std::cout << endl;
    }
}

Uint8 porownajZTablicaBayera(Uint8 kanal, int x, int y)
{
    constexpr int rozmiarTablicy{4}; //tablica 4x4
    constexpr float zakres{255/3.0}; //85, dla koloru opisanego na 2 bitach
    int przesuniecieWartosci{0};
    Uint8 nowyKolor{};
    float wartoscWTablicy = zaktualizowanaTablicaBayera4[y%rozmiarTablicy][x%rozmiarTablicy];
    while(kanal > zakres)
    {
        przesuniecieWartosci++;
        kanal -= zakres;
    }
    if(kanal > wartoscWTablicy)
    {
        nowyKolor = 1;
    }else
    {
        nowyKolor = 0;
    }
    nowyKolor += przesuniecieWartosci;
    nowyKolor *= zakres;
    return nowyKolor;
}













void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p1 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2) * bpp;
    Uint8 *p2 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2) * bpp;
    Uint8 *p3 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2+1) * bpp;
    Uint8 *p4 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2+1) * bpp;

    /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p1 = pixel;
            *p2 = pixel;
            *p3 = pixel;
            *p4 = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p1 = pixel;
            *(Uint16 *)p2 = pixel;
            *(Uint16 *)p3 = pixel;
            *(Uint16 *)p4 = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p1[0] = (pixel >> 16) & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = pixel & 0xff;
                p2[0] = (pixel >> 16) & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = pixel & 0xff;
                p3[0] = (pixel >> 16) & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = pixel & 0xff;
                p4[0] = (pixel >> 16) & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = pixel & 0xff;
            } else {
                p1[0] = pixel & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = (pixel >> 16) & 0xff;
                p2[0] = pixel & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = (pixel >> 16) & 0xff;
                p3[0] = pixel & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = (pixel >> 16) & 0xff;
                p4[0] = pixel & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p1 = pixel;
            *(Uint32 *)p2 = pixel;
            *(Uint32 *)p3 = pixel;
            *(Uint32 *)p4 = pixel;
            break;

        }
    }
}

void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc*2) && (y>=0) && (y<wysokosc*2))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p = pixel;
            break;
        }
    }
}

SDL_Color getPixel(int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)screen->pixels ;

        //przesunięcie względem y
        pPosition+=(screen->pitch*y*2) ;

        //przesunięcie względem x
        pPosition+=(screen->format->BytesPerPixel*x*2);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)surface->pixels ;

        //przesunięcie względem y
        pPosition+=(surface->pitch*y) ;

        //przesunięcie względem x
        pPosition+=(surface->format->BytesPerPixel*x);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}


void ladujBMP(char const* nazwa, int x, int y) {
    SDL_Surface* bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Color kolor;
        for (int yy=0; yy<bmp->h; yy++) {
			for (int xx=0; xx<bmp->w; xx++) {
				kolor = getPixelSurface(xx, yy, bmp);
				setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
			}
        }
		SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }

}


void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}

