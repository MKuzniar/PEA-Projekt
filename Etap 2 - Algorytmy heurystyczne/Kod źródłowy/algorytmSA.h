#pragma once

#include <iostream>
#include <vector>

#include "clock.h"

using namespace std;

void algorytmSA(int n, vector<int>& v); // G³ówna funkcja algorytmu 

int obliczKosztPermutacji(int n, vector<int>& permutacja, vector<int>& v); // Funkcja obliczaj¹ca koszt permutacji startowej 

void generacjaSasiedniejPermutacji(int n, vector<int>& v); // Funkcja generuj¹ca i obliczaj¹ca koszt permutacji z s¹siedztwa