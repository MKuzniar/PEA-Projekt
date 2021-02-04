#include <iostream>
#include <vector>
#include <Windows.h>

#include "matrix.h"

using namespace std;

// Funkcja odpowiedzialna za wypisanie macierzy s¹siedztwa 
void wyswietlMacierz(int n, vector<int>& v)
{
	cout << " Ilosc miast: " << n << endl;

	for (int i = 0; i < n * n; i++)
	{
		cout << v[i] << '\t';
		if (i % n == n - 1)
		{
			cout << endl;
		}
	}
}

// Funkcja odpowiedzialna za sprawdzenie macierzy s¹siedztwa 
void sprawdzDane(int n, vector<int>& v)
{
	bool test_poprawnosci = true;

	// Sprawdzenie czy na przek¹tnej macierzy znajduj¹ siê wy³acznie 0 
	for (int i = 0; i < n; i++)
	{
		if (v[n * i + i] == 0)
		{
			test_poprawnosci = true;
		}
		else
		{
			test_poprawnosci = false;
			break;
		}
	}

	if (test_poprawnosci == true)
	{
		cout << " Dane poprawne!" << endl;
	}
	else
	{
		cout << " Dane niepoprawne!" << endl;
		cout << "-------------------------------------------------" << endl;
		getchar(); getchar();
		exit(0);
	}
}