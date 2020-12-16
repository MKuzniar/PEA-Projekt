#include <iostream>
#include <vector>
#include <Windows.h>

#include "matrix.h"

using namespace std;

void wyswietlMacierz(int n, vector<int>& v) //funkcja wyswietlajaca wprowadzona macierz
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

void sprawdzDane(int n, vector<int>& v) //funkcja sprawdzajaca poprawnosc danych 
{
	bool test_poprawnosci = true;
	
	for (int i = 0; i < n; i++) //sprawdzenie czy na przekatnej macierzy znajduja sie wylacznie zera
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
	
	for (int j = 0; j < n; j++) //sprawdzenie czy poza przekatna nie ma zer w macierzy
	{
		for (int k = 0; k < n; k++)
		{
			if (v[n * j + k] == 0 && j != k)
			{
				test_poprawnosci = false;
			}
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