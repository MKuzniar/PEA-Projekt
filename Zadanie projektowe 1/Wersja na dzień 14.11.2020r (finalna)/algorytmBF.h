#pragma once

#include <iostream>
#include <vector>

using namespace std;

void algorytmBF(int n, vector<int>& v); //glowna funkcja algorytmu - odpowiedzialna za wyznaczenie wszystkich permutacji i wybranie tej o najmniejszym koszcie

int obliczKosztPermutacji(vector<int>& permutacja, vector<int>& v); //funkcja odpowiedzialna za obliczenie kosztu danej permutacji 

void wyswietlNajlepszaPermutacje(); //funkcja odpowiedzilana za wyswietlenie permutacji o najmniejszym koszcie