#include <iostream>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iomanip> 
#include <random>

#include "algorytmGA.h"

vector<int> rodzic_1;
vector<int> rodzic_2;

vector<int> potomek_1;
int koszt_potomka_1;

vector<int> potomek_2;
int koszt_potomka_2;

vector<int> permutacja_najlepsza;
int koszt_permutacji_najlepszej;

vector<int> permutacja_pomocnicza;
int koszt_permutacji_pomocniczej;

struct osobnik
{
	vector<int> chromosom;		// Permutacja miast 
	int wartosc_przystosowania; // Koszt permutacji 
};

vector<osobnik> populacja_poczatkowa;
vector<osobnik> populacja_chwilowa;
vector<osobnik> populacja;

// Funkcja pomocnicza do posortowania osobników populacji
bool sortujPoWartosciachPrzystosowania(const osobnik& a, const osobnik& b)
{
	return a.wartosc_przystosowania < b.wartosc_przystosowania;
}

// G³owna funkcja programu 
void algorytmGA(int n, vector<int>& v)
{
	long long int stan_czasu_start, stan_czasu_wykonanie;
	long long int frequency;

	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	
	// Parametry algorytmu genetycznego 
	float czas_wykonania;		// Czas wykonania (podawany z konsoli)
	int rodzaj_mutacji;			// Rodzaj operatora mutacji (podawany z konsoli)
	int lokalna_optymalizacja;	// Uruchomienie lokalnej optymalizacji (podawany z konsoli) 

	int rozmiar_populacji = 100;		 // Rozmiar populacji 
	int ilosc_osobnikow_elitarnych = 10; // Iloœæ osobników elitarnych przenoszonych do nowej populacji 

	float pp_krzyzowania = 0.8; // Prawdopodobienstwo krzyzowania
	float pp_mutacji = 0.1;	// Prawdopodobienstwo mutacji 

	// Generowanie liczb pseudolosowych 
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<> losuj_rodzicow(0, rozmiar_populacji - 1); // Wielkoœæ populacji - (0, rozmiar_populacji - 1)
	uniform_int_distribution<> losuj_sekcje_dopasowania(0, n - 2);		 // D³ugoœæ permutacji - (0, n - 2)
	uniform_real_distribution<> losuj_prawdopodobienstwo(0, 1);			 // Prawdopodobieñstwo - (0, 1)

	// Elementy lokalnej optymalizacji
	vector<int> permutacja_w_sasiedztwie_potomka_1;
	int koszt_permutacji_w_sasiedztwie_potomka_1;

	vector<int> permutacja_najlpesza_w_sasiedztwie_potomka_1;
	int kosz_permutacji_najlepszej_w_sasiedztwie_potomka_1;

	// Czyszczenie elementów algorytmu 
	populacja_poczatkowa.clear();
	populacja_poczatkowa.resize(rozmiar_populacji);

	populacja_chwilowa.clear();

	populacja.clear();
	populacja.resize(rozmiar_populacji);
		
	permutacja_pomocnicza.clear();
	permutacja_pomocnicza.resize(n - 1);

	permutacja_najlepsza.clear();
	permutacja_najlepsza.resize(n - 1);

	rodzic_1.clear();
	rodzic_1.resize(n - 1);

	rodzic_2.clear();
	rodzic_2.resize(n - 1);

	potomek_1.clear();
	
	potomek_2.clear();
	
	permutacja_w_sasiedztwie_potomka_1.clear();
	permutacja_w_sasiedztwie_potomka_1.resize(n - 1);

	permutacja_najlpesza_w_sasiedztwie_potomka_1.clear();
	permutacja_najlpesza_w_sasiedztwie_potomka_1.resize(n - 1);
			
	// Wczytanie danych od u¿ytkownika
	cout << " Czas wykonania [s]: "; // Czas wykonania
	cin >> czas_wykonania;
	cout << "----------------------------------------------------------- " << endl;
	cout << " | 1 - Transposition | 2 - Insertion |" << endl;
	cout << "-----------------------------------------------------------" << endl;	
	cout << " Rodzaj operatora mutacji: "; // Rodzaj operatora mutacji 
	cin >> rodzaj_mutacji;
	cout << "----------------------------------------------------------- " << endl;
	cout << " | 1 - Tak (zalecane dla mniejszych instancji) | 2 - Nie | " << endl;
	cout << "----------------------------------------------------------- " << endl;
	cout << " Uruchomienie lokalnej optymalizacji: "; // Uruchomienie lokalnej optymalizacji 
	cin >> lokalna_optymalizacja;


	// Generowanie populacji pocz¹tkowej w sposób losowy
	for (int i = 0; i < rozmiar_populacji; i++)
	{
		for (int i = 1; i < n; i++)
		{
			permutacja_pomocnicza[i - 1] = i;
		}
		random_shuffle(permutacja_pomocnicza.begin(), permutacja_pomocnicza.end());
		
		populacja_poczatkowa[i].chromosom = permutacja_pomocnicza;
	}
	populacja = populacja_poczatkowa;

	stan_czasu_start = read_QPC();

	// Pêtla g³ówna - zakañczana up³ywem czasu 
    do
    {
        stan_czasu_wykonanie = read_QPC() - stan_czasu_start;
       
		// Ocena jakoœci osobników populacji 
		for (int i = 0; i < rozmiar_populacji; i++)
		{
			populacja[i].wartosc_przystosowania = obliczKosztPermutacji(populacja[i].chromosom, v);
		}

		// Tworzenie nowej populacji 
		for (int i = 0; i < ((rozmiar_populacji - ilosc_osobnikow_elitarnych) / 2);)
		{
			// Selekcja chromosomów - metoda turniejowa 
			int m = 0; int p = 0;

			do 
			{
				m = losuj_rodzicow(gen);
				p = losuj_rodzicow(gen);
			} while (m == p);

			if (populacja[m].wartosc_przystosowania < populacja[p].wartosc_przystosowania)
			{
				rodzic_1 = populacja[m].chromosom;
			}
			else
			{
				rodzic_1 = populacja[p].chromosom;
			}

			do
			{
				m = losuj_rodzicow(gen);
				p = losuj_rodzicow(gen);
			} while (m == p);

			if (populacja[m].wartosc_przystosowania < populacja[p].wartosc_przystosowania)
			{
				rodzic_2 = populacja[m].chromosom;
			}
			else
			{
				rodzic_2 = populacja[p].chromosom;
			}

			// Krzy¿owanie osobników rodzicielskich - metoda OX
			if (losuj_prawdopodobienstwo(gen) < pp_krzyzowania)
			{
				int start = 0; int end = 0;

				do
				{
					start = losuj_sekcje_dopasowania(gen);
					end = losuj_sekcje_dopasowania(gen);
				} while (start == end || start > end || end == start + 1);

				for (int i = start; i < end; i++)
				{
					potomek_1.push_back(rodzic_1[i]);
					potomek_2.push_back(rodzic_2[i]);
				}

				int indeks_genu = 0; int gen_w_rodzicu_1 = 0; int gen_w_rodzicu_2 = 0;

				for (int i = 0; i < n - 1; i++)
				{
					indeks_genu = (end + i) % (n - 1);
					gen_w_rodzicu_1 = rodzic_1[indeks_genu];
					gen_w_rodzicu_2 = rodzic_2[indeks_genu];

					bool czy_zawiera = false;
					
					for (int a = 0; a < potomek_1.size(); a++)
					{
						if (potomek_1[a] == gen_w_rodzicu_2)
						{
							czy_zawiera = true;
						}
					}
					if (!czy_zawiera)
					{
						potomek_1.push_back(gen_w_rodzicu_2);
					}

					bool czy_zawiera_2 = false;

					for (int a = 0; a < potomek_2.size(); a++)
					{
						if (potomek_2[a] == gen_w_rodzicu_1)
						{
							czy_zawiera_2 = true;
						}
					}
					if (!czy_zawiera_2)
					{
						potomek_2.push_back(gen_w_rodzicu_1);
					}
				}

				int start_pomoc = start;

				rotate(potomek_1.begin(), potomek_1.end() - (start_pomoc--), potomek_1.end());
				rotate(potomek_2.begin(), potomek_2.end() - (start--), potomek_2.end());
			}
			else
			{
				potomek_1 = rodzic_1;
				potomek_2 = rodzic_2;
			}

			// Mutacja potomków
			if (rodzaj_mutacji == 1)
			{
				// Metoda TRANSPOSITION
				if (losuj_prawdopodobienstwo(gen) < pp_mutacji)
				{
					int x1 = 0; int x2 = 0;

					do
					{
						x1 = losuj_sekcje_dopasowania(gen);
						x2 = losuj_sekcje_dopasowania(gen);
					} while (x1 == x2 || x2 < x1);

					int tmp = potomek_1[x2];
					potomek_1[x2] = potomek_1[x1];
					potomek_1[x1] = tmp;
				}

				if (losuj_prawdopodobienstwo(gen) < pp_mutacji)
				{
					int y1 = 0; int y2 = 0;

					do
					{
						y1 = losuj_sekcje_dopasowania(gen);
						y2 = losuj_sekcje_dopasowania(gen);
					} while (y1 == y2 || y2 < y1);

					int tmp = potomek_2[y2];
					potomek_2[y2] = potomek_2[y1];
					potomek_2[y1] = tmp;
				}
			}
			else
			{
				// Metoda INSERTION 
				if (losuj_prawdopodobienstwo(gen) < pp_mutacji)
				{
					int u1 = 0; int u2 = 0;

					do
					{
						u1 = losuj_sekcje_dopasowania(gen);
						u2 = losuj_sekcje_dopasowania(gen);
					} while (u1 == u2 - 1 || u1 == u2 || u1 == u2 + 1);

					potomek_1.insert(potomek_1.begin() + u2, potomek_1[u1]);

					if (u2 > u1)
					{
						potomek_1.erase(potomek_1.begin() + u1);
					}
					else
					{
						potomek_1.erase(potomek_1.begin() + u1 + 1);
					}
				}
				if (losuj_prawdopodobienstwo(gen) < pp_mutacji)
				{
					int z1 = 0; int z2 = 0;

					do
					{
						z1 = losuj_sekcje_dopasowania(gen);
						z2 = losuj_sekcje_dopasowania(gen);
					} while (z1 == z2 - 1 || z1 == z2 || z1 == z2 + 1);

					potomek_2.insert(potomek_2.begin() + z2, potomek_2[z1]);

					if (z2 > z1)
					{
						potomek_2.erase(potomek_2.begin() + z1);
					}
					else
					{
						potomek_2.erase(potomek_2.begin() + z1 + 1);
					}
				}
			}

			// Lokalna optymalizacja
			if (lokalna_optymalizacja == 1)
			{
				koszt_potomka_1 = obliczKosztPermutacji(potomek_1, v);
				kosz_permutacji_najlepszej_w_sasiedztwie_potomka_1 = koszt_potomka_1;

				for (int i = 0; i < n - 1; i++)
				{
					for (int j = 0; j < n - 1; j++)
					{
						if (i != j - 1 && i != j && i != j + 1)
						{
							permutacja_w_sasiedztwie_potomka_1 = potomek_1;
							permutacja_w_sasiedztwie_potomka_1.insert(permutacja_w_sasiedztwie_potomka_1.begin() + j, permutacja_w_sasiedztwie_potomka_1[i]);

							if (j > i)
							{
								permutacja_w_sasiedztwie_potomka_1.erase(permutacja_w_sasiedztwie_potomka_1.begin() + i);
							}
							else
							{
								permutacja_w_sasiedztwie_potomka_1.erase(permutacja_w_sasiedztwie_potomka_1.begin() + i + 1);
							}

							koszt_permutacji_w_sasiedztwie_potomka_1 = obliczKosztPermutacji(permutacja_w_sasiedztwie_potomka_1, v);

							if (koszt_permutacji_w_sasiedztwie_potomka_1 < kosz_permutacji_najlepszej_w_sasiedztwie_potomka_1)
							{
								kosz_permutacji_najlepszej_w_sasiedztwie_potomka_1 = koszt_permutacji_w_sasiedztwie_potomka_1;
								permutacja_najlpesza_w_sasiedztwie_potomka_1 = permutacja_w_sasiedztwie_potomka_1;
							}
						}
					}
				}
				potomek_1 = permutacja_najlpesza_w_sasiedztwie_potomka_1;
			}
			// Dodanie potomków do populacji tymczasowej
			osobnik p1, p2;
			p1.chromosom = potomek_1;
			p2.chromosom = potomek_2;

			populacja_chwilowa.push_back(p1);
			populacja_chwilowa.push_back(p2);

			potomek_1.clear();
			potomek_2.clear();
			i++;
		}

		// Dodanie osobników elitarnych 
		sort(populacja.begin(), populacja.end(), sortujPoWartosciachPrzystosowania);
		
		for (int i = 0; i < 10; i++)
		{
			populacja_chwilowa.push_back(populacja[i]);
		}

		// Utworzenie nowej populacji 
		populacja = populacja_chwilowa;
		populacja_chwilowa.clear();

	} while (((float)stan_czasu_wykonanie / frequency < czas_wykonania));

	// Ocena jakoœci osobników populacji 
	for (int i = 0; i < rozmiar_populacji; i++)
	{
		populacja[i].wartosc_przystosowania = obliczKosztPermutacji(populacja[i].chromosom, v);
	}

	// Wyprowadzenie najlpeszego osobnika w populacji 
	koszt_permutacji_najlepszej = populacja[0].wartosc_przystosowania;

	for (int i = 0; i < rozmiar_populacji; i++)
	{
		if (koszt_permutacji_najlepszej > populacja[i].wartosc_przystosowania)
		{
			koszt_permutacji_najlepszej = populacja[i].wartosc_przystosowania;
		}
	}

	// Wypisanie wyników
	cout << "----------------------------------------------------------- " << endl;	
	cout << " Uzyskany wynik: " << koszt_permutacji_najlepszej << endl;
	cout << "----------------------------------------------------------- " << endl; 
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "----------------------------------------------------------- " << endl;
}

// Funkcja obliczaj¹ca koszt permutacji 
int obliczKosztPermutacji(vector<int>& permutacja, vector<int>& v)
{
	int koszt = 0;

	koszt = koszt + v[permutacja[0]];

	for (int i = 0; i < permutacja.size() - 1; i++)
	{
		koszt = koszt + v[(permutacja.size() + 1) * permutacja[i] + permutacja[i + 1]]; //obliczenie kosztu permutacji (koszt niekompletny)
	}

	koszt = koszt + v[(permutacja.size() + 1) * permutacja[permutacja.size() - 1] + 0]; //dodanie do kosztu dlugosc trasy do miasta 0 (koszt kompletny)

	return koszt;
}