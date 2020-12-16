#include <iostream>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iomanip> 

#include "algorytmTS.h"

using namespace std;

vector<int> najlepsza_permutacja;
int koszt_najlepszej_permutacji;

vector<int> tymczasowa_permutacja;
int koszt_tymczasowej_permutacji;

vector<int> najlepsza_w_sasiedztwie_permutacja;
int koszt_najlepszej_w_sasiedztwie_permutacji;

int kosztow_roznica;

// G³ówna funkcja algorytmu
void algorytmTS(int n, vector<int>& v)
{
	srand(time(NULL));

	long long int stan_czasu_start, stan_czasu_wykonanie;
	long long int start_TS, elapsed_TS;
	long long int frequency;

	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	// Ustalenie wartoœci parametrów algorytmu TS
	float czas_wykonania; 

	vector<int> tablica_tabu;
	int kadencja = (n * 2) / 5; // Kadencja 

	int ilosc_iteracji_bez_poprawy = 10000; // Warunek stopu - iloœæ iteracji bez poprawy najlepszego rozwi¹zania
	int licznik_braku_poprawy = 0;

	int i = 0;
	int j = 0;
	int i_najlepsze = 0; // Indeks 'i' wstawiany do tablicy tabu
	int j_najlepsze = 0; // Indeks 'j' wstawiany do tablicy tabu

	bool czy_to_pierwsza_permutacja = true; // Zmienna dla permutacji najlepszej w s¹siedztwie 

	// Czyszczenie wektorów i kosztów permutacji
	najlepsza_permutacja.clear();
	koszt_najlepszej_permutacji = 0;

	tymczasowa_permutacja.clear();
	koszt_tymczasowej_permutacji = 0;

	najlepsza_w_sasiedztwie_permutacja.clear();
	koszt_najlepszej_w_sasiedztwie_permutacji = 0;

	tablica_tabu.clear();

	najlepsza_permutacja.resize(n + 1);
	tymczasowa_permutacja.resize(n + 1);
	najlepsza_w_sasiedztwie_permutacja.resize(n + 1);

	tablica_tabu.resize(n * n);

	// Wczytanie wartoœci kryterium zatrzymania - maksymalnego czasu pracy
	cout << " Max czas wykonania [s]: ";
	cin >> czas_wykonania;

	start_TS = read_QPC();

	// Generowanie losowego rozwi¹zania pocz¹tkowego
	for (int i = 1; i < n; i++)
	{
		tymczasowa_permutacja[i] = i;
	}
	random_shuffle(tymczasowa_permutacja.begin() + 1, tymczasowa_permutacja.end() - 1);
	koszt_tymczasowej_permutacji = obliczKosztPermutacjiPoczatkowej(n, tymczasowa_permutacja, v);

	// Przyjêcie rozwi¹zania losowego jako najlepsze (tymczasowo)
	najlepsza_permutacja = tymczasowa_permutacja;
	koszt_najlepszej_permutacji = koszt_tymczasowej_permutacji;

	stan_czasu_start = read_QPC();

	// Pêtla g³ówna - przerywana przez czas lub iloœæ iteracji bez poprawy
	do
	{
		stan_czasu_wykonanie = read_QPC() - stan_czasu_start;
		i_najlepsze = 0; 
		j_najlepsze = 0;

		// Pêtle przegl¹daj¹ce s¹siedztwo i wybieraj¹ce najlepsze rozwi¹zanie s¹siednie
		for (i = 1; i < n; i++)
		{
			for (j = i + 1; j < n; j++)
			{
				// S¹siedztwo typu Swap - wykonanaie ruchu typu Swap
				if (i + 1 == j)
				{
					kosztow_roznica = 0;

					// Usuniêcie po³¹czenia miêdzy poprzednikiem a 'i', 'i' a 'j' oraz 'j' a nastêpnikiem
					kosztow_roznica = kosztow_roznica - v[n * tymczasowa_permutacja[i - 1] + tymczasowa_permutacja[i]];
					kosztow_roznica = kosztow_roznica - v[n * tymczasowa_permutacja[i] + tymczasowa_permutacja[j]];
					kosztow_roznica = kosztow_roznica - v[n * tymczasowa_permutacja[j] + tymczasowa_permutacja[j + 1]];

					// Dodanie po³¹czenia miêdzy poprzednikiem 'i' a 'j', 'j' a 'i' oraz 'i' a nastêpnikiem 'j'
					kosztow_roznica = kosztow_roznica + v[n * tymczasowa_permutacja[i - 1] + tymczasowa_permutacja[j]];
					kosztow_roznica = kosztow_roznica + v[n * tymczasowa_permutacja[j] + tymczasowa_permutacja[i]];
					kosztow_roznica = kosztow_roznica + v[n * tymczasowa_permutacja[i] + tymczasowa_permutacja[j + 1]];
				}
				else
				{
					kosztow_roznica = 0;

					// Usuniêcie po³¹cznia miêdzy poprzednikiem a 'i', 'i' a nastêpnikiem, poprzednikiem a 'j' oraz 'j' a nastêpnikiem
					kosztow_roznica = kosztow_roznica - v[n * tymczasowa_permutacja[i - 1] + tymczasowa_permutacja[i]];
					kosztow_roznica = kosztow_roznica - v[n * tymczasowa_permutacja[i] + tymczasowa_permutacja[i + 1]];
					kosztow_roznica = kosztow_roznica - v[n * tymczasowa_permutacja[j - 1] + tymczasowa_permutacja[j]];
					kosztow_roznica = kosztow_roznica - v[n * tymczasowa_permutacja[j] + tymczasowa_permutacja[j + 1]];

					// Dodanie po³¹cznia miêdzy poprzednikiem 'i' a 'j', 'j' a nastêpnikiem 'i', poprzednikiem 'j' a 'i' oraz 'i' a nastêpnikiem 'j'
					kosztow_roznica = kosztow_roznica + v[n * tymczasowa_permutacja[i - 1] + tymczasowa_permutacja[j]];
					kosztow_roznica = kosztow_roznica + v[n * tymczasowa_permutacja[j] + tymczasowa_permutacja[i + 1]];
					kosztow_roznica = kosztow_roznica + v[n * tymczasowa_permutacja[j - 1] + tymczasowa_permutacja[i]];
					kosztow_roznica = kosztow_roznica + v[n * tymczasowa_permutacja[i] + tymczasowa_permutacja[j + 1]];
				}

				// Ruch Swap - zamiana elementów z pozycji i-tej i j-tej
				int tmp = tymczasowa_permutacja[j];
				tymczasowa_permutacja[j] = tymczasowa_permutacja[i];
				tymczasowa_permutacja[i] = tmp;

				koszt_tymczasowej_permutacji = koszt_tymczasowej_permutacji + kosztow_roznica;

				// Ruch nie znajdujê siê w tablicy tabu (nie jest zakazany)
				if (tablica_tabu[n * i + j] == 0)
				{
					if (czy_to_pierwsza_permutacja == true)
					{
						koszt_najlepszej_w_sasiedztwie_permutacji = koszt_tymczasowej_permutacji;
						najlepsza_w_sasiedztwie_permutacja = tymczasowa_permutacja;

						i_najlepsze = i;
						j_najlepsze = j;

						czy_to_pierwsza_permutacja = false;
					}
					else
					{
						if (koszt_tymczasowej_permutacji < koszt_najlepszej_w_sasiedztwie_permutacji)
						{
							koszt_najlepszej_w_sasiedztwie_permutacji = koszt_tymczasowej_permutacji;
							najlepsza_w_sasiedztwie_permutacja = tymczasowa_permutacja;

							i_najlepsze = i;
							j_najlepsze = j;
						}
					}
				}

				// Ruch znajdujê siê w tablicy tabu (jest zakazany) ale spe³nia kryterium aspiracji 
				else if (koszt_tymczasowej_permutacji < koszt_najlepszej_permutacji)
				{
					if (czy_to_pierwsza_permutacja == true)
					{
						koszt_najlepszej_w_sasiedztwie_permutacji = koszt_tymczasowej_permutacji;
						najlepsza_w_sasiedztwie_permutacja = tymczasowa_permutacja;

						i_najlepsze = i;
						j_najlepsze = j;

						czy_to_pierwsza_permutacja = false;
					}
					else
					{
						if (koszt_tymczasowej_permutacji < koszt_najlepszej_w_sasiedztwie_permutacji)
						{
							koszt_najlepszej_w_sasiedztwie_permutacji = koszt_tymczasowej_permutacji;
							najlepsza_w_sasiedztwie_permutacja = tymczasowa_permutacja;

							i_najlepsze = i;
							j_najlepsze = j;
						}
					}
				}
			}
		}

		czy_to_pierwsza_permutacja = true;

		licznik_braku_poprawy++;

		tymczasowa_permutacja = najlepsza_w_sasiedztwie_permutacja;
		koszt_tymczasowej_permutacji = koszt_najlepszej_w_sasiedztwie_permutacji;

		// Sprawdzenie czy permutacja najlpesza w s¹siedztwie ma mniejszy koszt ni¿ permutacja najlepsza
		if (koszt_tymczasowej_permutacji < koszt_najlepszej_permutacji)
		{
			koszt_najlepszej_permutacji = koszt_tymczasowej_permutacji;
			najlepsza_permutacja = tymczasowa_permutacja;

			licznik_braku_poprawy = 0;
		}

		// Dekrementacja zawartoœci tablicy tabu
		for (int i = 0; i < n * n; i++)
		{
			if (tablica_tabu[i] != 0)
			{
				tablica_tabu[i]--;
			}
		}

		// Dodanie do tablicy tabu wykonanego ruchu 
		tablica_tabu[n * i_najlepsze + j_najlepsze] = kadencja;

	} while (((float)stan_czasu_wykonanie / frequency < czas_wykonania) /*&& (licznik_braku_poprawy < ilosc_iteracji_bez_poprawy)*/);

	elapsed_TS = read_QPC() - start_TS;

	// Wypisanie wyników
	cout << "-------------------------------------------------" << endl;
	cout << " Koszt otrzymany TS: " << koszt_najlepszej_permutacji << endl;
	cout << "-------------------------------------------------" << endl;
	cout << " Czas [s] = " << fixed << setprecision(3) << (float)elapsed_TS / frequency << endl;
	cout << " Czas [ms] = " << setprecision(0) << (1000.0 * elapsed_TS) / frequency << endl;
	cout << " Czas [us] = " << setprecision(0) << (1000000.0 * elapsed_TS) / frequency << endl;
	cout << "-------------------------------------------------" << endl;
	cout << endl;
}

// Obliczenie kosztu rozwiazania poczatkowego 
int obliczKosztPermutacjiPoczatkowej(int n, vector<int>& permutacja, vector<int>& v)
{
	int koszt = 0;

	for (int i = 0; i < n; i++)
	{
		koszt = koszt + v[n * permutacja[i] + permutacja[i + 1]];
	}

	return koszt;
}