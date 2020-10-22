#pragma once

#include <iostream>
#include <vector>

using namespace std;

int funkcja_rekurencyjna_DP(int maska, int aktualne_miasto, int ilosc_miast, vector<int> macierz); //rekurencyjna funkcja wyznaczajaca najkrotsza droge miedzy miastami 

int minimum_z_rozwiazan(int rozwiazanie_1, int rozwiazanie_2); //wyznaczenie min z wartosci dwoch rozwiazan