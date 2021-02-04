//---------------------------------------
// Projektowanie efektywnych algorytmów - Projekt
// Semestr zimowy 2020 - 2021
//---------------------------------------
// Zadanie projektowe 3
// Algorytmy ewolucyjne - GA
//---------------------------------------
// Miroslaw Kuzniar
// nr indeksu: 248870
//---------------------------------------

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>

#include "matrix.h"
#include "clock.h"
#include "algorytmGA.h"

using namespace std;

int ilosc_miast;
vector<int> macierz_sasiedztwa;

int main()
{
    char nazwa_pliku[15];

    cout << "-------------------------------------------------" << endl; //Sekcja informacyjna

    cout << " Projekt: Zadanie projektowe 3 \n Problem: Problem Komiwojazera (ATSP)" << endl;

    cout << "-------------------------------------------------" << endl; //Sekcja wczytania danych z pliku

    cout << " Wprowadz nazwe pliku: ";
    cin >> nazwa_pliku;

    fstream plik_odczyt;
    int liczba;

    plik_odczyt.open(nazwa_pliku, ios::in);

    if (plik_odczyt.good())
    {
        plik_odczyt >> ilosc_miast;

        for (int i = 0; i < ilosc_miast * ilosc_miast; i++)
        {
            plik_odczyt >> liczba;
            macierz_sasiedztwa.push_back(liczba);
        }
    }
    else
    {
        cout << "-------------------------------------------------" << endl;
        cout << " Blad pliku!" << endl;
        cout << "-------------------------------------------------" << endl;
        getchar(); getchar();
        exit(0);
    }
    plik_odczyt.close();

    cout << "-------------------------------------------------" << endl; //Sekcja wypisania macierzy

    wyswietlMacierz(ilosc_miast, macierz_sasiedztwa);

    cout << "-------------------------------------------------" << endl; //Sekcja sprawdzenia danych 

    sprawdzDane(ilosc_miast, macierz_sasiedztwa);

    cout << "-------------------------------------------------" << endl << endl; //Sekcja wykonania algorytmow 

    cout << "----------------------------------------------------------- " << endl; 

    for (;;) 
    {
        algorytmGA(ilosc_miast, macierz_sasiedztwa); // Algorytm genetyczny
    }

    cout << "-------------------------------------------------" << endl;

    getchar(); getchar();

    return 0;
}