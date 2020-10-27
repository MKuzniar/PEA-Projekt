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

void generujPermutacje(int liczba_miast, vector<int> miacierz)
{	
	for (int i = 0; i < liczba_miast; i++)
	{
		pojedyncza_permutacja.push_back(i);
	}

	obliczKoszt(pojedyncza_permutacja, miacierz);

	for (int i = 0; i < pojedyncza_permutacja.size(); i++)
	{
		int x = pojedyncza_permutacja[i];
		tablica_permutacji.push_back(x);
	}
	
	for (int i = 0; i < tgamma(liczba_miast) - 1; i++)
	{
		next_permutation(pojedyncza_permutacja.begin(), pojedyncza_permutacja.end());

		obliczKoszt(pojedyncza_permutacja, miacierz);

		for (int m = 0; m < pojedyncza_permutacja.size(); m++)
		{
			int x = pojedyncza_permutacja[m];
			tablica_permutacji.push_back(x);
		}
		
	}

	koszt_minimalny = tablica_kosztow[0];
	for (int k = 0; k < tablica_kosztow.size(); k++)
	{
		if (koszt_minimalny > tablica_kosztow[k])
		{
			koszt_minimalny = tablica_kosztow[k];
			indeks_kosztu_minimalnego = k;
		}
	}

	for (int l = 0; l < liczba_miast; l++)
	{
		int y;
		y = tablica_permutacji[liczba_miast * indeks_kosztu_minimalnego + l];
		najlepsza_permutacja.push_back(y);
	}

}

void obliczKoszt(vector<int> pojedyncza_permutacja,vector<int> macierz)
{
	int koszt = 0;

	for (int i = 0; i < pojedyncza_permutacja.size() - 1; i++)
	{
		koszt = koszt + macierz[pojedyncza_permutacja.size() * pojedyncza_permutacja[i] + pojedyncza_permutacja[i + 1]];
	}

	koszt = koszt + macierz[pojedyncza_permutacja.size() * pojedyncza_permutacja[pojedyncza_permutacja.size() - 1] + 0];

	tablica_kosztow.push_back(koszt);
}

void wyswietlNajlepszaPermutacje()
{
	cout << " Sciezka: ";
	for (int i = 0; i < najlepsza_permutacja.size(); i++)
	{
		cout << najlepsza_permutacja[i] << "->";
	}
	cout << "0";
}