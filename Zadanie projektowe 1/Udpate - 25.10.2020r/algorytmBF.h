#pragma once

#include <iostream>
#include <vector>


using namespace std;

void generujPermutacje(int liczba_miast, vector<int> miacierz, int koszt_minimalny);

void wyswietlWektor(vector<int> permutacje);

int obliczKoszt(vector<int> permutacje, vector<int> macierz, int koszt_minimalny);