#pragma once

#include <iostream>
#include <vector>

using namespace std;

int funkcjaRekurencyjna(int maska, int aktualne_miasto, int n, vector<int>& v); //rekurencyjna funkcja wyznaczajaca najkrotsza droge miedzy miastami 

int algorytmDP(int n, vector<int>& v); //funkcja inicjujaca wykonywanie algorytmu DP