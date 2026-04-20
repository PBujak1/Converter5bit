// funkcje do operacji na plikach
#include "GK2024-Funkcje.h"
#include "GK2024-Zmienne.h"
#include "GK2024-Paleta.h"
#include "GK2024-MedianCut.h"
#include "GK2024-Pliki.h"


void zapiszPlikv0() {
    SDL_Color kolor;
    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;
    Uint8 ileBitow = 5;

    cout<<"Zapisujemy plik 'obraz.bin' uzywajac operatora <<"<<endl;
    ofstream wyjscie("obraz.bin");

    wyjscie<<"DG";
    wyjscie<<(Uint8)(szerokoscObrazka)<<(Uint8)(szerokoscObrazka>>5);
    wyjscie<<(Uint8)(wysokoscObrazka)<<(Uint8)(wysokoscObrazka>>5);
    wyjscie<<ileBitow;

    for (int y=0; y<wysokoscObrazka; y++) {
        for (int x=0; x<szerokoscObrazka; x++) {
            kolor = getPixel(x, y);
            wyjscie<<kolor.r<<kolor.g<<kolor.b;
        }
    }

    wyjscie.close();
    SDL_UpdateWindowSurface(window);
}

void zapiszPlik() {

    SDL_Color kolor;
    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;
    Uint8 ileBitow = 5;
    char identyfikator[] = "DG";

    cout<<"Zapisujemy plik 'obrazRGB.bin' uzywajac metody write()"<<endl;
    ofstream wyjscie("obrazRGB.bin", ios::binary);
    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&ileBitow, sizeof(Uint8));

    for (int y=0; y<wysokoscObrazka; y++) {
        for (int x=0; x<szerokoscObrazka; x++) {
            kolor = getPixel(x,y);
            wyjscie.write((char*)&kolor, sizeof(Uint8)*3);
            // wyjscie.write((char*)&kolor.r, sizeof(Uint8));
            // wyjscie.write((char*)&kolor.g, sizeof(Uint8));
            // wyjscie.write((char*)&kolor.b, sizeof(Uint8));
        }
    }

    wyjscie.close();
    SDL_UpdateWindowSurface(window);
}

void odczytajPlik() {
    SDL_Color kolor;
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    Uint8 ileBitow = 0;
    char identyfikator[] = " ";

    cout<<"Odczytujemy plik 'obrazRGB.bin' uzywajac metody read()"<<endl;
    ifstream wejscie("obrazRGB.bin", ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&ileBitow, sizeof(Uint8));

    cout<<"id: "<<identyfikator<<endl;
    cout<<"szerokosc: "<<szerokoscObrazka<<endl;
    cout<<"wysokosc: "<<wysokoscObrazka<<endl;
    cout<<"ile bitow: "<<(int)ileBitow<<endl;

    for (int y=0; y<wysokoscObrazka; y++) {
        for (int x=0; x<szerokoscObrazka; x++) {
            wejscie.read((char*)&kolor, sizeof(Uint8)*3);
            setPixel(x+(szerokosc/2), y, kolor.r, kolor.g, kolor.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void zapiszPlik8() {
    SDL_Color kolor;
    Uint8 kolor8bit;
    Uint16 szerokoscObrazka = szerokosc / 2;
    Uint16 wysokoscObrazka = wysokosc / 2;
    Uint8 ileBitow = 5;
    char identyfikator[] = "DG";

    cout << "Zapisujemy plik 'obraz8.bin' uzywajac metody write()" << endl;
    ofstream wyjscie("obraz8.bin", ios::binary);
    wyjscie.write((char*)&identyfikator, sizeof(char) * 2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&ileBitow, sizeof(Uint8));

    int x = 0, y = 0;

    while (y < wysokoscObrazka) {
        if (x < 319 && y < 66) {
            kolor = getPixel(x, y);
            kolor8bit = z24Kdo8K(kolor);
            wyjscie.write((char*)&kolor8bit, sizeof(Uint8));
            x++;
        } else if (x == 319 && y < 66) {
            kolor = getPixel(x, y);
            kolor8bit = z24Kdo8K(kolor);
            wyjscie.write((char*)&kolor8bit, sizeof(Uint8));
            x = 0;
            y++;
        } else if (y >= 66 && y < 132) {
            kolor = getPixel(x, y);
            kolor8bit = z24Kdo8K(kolor);
            wyjscie.write((char*)&kolor8bit, sizeof(Uint8));
            x++;
            if (x >= szerokoscObrazka) {
                x = 0;
                y++;
            }
        } else if (y >= 132 && y < wysokoscObrazka) {
            kolor = getPixel(x, y);
            kolor8bit = z24Kdo8K(kolor);
            wyjscie.write((char*)&kolor8bit, sizeof(Uint8));
            x++;
            if (x >= szerokoscObrazka) {
                x = 0;
                y++;
            }
        }
    }

    wyjscie.close();
    SDL_UpdateWindowSurface(window);
}

void odczytajPlik8() {
    SDL_Color kolor;
    Uint8 kolor8bit = 0;
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    Uint8 ileBitow = 0;
    char identyfikator[] = " ";

    cout << "Odczytujemy plik 'obraz8.bin' uzywajac metody read()" << endl;
    ifstream wejscie("obraz8.bin", ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char) * 2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&ileBitow, sizeof(Uint8));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokoscObrazka << endl;
    cout << "wysokosc: " << wysokoscObrazka << endl;
    cout << "ile bitow: " << (int)ileBitow << endl;

    int x = 0, y = 0;

    while (y < wysokoscObrazka) {
        if (x < 319 && y < 66) {
            wejscie.read((char*)&kolor8bit, sizeof(Uint8));
            kolor = z8Kdo24K(kolor8bit);
            setPixel(x + szerokoscObrazka, y, kolor.r, kolor.g, kolor.b);
            x++;
        } else if (x == 319 && y < 66) {
            wejscie.read((char*)&kolor8bit, sizeof(Uint8));
            kolor = z8Kdo24K(kolor8bit);
            setPixel(x + szerokoscObrazka, y, kolor.r, kolor.g, kolor.b);
            x = 0;
            y++;
        } else if (y >= 66 && y < 132) {
            wejscie.read((char*)&kolor8bit, sizeof(Uint8));
            kolor = z8Kdo24K(kolor8bit);
            setPixel(x + szerokoscObrazka, y, kolor.r, kolor.g, kolor.b);
            x++;
            if (x >= szerokoscObrazka) {
                x = 0;
                y++;
            }
        } else if (y >= 132 && y < wysokoscObrazka) {
            wejscie.read((char*)&kolor8bit, sizeof(Uint8));
            kolor = z8Kdo24K(kolor8bit);
            setPixel(x + szerokoscObrazka, y, kolor.r, kolor.g, kolor.b);
            x++;
            if (x >= szerokoscObrazka) {
                x = 0;
                y++;
            }
        }
    }

    SDL_UpdateWindowSurface(window);
}
