// metody do algorytmu kwantyzacji (MedianCut)
#include "GK2024-MedianCut.h"
#include "GK2024-Zmienne.h"
#include "GK2024-Funkcje.h"
#include "GK2024-Paleta.h"
using namespace std;

void paletaMedianCutBW()
{
    ileKubelkow = 0;
    ileKolorow = 0;
    czyscPalete();
    SDL_Color kolor;
    int szary{};
    int numer{};
    int index{};
    for(int y = 0; y < wysokosc / 2; y++)
    {
        for(int x = 0; x < szerokosc / 2; x++)
        {
            kolor=getPixel(x, y);
            szary = (0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b); //konwertuj na szary8bit
            obrazekSzarosc[numer] = szary;
            setPixel(x + szerokosc / 2, y, szary, szary, szary);
            numer++;
        }
    }
    sortujKubelekBW(0, numer); //dla szarosci sortujemy tylko 1 raz
    medianCutBW(0, numer - 1, 5); //5 iteracji dla 5 bitow

    for(int y = 0; y < wysokosc / 2; y++)
    {
        for(int x = 0; x < szerokosc / 2; x++)
        {
            szary=getPixel(x + szerokosc / 2, y).r;
            index = znajdzSasiadaBW(szary);
            obrazekSzarosc[numer] = szary;
            setPixel(x + szerokosc / 2, y + wysokosc / 2, paleta8s[index].r, paleta8s[index].g, paleta8s[index].b);
        }
        narysujPaleteSzarosci(0, 200, paleta8s);
    }
}

void medianCutBW(int start, int koniec, int iteracja)
{
    for(int i = 0; i < iteracja; i++)
    {
        cout << "   ";
    }
    cout << "start: " << start << ", koniec: " << koniec << ", iteracja: " << iteracja << endl;
    if(iteracja > 0)
    {
        for(int i = 0; i < iteracja; i++)
        {
            cout << "   ";
        }
        cout << "Dzielimy kubelek na poziomie " << iteracja << endl;
        int srodek = (start + koniec + 1) / 2;
        medianCutBW(start, srodek - 1, iteracja - 1);
        medianCutBW(srodek, koniec, iteracja - 1);
    }else
    {
        int sumaBW{};
        for(int i = start; i <= koniec; i++)
        {
            sumaBW += obrazekSzarosc[i];
        }
        Uint8 noweBW = sumaBW / (koniec + 1 - start);
        SDL_Color nowyKolor = {noweBW, noweBW, noweBW};
        paleta8s[ileKubelkow] = nowyKolor;
        cout << "kubelek " << ileKubelkow << ": ";
        cout << "(s:" << start << ", k:" << koniec << ", e:" << (koniec + 1 - start) << ")" << endl;
        cout << "kolor " << ileKubelkow << ":(" << (int)nowyKolor.r << ", " << (int)nowyKolor.g << ", " << (int)nowyKolor.b << ")" << endl;
        ileKubelkow++;
    }
}

void sortujKubelekBW(int start, int koniec)
{
    int minimum{};
    for(int i = start; i <= koniec; i++)
    {
        minimum = i;
        for(int j = i; j <= koniec; j++)
        {
            if(obrazekSzarosc[j] < obrazekSzarosc[minimum])
            {
                minimum = j;
            }
        }
        swap(obrazekSzarosc[i], obrazekSzarosc[minimum]);
    }
}

int znajdzSasiadaBW(Uint8 wartosc)
{
    int minimum{999};
    int indexMin{0};
    int odleglosc{};
    for(int i = 0; i < 32; i++) //5bit
    {
        odleglosc = abs(wartosc - paleta8s[i].r);
        if(odleglosc < minimum)
        {
            minimum = odleglosc;
            indexMin = i;
        }
    }
    return indexMin;
}
void paletaMedianCutKolor()
{
    ileKubelkow = 0;
    ileKolorow = 0;
    czyscPalete();
    SDL_Color kolor;
    int szary{};
    int numer{};
    int index{};
    for(int y = 0; y < wysokosc / 2; y++)
    {
        for(int x = 0; x < szerokosc / 2; x++)
        {
            kolor=getPixel(x, y);
            obrazekKolor[numer] = {kolor.r, kolor.g, kolor.b};
            setPixel(x + szerokosc / 2, y, obrazekKolor[numer].r, obrazekKolor[numer].g, obrazekKolor[numer].b);
            numer++;
        }
    }
    sortujKubelek(0, numer, najwiekszaRoznica(0, numer)); //pierwsze sortowanie
    medianCutKolor(0, numer - 1, 5); //5 iteracji dla 5 bitow

    numer = 0;
        for(int y = 0; y < wysokosc / 2; y++)
    {
        for(int x = 0; x < szerokosc / 2; x++)
        {
            kolor = getPixel(x, y);
            index = znajdzSasiada(kolor);
            setPixel(x + szerokosc / 2, y + wysokosc / 2, paleta8k[index].r, paleta8k[index].g, paleta8k[index].b);
        }
    }
    narysujPalete(0, 200, paleta8k);
}

void medianCutKolor(int start, int koniec, int iteracja)
{
    for(int i = 0; i < iteracja; i++)
    {
        cout << "   ";
    }
    cout << "start: " << start << ", koniec: " << koniec << ", iteracja: " << iteracja << endl;
    if(iteracja > 0)
    {
        Uint8 sortowanie = najwiekszaRoznica(start, koniec);
        sortujKubelek(start, koniec, sortowanie);
        for(int i = 0; i < iteracja; i++)
        {
            cout << "   ";
        }
        cout << "Dzielimy kubelek na poziomie " << iteracja << endl;
        int srodek = (start + koniec + 1) / 2;
        medianCutKolor(start, srodek - 1, iteracja - 1);
        medianCutKolor(srodek, koniec, iteracja - 1);
    }else
    {
        int sumaR{};
        int sumaG{};
        int sumaB{};
        for(int i = start; i <= koniec; i++)
        {
            sumaR += obrazekKolor[i].r;
            sumaG += obrazekKolor[i].g;
            sumaB += obrazekKolor[i].b;
        }
        int sredniaR = sumaR / (koniec + 1 - start);
        int sredniaG = sumaG / (koniec + 1 - start);
        int sredniaB = sumaB / (koniec + 1 - start);
        SDL_Color nowyKolor = {sredniaR, sredniaG, sredniaB};
        paleta8k[ileKubelkow] = nowyKolor;
        cout << "kubelek " << ileKubelkow << ": ";
        cout << "(s:" << start << ", k:" << koniec << ", e:" << (koniec + 1 - start) << ")" << endl;
        cout << "kolor " << ileKubelkow << ":(" << (int)nowyKolor.r << ", " << (int)nowyKolor.g << ", " << (int)nowyKolor.b << ")" << endl;
        ileKubelkow++;
    }
}

Uint8 najwiekszaRoznica(int start, int koniec)
{
    int minR = start;
    int minG = start;
    int minB = start;
    int maxR = start;
    int maxG = start;
    int maxB = start;
    Uint8 roznica{};
    for(int i = start; i <= koniec; i++)
    {
        if(obrazekKolor[i].r < obrazekKolor[minR].r)
        {
            minR = i;
        }
        if(obrazekKolor[i].g < obrazekKolor[minG].g)
        {
            minG = i;
        }
        if(obrazekKolor[i].b < obrazekKolor[minB].b)
        {
            minB = i;
        }
        if(obrazekKolor[i].r > obrazekKolor[maxR].r)
        {
            maxR = i;
        }
        if(obrazekKolor[i].g > obrazekKolor[maxG].g)
        {
            maxG = i;
        }
        if(obrazekKolor[i].b > obrazekKolor[maxB].b)
        {
            maxB = i;
        }
    }
    int roznicaR = obrazekKolor[maxR].r - obrazekKolor[minR].r;
    int roznicaG = obrazekKolor[maxG].g - obrazekKolor[minG].g;
    int roznicaB = obrazekKolor[maxB].b - obrazekKolor[minB].b;
    cout << "roznice: (R:" << roznicaR << ", G:" << roznicaG << ", B:" << roznicaB << ")" << endl;
    int rozmicaM = max(max(roznicaB, roznicaG), roznicaR);
    if(rozmicaM == roznicaR)
    {
        roznica = 1;
    }else if(rozmicaM == roznicaG)
    {
        roznica = 2;
    }else
    {
        roznica = 3;
    }
    return roznica;
}

void sortujKubelek(int start, int koniec, Uint8 sortowanie)
{
    int minimum{};
    for(int i = start; i <= koniec; i++)
    {
        minimum = i;
        for(int j = i; j <= koniec; j++)
        {
            switch(sortowanie)
            {
            case 1:
                if(obrazekKolor[j].r < obrazekKolor[minimum].r)
                {
                    minimum = j;
                }
                break;
            case 2:
                if(obrazekKolor[j].g < obrazekKolor[minimum].g)
                {
                    minimum = j;
                }
                break;
            case 3:
                if(obrazekKolor[j].b < obrazekKolor[minimum].b)
                {
                    minimum = j;
                }
                break;
            }
        }
        swap(obrazekKolor[i], obrazekKolor[minimum]);
    }

}

int znajdzSasiada(SDL_Color kolor)
{
    int minimum{99999};
    int indexMin;
    SDL_Color kolorPaleta;
    float odleglosc;


    for(int i = 0; i < 32; i++) //5bit
    {
        kolorPaleta = paleta8k[i];
        odleglosc = sqrt((kolor.r - kolorPaleta.r)*(kolor.r - kolorPaleta.r) +
                         (kolor.g - kolorPaleta.g)*(kolor.g - kolorPaleta.g) +
                         (kolor.b - kolorPaleta.b)*(kolor.b - kolorPaleta.b));
        if(odleglosc < minimum)
        {
            minimum = odleglosc;
            indexMin = i;
        }
    }
    return indexMin;

}
