#pragma once

#include <iostream>
#include <vector>

#include "clock.h"

using namespace std;

void algorytmSA(int n, vector<int>& v); // G��wna funkcja algorytmu 

int obliczKosztPermutacji(int n, vector<int>& permutacja, vector<int>& v); // Funkcja obliczaj�ca koszt permutacji startowej 

void generacjaSasiedniejPermutacji(int n, vector<int>& v); // Funkcja generuj�ca i obliczaj�ca koszt permutacji z s�siedztwa