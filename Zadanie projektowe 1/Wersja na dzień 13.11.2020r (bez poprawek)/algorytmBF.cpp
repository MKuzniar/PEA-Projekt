#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "algorytmBF.h"

using namespace std;

vector<int> tablica_permutacji;
vector<int> pojedyncza_permutacja;
vector<int> najlepsza_permutacja;

vector<int> tablica_kosztow;
int koszt_minimalny;
int indeks_kosztu_minimalnego;

void algorytmBF(int n, vector<int>& v)
{	
	for (int a = 0; a < n; a++) 
	{
		pojedyncza_permutacja.push_back(a); //generowanie permutacji bazowej postaci [0, 1, 2 ... n-1]
	}

	obliczKosztPojedynczejPermutacji(pojedyncza_permutacja, v); //obliczenie kosztu permutacji bazowej 

	for (int b = 0; b < pojedyncza_permutacja.size(); b++) 
	{
		int x = pojedyncza_permutacja[b];
		tablica_permutacji.push_back(x); //wpisywanie permutacji bazowej do tablicy permutacji 
	}
	
	for (int c = 0; c < tgamma(n) - 1; c++) 
	{
		next_permutation(pojedyncza_permutacja.begin(), pojedyncza_permutacja.end()); //generownie kolejnych permutacji - zawsze zaczynajacych sie od 0 (petla wykonuje sie (n-1)! razy)

		obliczKosztPojedynczejPermutacji(pojedyncza_permutacja, v); //obliczenie kosztow kolejnych permutacji 

		for (int d = 0; d < pojedyncza_permutacja.size(); d++)
		{
			int tmp_1 = pojedyncza_permutacja[d];
			tablica_permutacji.push_back(tmp_1); //wpisywanie kolejnych permutacji do tablicy permutacji 
		}
		
	}

	koszt_minimalny = tablica_kosztow[0];
	for (int e = 0; e < tablica_kosztow.size(); e++)
	{
		if (koszt_minimalny > tablica_kosztow[e])
		{
			koszt_minimalny = tablica_kosztow[e]; //wybranie z talicy kosztow wartosci min - najmniejszy koszt 
			indeks_kosztu_minimalnego = e; //przechowanie indeksu (w celu znalezienie odpowiadajacej permutacji)
		}
	}

	for (int f = 0; f < n; f++)
	{
		int tmp_2;
		tmp_2 = tablica_permutacji[n * indeks_kosztu_minimalnego + f]; //wybranie permutacji odpowiadajacej najmniejszemu kosztowi 
		najlepsza_permutacja.push_back(tmp_2);
	}

}

void obliczKosztPojedynczejPermutacji(vector<int>& pojedyncza_permutacja,vector<int>& v)
{
	int koszt = 0;

	for (int i = 0; i < pojedyncza_permutacja.size() - 1; i++)
	{
		koszt = koszt + v[pojedyncza_permutacja.size() * pojedyncza_permutacja[i] + pojedyncza_permutacja[i + 1]]; //obliczenie kosztu permutacji (koszt niekompletny)
	}

	koszt = koszt + v[pojedyncza_permutacja.size() * pojedyncza_permutacja[pojedyncza_permutacja.size() - 1] + 0]; //dodanie do kosztu dlugosc trasy do miasta 0 (koszt kompletny)

	tablica_kosztow.push_back(koszt); //wpisanie kosztu permutacji do tablicy kosztow
}

void wyswietlNajlepszaPermutacje()
{
	cout << " Sciezka: ";
	for (int i = 0; i < najlepsza_permutacja.size(); i++)
	{
		cout << najlepsza_permutacja[i] << "->"; //wyswietlenie permutacji o najnizszym koszcie
	}
	cout << "0";
}