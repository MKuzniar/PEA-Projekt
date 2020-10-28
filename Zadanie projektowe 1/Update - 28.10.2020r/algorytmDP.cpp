#include <iostream>
#include <vector>
#include <bitset>

#include "algorytmDP.h"

using namespace std;

int algorytmDP(int maska, int aktualne_miasto, int n, vector<int> v) 
{
	if (maska == ((1 << n) - 1)) //sprawdzenie warunku czy wszystkie miasta zostaly odwiedzone
	{
		return v[n * aktualne_miasto + 0]; //zwracana jest odleglosc od aktualnego miasta do miasta 0
	}
	
	int koszt_calkowity = 999999; 
	
	for (int i = 0; i < n; i++)
	{
		if (((maska) & (1 << i)) == 0) //sprawdzenie czy miasto 'i' jest juz odwiedzone poprzez AND maski miasta i maski ogolnej
		{
			int koszt_tymczasowy = v[n * aktualne_miasto + i] + algorytmDP(maska | (1 << i), i, n, v); //rozwiazywane rowniana rekurencyjnego g(i,S) = min {cik + g(k,S-{k})}

			if (koszt_calkowity < koszt_tymczasowy)
			{
				koszt_calkowity = koszt_calkowity;
			}
			else
			{
				koszt_calkowity = koszt_tymczasowy; //wybieranie wartosci min {cik + g(k,S-{k})}
			}
		}
	}
	return koszt_calkowity;	
}
