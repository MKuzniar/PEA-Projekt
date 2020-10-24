//---------------------------------------
//Projektowanie efektywnych algorytmów - Projekt
//Semestr zimowy 2020 - 2021
//---------------------------------------
//Zadanie projektowe 1
//Implementacja i analiza efektywnosci
//algorytmu Programowania Dynamicznego (DP)
//dla Problemu Komiwojazera (TSP)
//---------------------------------------
//Miroslaw Kuzniar
//nr indeksu: 248870
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
#include "algorytmDP.h"
#include "algorytmBF.h"

using namespace std;

int ilosc_miast;
vector<int> macierz;
int koszt_minimalny;

int main()
{
    char nazwa_pliku[15];

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

    cout << "-------------------------------------------------" << endl; //Sekcja informacyjna

    cout << " Probelm: Problem komiwojazera (TSP)" << endl;
    cout << " Algorytm: Programowanie dynamiczne (DP)" << endl;

    cout << "-------------------------------------------------" << endl; //Sekcja wczytania danych z pliku
   
    cout << " Wprowadz nazwe pliku: ";
    cin >> nazwa_pliku;

    fstream plik;
    int liczba;

    plik.open(nazwa_pliku, ios::in);

    if (plik.good())
    {
        plik >> ilosc_miast;

        for (int i = 0; i < ilosc_miast * ilosc_miast; i++)
        {
            plik >> liczba;
            macierz.push_back(liczba);
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
    plik.close();

    cout << "-------------------------------------------------" << endl; //Sekcja wypisania macierzy

    wyswietlMacierz(ilosc_miast, macierz);

    cout << "-------------------------------------------------" << endl; //Sekcja sprawdzenia danych 

    sprawdzDane(ilosc_miast, macierz);
   
    cout << "-------------------------------------------------" << endl; //Sekcja wykonania algorytmu 

    start = read_QPC(); // <- czas START
    koszt_minimalny = funkcja_rekurencyjna_DP(1 << 0, 0, ilosc_miast, macierz);
    cout << " Koszt minimalny: " << koszt_minimalny << endl;
    elapsed = read_QPC() - start; // <- czas STOP

    cout << "-------------------------------------------------" << endl; //Sekcja pomiaru czasu
   
    cout << " Czas [s] = " << fixed << setprecision(3) << (float)elapsed / frequency << endl;
    cout << " Czas [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
    cout << " Czas [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;

    cout << "-------------------------------------------------" << endl;

    generujPermutacje(ilosc_miast, macierz, koszt_minimalny);

    cout << "-------------------------------------------------" << endl;

    getchar(); getchar();

    return 0;
}

