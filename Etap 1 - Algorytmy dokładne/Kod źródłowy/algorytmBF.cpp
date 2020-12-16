#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "algorytmBF.h"

using namespace std;

vector<int> permutacja;
vector<int> najlepsza_permutacja;

int koszt_minimalny;
int koszt_tymczasowy;

void algorytmBF(int n, vector<int>& v)
{	
	for (int a = 1; a < n; a++) 
	{
		permutacja.push_back(a); //generowanie permutacji bazowej postaci [1, 2 ... n-1]
	}

	for (int i = 0; i < (n - 1); i++)
	{
		int tmp;
		tmp = permutacja[i];
		najlepsza_permutacja.push_back(tmp);
	}
	
	koszt_minimalny = obliczKosztPermutacji(permutacja, v); //obliczenie kosztu permutacji bazowej 

	while(next_permutation(permutacja.begin(), permutacja.end()))
	{
		koszt_tymczasowy = obliczKosztPermutacji(permutacja, v); //obliczenie kosztow kolejnych permutacji 
		
		if (koszt_tymczasowy < koszt_minimalny)
		{
			koszt_minimalny = koszt_tymczasowy;

			najlepsza_permutacja.clear();

			for (int i = 0; i < (n - 1); i++)
			{
				int tmp;
				tmp = permutacja[i];
				najlepsza_permutacja.push_back(tmp);
			}
		}
	}
}

int obliczKosztPermutacji(vector<int>& permutacja,vector<int>& v)
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

void wyswietlNajlepszaPermutacje()
{
	cout << " Koszt minimalny BF: " << koszt_minimalny << endl;

	cout << " Sciezka: 0->";
	for (int i = 0; i < najlepsza_permutacja.size(); i++)
	{
		cout << najlepsza_permutacja[i] << "->";
	}
	cout << "0";
}
