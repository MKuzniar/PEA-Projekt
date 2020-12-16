#include <iostream>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iomanip> 

#include "algorytmSA.h"

using namespace std;

int koszt_tymczasowy;
vector<int> permutacja_tymczasowa;

int koszt_najlepszy;
vector<int> permutacja_najlepsza;

int roznica_kosztow;
int rodzaj_sasiedztwa;

int delta;

void algorytmSA(int n, vector<int>& v)
{
    srand(time(NULL));

	long long int stan_czasu_start, stan_czasu_wykonanie;
    long long int start_SA, elapsed_SA;
    long long int frequency;

	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

    // Ustalenie warto�ci modyfikowalnych parametr�w algorytmu SA
    float czas_wykonania;

    float temperatura = 100; // T0 - temperatura pocz�tkowa. W przpadku zmiany T0 nale�y te� zakomentowa� linie 73 - 81
    float wspolczynnik_zmniejszania_temp = 0.99; // Geometryczny schemat ch�odzenia 
    float temperatura_minimalna = 0.001; // Tmin - temperatura minimalna (warunek stopu)

    int dlogosc_epoki = 1000; // D�ugo�� epoki
    int licznik = 0;

    // Czyszczenie wektor�w 
    permutacja_najlepsza.clear();
    permutacja_tymczasowa.clear();

    permutacja_najlepsza.resize(n + 1);
    permutacja_tymczasowa.resize(n + 1);

    // Wczytanie wartosci kryterium zatrzymania 
    cout << " Max czas wykonania [s]: ";
    cin >> czas_wykonania;

    // Wczytanie danych o rodzaju s�siedztwa
    cout << "-------------------------------------------------" << endl;
    cout << " | 1 - Swap | 2 - Invert | 3 - Insert |" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << " Rodzaj sasiedztwa: ";
    cin >> rodzaj_sasiedztwa;

    start_SA = read_QPC();

    // Generowanie losowego rozwi�zania pocz�tkowego i przyj�cie go jako rozwi�zanie najlepsze (tymczasowo)
    for (int i = 1; i < n; i++)
    {
        permutacja_najlepsza[i] = i;
    }
    random_shuffle(permutacja_najlepsza.begin() + 1, permutacja_najlepsza.end() - 1);
    koszt_najlepszy = obliczKosztPermutacji(n, permutacja_najlepsza, v);

    //Ustalenie warto�ci temperatury pocz�tkowej 
    delta = 0;

    for (int i = 0; i < 50; i++)
    {
        generacjaSasiedniejPermutacji(n, v);
        delta = delta + roznica_kosztow;
    }

    temperatura = static_cast<float>(abs((-(delta / 50)) / (-0.01005033)));

    stan_czasu_start = read_QPC();

    // P�tla zewn�trzna - zako�czona gdy spe�niony warunek stopu (czas lub temperatura)
    do
    {
        stan_czasu_wykonanie = read_QPC() - stan_czasu_start;  

        // P�tla wewn�trzna - osi�ganie stanu r�wnowagi (czas lub d�ugo�� epoki) - temperatura si� nie zmienia 
        while (((float)stan_czasu_wykonanie / frequency < czas_wykonania) && (licznik < dlogosc_epoki))
        {
            stan_czasu_wykonanie = read_QPC() - stan_czasu_start;

            generacjaSasiedniejPermutacji(n, v);
            koszt_tymczasowy = koszt_najlepszy + roznica_kosztow;

            // Przyj�cie rozwi�zania o ni�szym koszcie jako najlepsze
            if (koszt_tymczasowy < koszt_najlepszy)
            {
                koszt_najlepszy = koszt_tymczasowy;
                permutacja_najlepsza = permutacja_tymczasowa;
            }

            // Przyj�cie rozwi�zania o wy�szym koszcie jako najlepsze z pewnym prawdopodobienstwem (unikniecie 'utkniecia' w minimum lokalnym)
            else if (static_cast<float>(rand()) / RAND_MAX < exp(-(static_cast<float>((koszt_tymczasowy - koszt_najlepszy) / temperatura)))) 
            {
                koszt_najlepszy = koszt_tymczasowy;
                permutacja_najlepsza = permutacja_tymczasowa;
            }
            else
            {
                koszt_tymczasowy = koszt_tymczasowy - roznica_kosztow;
            }
            licznik++;
        }

        // Obni�enie temperatury i reset licznika d�ugo�ci epoki
        temperatura = temperatura * wspolczynnik_zmniejszania_temp;
        licznik = 0;
        
    } while (((float)stan_czasu_wykonanie / frequency < czas_wykonania) /*&& (temperatura > temperatura_minimalna)*/);

   elapsed_SA = read_QPC() - start_SA;
    
    // Wypisanie wynik�w
    cout << "-------------------------------------------------" << endl;
    cout << " Koszt otrzymany SA: " << koszt_najlepszy << endl;
    cout << "-------------------------------------------------" << endl;
    cout << " Czas [s] = " << fixed << setprecision(3) << (float)elapsed_SA / frequency << endl;
    cout << " Czas [ms] = " << setprecision(0) << (1000.0 * elapsed_SA) / frequency << endl;
    cout << " Czas [us] = " << setprecision(0) << (1000000.0 * elapsed_SA) / frequency << endl;
    cout << "-------------------------------------------------" << endl;
    cout << endl;
}

// Obliczenie kosztu rozwi�zania pocz�tkowego
int obliczKosztPermutacji(int n, vector<int>& permutacja, vector<int>& v)
{
    int koszt = 0;

    for (int i = 0; i < n; i++)
    {
        koszt = koszt + v[n * permutacja[i] + permutacja[i + 1]]; 
    }

    return koszt;
}

// Generowanie rozwi�zania z s�siedztwa i obliczenie r�nicy koszt�w mi�dzy nim a bazowym
void generacjaSasiedniejPermutacji(int n, vector<int>& v)
{
    int i = 0;
    int j = 0;

    permutacja_tymczasowa = permutacja_najlepsza;
    
    //Generowanie rozwi�zania s�siedniego w zale�no�ci od wybranego rodzaju s�siedztwa 

    if (rodzaj_sasiedztwa == 1) //S�siedztwo typu Swap - wykonanie ruchu typu Swap
    {
        // Generowanie losowych indeks�w 'i' i 'j' (gdzie 'i' != 'j' oraz 'i' < 'j') 
        do
        {
            i = (rand() % (n - 1)) + 1;
            j = (rand() % (n - 1)) + 1;
        } while (i == j || j < i);

        // Obliczenie r�nicy koszt�w mi�dzy rozwi�zaniami
        if (i + 1 == j)
        {
            roznica_kosztow = 0;

            // Usuni�cie po��czenia mi�dzy poprzednikiem a 'i', 'i' a 'j' oraz 'j' a nast�pnikiem
            roznica_kosztow = roznica_kosztow - v[n * permutacja_tymczasowa[i - 1] + permutacja_tymczasowa[i]];
            roznica_kosztow = roznica_kosztow - v[n * permutacja_tymczasowa[i] + permutacja_tymczasowa[j]];
            roznica_kosztow = roznica_kosztow - v[n * permutacja_tymczasowa[j] + permutacja_tymczasowa[j + 1]];

            // Dodanie po��czenia mi�dzy poprzednikiem 'i' a 'j', 'j' a 'i' oraz 'i' a nast�pnikiem 'j'
            roznica_kosztow = roznica_kosztow + v[n * permutacja_tymczasowa[i - 1] + permutacja_tymczasowa[j]];
            roznica_kosztow = roznica_kosztow + v[n * permutacja_tymczasowa[j] + permutacja_tymczasowa[i]];
            roznica_kosztow = roznica_kosztow + v[n * permutacja_tymczasowa[i] + permutacja_tymczasowa[j + 1]];
        }
        else
        {
            roznica_kosztow = 0;

            // Usuni�cie po��cznia mi�dzy poprzednikiem a 'i', 'i' a nast�pnikiem, poprzednikiem a 'j' oraz 'j' a nast�pnikiem
            roznica_kosztow = roznica_kosztow - v[n * permutacja_tymczasowa[i - 1] + permutacja_tymczasowa[i]];
            roznica_kosztow = roznica_kosztow - v[n * permutacja_tymczasowa[i] + permutacja_tymczasowa[i + 1]];
            roznica_kosztow = roznica_kosztow - v[n * permutacja_tymczasowa[j - 1] + permutacja_tymczasowa[j]];
            roznica_kosztow = roznica_kosztow - v[n * permutacja_tymczasowa[j] + permutacja_tymczasowa[j + 1]];

            // Dodanie po��cznia mi�dzy poprzednikiem 'i' a 'j', 'j' a nast�pnikiem 'i', poprzednikiem 'j' a 'i' oraz 'i' a nast�pnikiem 'j'
            roznica_kosztow = roznica_kosztow + v[n * permutacja_tymczasowa[i - 1] + permutacja_tymczasowa[j]];
            roznica_kosztow = roznica_kosztow + v[n * permutacja_tymczasowa[j] + permutacja_tymczasowa[i + 1]];
            roznica_kosztow = roznica_kosztow + v[n * permutacja_tymczasowa[j - 1] + permutacja_tymczasowa[i]];
            roznica_kosztow = roznica_kosztow + v[n * permutacja_tymczasowa[i] + permutacja_tymczasowa[j + 1]];

        }

        // Ruch Swap - zamiana element�w z pozycji i-tej i j-tej
        int tmp = permutacja_tymczasowa[j];
        permutacja_tymczasowa[j] = permutacja_tymczasowa[i];
        permutacja_tymczasowa[i] = tmp;
    }
    else if (rodzaj_sasiedztwa == 2) // S�siedztwo typu Invert - wykonanie ruchu typu Invert
    {
        // Generowanie losowych indeks�w 'i' i 'j' (gdzie 'i' != 'j' oraz 'i' < 'j') 
        do
        {
            i = (rand() % (n - 1)) + 1;
            j = (rand() % (n - 1)) + 1;
        } while (i == j || j < i);
        
        roznica_kosztow = 0;

        // Usuni�cie po��czenia mi�dzy poprzednikiem a 'i' oraz 'j' a nast�pnikiem
        roznica_kosztow = roznica_kosztow - v[n * permutacja_tymczasowa[i - 1] + permutacja_tymczasowa[i]] - v[n * permutacja_tymczasowa[j] + permutacja_tymczasowa[j + 1]];

        // Dodanie po��czenia mi�dzy poprzednikiem 'i' a 'j' oraz 'i' a nast�pnikiem 'j'
        roznica_kosztow = roznica_kosztow + v[n * permutacja_tymczasowa[i - 1] + permutacja_tymczasowa[j]] + v[n * permutacja_tymczasowa[i] + permutacja_tymczasowa[j + 1]];

        // (j-i) - krotne usuwanie i dodawanie po�acze� mi�dzy elementami permutacji
        for (int m = i; m < j; m++)
        {
            roznica_kosztow = roznica_kosztow - v[n * permutacja_tymczasowa[m] + permutacja_tymczasowa[m + 1]] + v[n * permutacja_tymczasowa[m + 1] + permutacja_tymczasowa[m]];
        }

        // Ruch Invert - odwr�cenie w permutacji ci�gu od i-tego do j-tego elementu
        reverse(permutacja_tymczasowa.begin() + i, permutacja_tymczasowa.begin() + j + 1);
    }
    else if (rodzaj_sasiedztwa == 3) // S�siedztwo typu Insert - wykonanie ruchu typu Insert
    {
        // Generowanie losowych indeks�w 'i' i 'j' (gdzie 'i' != 'j' oraz 'i' i 'j' nie s� swoimi nast�pnikami) 
        do
        {
            i = (rand() % (n - 1)) + 1;
            j = (rand() % (n - 1)) + 1;
        } while (i == j - 1 || i == j || i == j + 1);

        roznica_kosztow = 0;

        // Usuni�cie po��cznia mi�dzy 'i' a nast�pnikiem, poprzednikiem a 'j' oraz poprzednikiem a 'i'
        roznica_kosztow = roznica_kosztow - v[n * permutacja_tymczasowa[i] + permutacja_tymczasowa[i + 1]];
        roznica_kosztow = roznica_kosztow - v[n * permutacja_tymczasowa[j - 1] + permutacja_tymczasowa[j]];
        roznica_kosztow = roznica_kosztow - v[n * permutacja_tymczasowa[i - 1] + permutacja_tymczasowa[i]];

        // Dodanie po��cznia mi�dzy poprzednikiem a 'i', 'i' a nast�pnikiem, poprzednikiem a 'j' oraz 'j' a nast�pnikiem
        roznica_kosztow = roznica_kosztow + v[n * permutacja_tymczasowa[i - 1] + permutacja_tymczasowa[i + 1]];
        roznica_kosztow = roznica_kosztow + v[n * permutacja_tymczasowa[j - 1] + permutacja_tymczasowa[i]];
        roznica_kosztow = roznica_kosztow + v[n * permutacja_tymczasowa[i] + permutacja_tymczasowa[j]];

        // Ruch Insert - usuni�cie elementu z pozycji i-tej i wsawienie go na pozycj� j-t� 
        permutacja_tymczasowa.insert(permutacja_tymczasowa.begin() + j, permutacja_tymczasowa[i]);

        if (j > i)
        {
            // Element przechodzi na pozycj� o wi�kszym indeksie - (i)
            permutacja_tymczasowa.erase(permutacja_tymczasowa.begin() + i);
        }
        else
        {
            // Element przechodzi na pozycj� o mniejszym indeksie - (i + 1)
            permutacja_tymczasowa.erase(permutacja_tymczasowa.begin() + i + 1);
        }
    }
}