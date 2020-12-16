#include <iostream>
#include <vector>
#include <bitset>

#include "algorytmDP.h"

using namespace std;

vector<int>tablica;

int funkcjaRekurencyjna(int maska, int aktualne_miasto, int n, vector<int>& v) 
{
	if (maska == ((1 << n) - 1)) //sprawdzenie warunku czy wszystkie miasta zostaly odwiedzone
	{
		return v[n * aktualne_miasto + 0]; //zwracana jest odleglosc od aktualnego miasta do miasta 0
	}

	if (tablica[maska * n + aktualne_miasto] != -999999) //sprawdzenie rozwazania w tablicy zamiast ponownie wykonywac funkcje jesli juz byla raz wykonana
	{
		return tablica[maska * n + aktualne_miasto];
	}
	
	int koszt_calkowity = 999999; 
	
	for (int i = 0; i < n; i++)
	{
		if (((maska) & (1 << i)) == 0) //sprawdzenie czy miasto 'i' jest juz odwiedzone poprzez AND maski miasta i maski ogolnej
		{
			int koszt_tymczasowy = v[n * aktualne_miasto + i] + funkcjaRekurencyjna(maska | (1 << i), i, n, v); //rozwiazywane rowniana rekurencyjnego g(i,S) = min {cik + g(k,S-{k})}

			if (koszt_tymczasowy < koszt_calkowity)
			{
				koszt_calkowity = koszt_tymczasowy;
			}
		}
	}
	tablica[maska * n + aktualne_miasto] = koszt_calkowity;
	return koszt_calkowity;	
}

int algorytmDP(int n, vector<int>& v)
{
	tablica.reserve((1 << n) * n); //tabela o wymiarach 2^N * N, N - liczba miast

	for (int i = 0; i < (1 << n) * n; i++)
	{
		tablica.push_back(-999999);
	}

	funkcjaRekurencyjna(1 << 0, 0, n, v);
	
	return tablica[n];
}

