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
int koszt_minimalny_DP;

int main()
{
    char nazwa_pliku[15];

    long long int frequency, start_DP, elapsed_DP, start_BF, elapsed_BF;
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

    cout << "-------------------------------------------------" << endl; //Sekcja informacyjna

    cout << " Problem komiwojazera (TSP)" << endl;

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
    plik_odczyt.close();

    cout << "-------------------------------------------------" << endl; //Sekcja wypisania macierzy

    wyswietlMacierz(ilosc_miast, macierz);

    cout << "-------------------------------------------------" << endl; //Sekcja sprawdzenia danych 

    sprawdzDane(ilosc_miast, macierz);
   
    cout << "-------------------------------------------------" << endl; //Sekcja wykonania algorytmu 
       
    start_DP = read_QPC(); 
    koszt_minimalny_DP = funkcja_rekurencyjna_DP(1 << 0, 0, ilosc_miast, macierz);
    elapsed_DP = read_QPC() - start_DP; 

    cout << " Koszt minimalny: " << koszt_minimalny_DP << endl;

    start_BF = read_QPC();
    generujPermutacje(ilosc_miast, macierz);
    elapsed_BF = read_QPC() - start_BF;

    wyswietlNajlepszaPermutacje();

    cout << endl << "-------------------------------------------------" << endl; //Sekcja pomiaru czasu

    cout << " DYNAMIC PROGRAMING " << endl << endl;
    cout << " Czas [s] = " << fixed << setprecision(3) << (float)elapsed_DP / frequency << endl;
    cout << " Czas [ms] = " << setprecision(0) << (1000.0 * elapsed_DP) / frequency << endl;
    cout << " Czas [us] = " << setprecision(0) << (1000000.0 * elapsed_DP) / frequency << endl;

    cout << "-------------------------------------------------" << endl;

    cout << " BRUTE FORCE " << endl << endl;
    cout << " Czas [s] = " << fixed << setprecision(3) << (float)elapsed_BF / frequency << endl;
    cout << " Czas [ms] = " << setprecision(0) << (1000.0 * elapsed_BF) / frequency << endl;
    cout << " Czas [us] = " << setprecision(0) << (1000000.0 * elapsed_BF) / frequency << endl;

    cout << "-------------------------------------------------" << endl; //Sekcja zapisu do pliku 

    fstream plik_zapis;
    plik_zapis.open("Wyniki.txt", ios::out | ios::app);

    plik_zapis << ilosc_miast << " " << int((1000000.0 * elapsed_DP) / frequency) << " " << int((1000000.0 * elapsed_BF) / frequency) << endl;

    plik_zapis.close();

    getchar(); getchar();

    return 0;
}

