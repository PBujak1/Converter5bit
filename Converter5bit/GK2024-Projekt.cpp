#include "GK2024-Zmienne.h"
#include "GK2024-Funkcje.h"
#include "GK2024-Paleta.h"
#include "GK2024-MedianCut.h"

#include <exception>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <dirent.h>
#include <vector>

using namespace std;

// Funkcja do wyświetlenia listy plików BMP w katalogu
vector<string> listBMPFiles(const string& directory) {
    vector<string> bmpFiles;
    DIR* dir = opendir(directory.c_str());
    if (dir == nullptr) {
        cerr << "Nie mozna otworzyc katalogu: " << directory << endl;
        return bmpFiles;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string fileName = entry->d_name;
        if (fileName.size() > 4 && fileName.substr(fileName.size() - 4) == ".bmp") {
            bmpFiles.push_back(directory + "/" + fileName);
        }
    }
    closedir(dir);
    return bmpFiles;
}

// Funkcja do wyświetlania opcji w konsoli
void displayOptions() {
    cout << "\nWybierz jedna z dostepnych opcji:\n";
    for (int i = 1; i <= 9; i++) {
        cout << i << ": Funkcja" << i << endl;
    }
    cout << "10: Zakoncz" << endl;
}

int main(int argc, char* argv[]) {
    string directory = "C:\\Users\\Piotr\\Desktop\\Studia\\3 Semestr\\GK\\Projekt\\GK2024-Projekt-Z23-05\\GK2024-Projekt";
    vector<string> bmpFiles = listBMPFiles(directory);

    if (bmpFiles.empty()) {
        cerr << "Brak plikow BMP w katalogu: " << directory << endl;
        return EXIT_FAILURE;
    }

    cout << "Dostepne pliki BMP w katalogu: " << directory << endl;
    for (size_t i = 0; i < bmpFiles.size(); i++) {
        cout << i + 1 << ": " << bmpFiles[i] << endl;
    }

    size_t fileChoice;
    cout << "\nWybierz numer pliku BMP do przetworzenia: ";
    cin >> fileChoice;

    if (fileChoice < 1 || fileChoice > bmpFiles.size()) {
        cerr << "Nieprawidlowy wybor." << endl;
        return EXIT_FAILURE;
    }

    string chosenFile = bmpFiles[fileChoice - 1];
    cout << "Wybrano plik: " << chosenFile << endl;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(tytul, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc * 2, wysokosc * 2, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_UpdateWindowSurface(window);

    bool done = false;
    SDL_Event event;

    // Ładujemy wybrany obraz
    ladujBMP(chosenFile.c_str(), 0, 0);

    // Główna pętla programu
    while (!done && SDL_WaitEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                else {
                    displayOptions();
                    int option;
                    cout << "Wybierz opcje: ";
                    cin >> option;
                    switch (option) {
                        case 1: Funkcja1(); break;
                        case 2: Funkcja2(); break;
                        case 3: Funkcja3(); break;
                        case 4: Funkcja4(); break;
                        case 5: Funkcja5(); break;
                        case 6: Funkcja6(); break;
                        case 7: Funkcja7(); break;
                        case 8: Funkcja8(); break;
                        case 9: Funkcja9(); break;
                        case 10: done = true; break;
                        default: cerr << "Nieprawidlowa opcja." << endl;
                    }
                }
                break;
        }
    }

    if (screen) {
        SDL_FreeSurface(screen);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}
