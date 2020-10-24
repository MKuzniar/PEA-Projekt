#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


#include "algorytmBF.h"

using namespace std;

vector<int> permutacje;

void generujPermutacje(int liczba_miast, vector<int> miacierz, int koszt_minimalny)
{
	for (int i = 0; i < liczba_miast; i++)
	{
		permutacje.push_back(i);
	}

	obliczKoszt(permutacje, miacierz, koszt_minimalny);
	wyswietlWektor(permutacje);
		
	for (int i = 0; i < tgamma(liczba_miast) - 1; i++)
	{
		next_permutation(permutacje.begin(), permutacje.end());

		obliczKoszt(permutacje, miacierz, koszt_minimalny);
		wyswietlWektor(permutacje);
		
	}
}

void wyswietlWektor(vector<int> permutacje)
{
	for (int i = 0; i < permutacje.size(); i++)
	{
		cout << permutacje[i] << "->";
	}
	cout << "0" << endl;
}


void obliczKoszt(vector<int> permutacje,vector<int> macierz,int koszt_minimalny)
{
	int koszt = 0;

	for (int i = 0; i < permutacje.size() - 1; i++)
	{
		koszt = koszt + macierz[permutacje.size() * permutacje[i] + permutacje[i + 1]];
	}

	koszt = koszt + macierz[permutacje.size() * permutacje[permutacje.size() - 1] + 0];

	if (koszt == koszt_minimalny)
	{
		cout << ">Kosz to: " << koszt << " | ";
	}
	else
	{
		cout << " Kosz to: " << koszt << " | ";
	}
}