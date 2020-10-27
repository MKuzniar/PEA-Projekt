#include <iostream>
#include <vector>
#include <bitset>

#include "algorytmDP.h"

using namespace std;

int funkcja_rekurencyjna_DP(int maska, int aktualne_miasto, int ilosc_miast, vector<int> macierz) //rekurencyjna funkcja wyznaczajaca najkrotsza droge miedzy miastami 
{
	if (maska == ((1 << ilosc_miast) - 1)) //sprawdzenie warunku czy wszystkie miasta zostaly odwiedzone (wtedy maska ma postac 2^n -1, np. dla 4 miast jest to 1111 (1 - miasto odwiedzone, 0 - miasto nieodwiedzone))
	{
		return macierz[ilosc_miast * aktualne_miasto + 0]; //jeœli tak zwracana jest odleglosc od aktualnego miasta do miasta 0 - poczatku 
	}
	
	int koszt_calkowity = 999999; //zmienna koszt_calkowity tymczasowo przechowuje bardzo duza liczbe, gdyby nie to, to moglaby przyjac wartosc 0 i na peno byc mniejsza od wyznaczonej najkrotszej drogi 
	
	for (int i = 0; i < ilosc_miast; i++)
	{
		if (((maska) & (1 << i)) == 0) //sprawdzamy czy miasto 'i' jest juz odwiedzone poprzez AND maski miasta i maski ogolnej
		{
			int koszt_tymczasowy = macierz[ilosc_miast * aktualne_miasto + i] + funkcja_rekurencyjna_DP(maska | (1 << i), i, ilosc_miast, macierz);// jeœli nie to rozwiazywane jest rownanie g(i,S) = min {cik + g(k,S-{k})}

			if (koszt_calkowity < koszt_tymczasowy)
			{
				koszt_calkowity = koszt_calkowity;
			}
			else
			{

				koszt_calkowity = koszt_tymczasowy;
			}
		}
	}
	return koszt_calkowity;	
}
