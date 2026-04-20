// funkcje do redukcji kolorów i tworzenia palet
#include "GK2024-Paleta.h"
#include "GK2024-Zmienne.h"
#include "GK2024-Funkcje.h"

void paletaNarzucona()
{
    SDL_Color kolor, newColor, newSzary;
    Uint8 kolor5bit, szary8bit;
    SDL_Color paleta8k[32];
    for(int y = 0; y < wysokosc / 2; y++)
    {
        for(int x = 0; x < szerokosc / 2; x++)
        {
            kolor=getPixel(x, y);
            kolor5bit = z24Kdo8K(kolor);
            newColor = z8Kdo24K(kolor5bit);
            setPixel(x + szerokosc / 2, y, newColor.r, newColor.g, newColor.b);
        }
    }
    for(int i = 0; i < 32; i++)
    {
        paleta8k[i] = z8Kdo24K(i);
    }
    narysujPalete(0, 200, paleta8k);
}
void paletaNarzuconaSzarosci()
{
    SDL_Color kolor, newColor, newSzary;
    Uint8 szary5bit;
    SDL_Color paleta8k[32];
    for(int y = 0; y < wysokosc / 2; y++)
    {
        for(int x = 0; x < szerokosc / 2; x++)
        {
            kolor=getPixel(x, y); //pobierz piksel
            szary5bit = (0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b) / 255 * 31; //konwertuj na szary5bit
            newColor = z8Kdo24KSzarosci(szary5bit);
            setPixel(x + szerokosc / 2, y, newColor.r, newColor.g, newColor.b);
        }
    }
    for(int i = 0; i < 32; i++)
    {
        paleta8k[i] = z8Kdo24KSzarosci(i);
    }
    narysujPalete(0, 200, paleta8k);
}

void narysujPalete(int poczX, int poczY, SDL_Color pal8[])
{
    int x, y;

    for(int i = 0; i < 32; i++)
    {
        y = i / 8;
        x = i % 8;
        for(int row = 0; row < 40; row++)
        {
            for(int col = 0; col < 50; col++)
            {
                setPixel(x * 40 + row + poczX, y * 50 + col + poczY, pal8[i].r, pal8[i].g, pal8[i].b);
            }
        }
    }

}
void narysujPaleteSzarosci(int poczX, int poczY, SDL_Color pal8[])
{
    int x, y;

    for(int i = 0; i < 32; i++)
    {
        y = i / 8;
        x = i % 8;
        for(int row = 0; row < 40; row++)
        {
            for(int col = 0; col < 50; col++)
            {
                setPixel(x * 40 + row + poczX, y * 50 + col + poczY, pal8[i].r, pal8[i].r, pal8[i].r);
            }
        }
    }

}


//lab3
void czyscPalete()
{
    for(int i = 0; i < ileKolorow; i++)
    {
        paleta8[i] = {0,0,0};
    }
    for(int i = 0; i < 256; i++)
    {
        paleta8k[i] = {0, 0, 0};
        paleta8s[i] = {0, 0, 0};
    }
    ileKolorow = 0;
}
void paletaDedykowana()
{
    czyscPalete();
    int indexKoloru{};
    SDL_Color kolor;
    for(int y = 0; y < wysokosc / 2; y++)
    {
        for(int x = 0; x < wysokosc / 2; x++)
        {
            kolor = getPixel(x, y);
            indexKoloru = sprawdzKolor(kolor);
        }
    }
    cout << endl << "ile kolorow: " << ileKolorow << endl;
    if(ileKolorow <= 32) //5bit
    {
        cout << "Paleta spelnia ograniczenia 5-bit / piksel" << endl;
    }else
    {
        cout << "Paleta przekracza ograniczenia 5-bit / piksel" << endl;
    }
}
void paletaNarzuconaDitteringKolor()
{
    int rozmiarTablicy{4};
    constexpr float zakres = 255 / 3.0;
    int przesuniecieWartosci{0};
    zaktualizujTabliceBayera4_2bit();
    zaktualizujTabliceBayera4_1bit();
    SDL_Color kolor, newColor;
    Uint8 obecnyKolor{};
    Uint8 kolor5bit;
    SDL_Color paleta8k[32];
    float wartoscWTablicy{};
    for(int y = 0; y < wysokosc / 2; y++)
    {
        for(int x = 0; x < szerokosc / 2; x++)
        {
            kolor=getPixel(x, y);
            kolor5bit = z24Kdo8K(kolor);
            newColor = kolor;
            wartoscWTablicy = zaktualizowanaTablicaBayera4[y%rozmiarTablicy][x%rozmiarTablicy];
            float wartoscWTablicy_1bit = zaktualizowanaTablicaBayera4_1[y%rozmiarTablicy][x%rozmiarTablicy];
            obecnyKolor = newColor.r;
            if(obecnyKolor > zakres)
            {
                przesuniecieWartosci++;
                obecnyKolor -= zakres;
            }
            if(obecnyKolor > zakres)
            {
                przesuniecieWartosci++;
                obecnyKolor -= zakres;
            }
            if(obecnyKolor > wartoscWTablicy)
            {
                newColor.r = 1;
            }else
            {
                newColor.r = 0;
            }
            newColor.r += przesuniecieWartosci;
            newColor.r *= zakres;
            przesuniecieWartosci = 0;


            obecnyKolor = newColor.g;
            if(obecnyKolor > zakres)
            {
                przesuniecieWartosci++;
                obecnyKolor -= zakres;
            }
            if(obecnyKolor > zakres)
            {
                przesuniecieWartosci++;
                obecnyKolor -= zakres;
            }
            if(obecnyKolor > wartoscWTablicy)
            {
                newColor.g = 1;
            }else
            {
                newColor.g = 0;
            }
            newColor.g += przesuniecieWartosci;
            newColor.g *= zakres;
            przesuniecieWartosci = 0;


            /*
            obecnyKolor = newColor.b;
            if(obecnyKolor > wartoscWTablicy)
            {
                newColor.b = 255;
            }else
            {
                newColor.b = 0;
            }
            przesuniecieWartosci = 0;
*/
            obecnyKolor = newColor.b;
            if(obecnyKolor > zakres)
            {
                przesuniecieWartosci++;
                obecnyKolor -= zakres;
            }
            if(obecnyKolor > zakres)
            {
                przesuniecieWartosci++;
                obecnyKolor -= zakres;
            }
            if(obecnyKolor > wartoscWTablicy)
            {
                newColor.b = 1;
            }else
            {
                newColor.b = 0;
            }
            newColor.b += przesuniecieWartosci;
            newColor.b *= zakres;
            przesuniecieWartosci = 0;




            setPixel(x + szerokosc / 2, y, newColor.r, newColor.g, newColor.b);
        }
    }
    for(int i = 0; i < 32; i++)
    {
        paleta8k[i] = z8Kdo24K(i);
    }
    narysujPalete(0, 200, paleta8k);

}
void paletaNarzuconaDitteringSzary()
{
    int rozmiarTablicy{4};
    constexpr float zakres = 255 / 32.0; //5bit dla szarego
    int przesuniecieWartosci{0};
    zaktualizujTabliceBayera4_5bit();
    SDL_Color kolor, newColor;
    Uint8 szary5bit{};
    Uint8 szary8bit{};
    float nowySzary{};
    SDL_Color paleta8k[32];
    float wartoscWTablicy{};
    for(int y = 0; y < wysokosc / 2; y++)
    {
        for(int x = 0; x < szerokosc / 2; x++)
        {
            kolor=getPixel(x, y);
            szary8bit = (0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b); //konwertuj na szary8bit

            //nowySzary = z8Kdo24KSzarosci(szary5bit);
            nowySzary = szary8bit;
            //nowySzary = 255;
            wartoscWTablicy = zaktualizowanaTablicaBayera4[y%rozmiarTablicy][x%rozmiarTablicy];
            while(nowySzary > zakres)
            {
                przesuniecieWartosci++;
                nowySzary -= zakres;
            }

            if(nowySzary > wartoscWTablicy)
            {
                szary5bit = 1;
            }else
            {
                szary5bit = 0;
            }
            szary5bit += przesuniecieWartosci;
            szary5bit *= zakres;
            przesuniecieWartosci = 0;
            newColor = z8Kdo24KSzarosci(szary5bit * 31.0 / 255);
            setPixel(x + szerokosc / 2, y, newColor.r, newColor.g, newColor.b);
        }
    }
    for(int i = 0; i < 32; i++)
    {
        paleta8k[i] = z8Kdo24KSzarosci(i);
    }
    narysujPaleteSzarosci(0, 200, paleta8k);

}
