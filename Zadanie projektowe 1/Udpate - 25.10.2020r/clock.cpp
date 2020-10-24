#include <windows.h>
#include <iostream>
#include <iomanip>

#include "clock.h"

using namespace std;

long long int read_QPC() //QueryPerformanceCounter (funkcja ze strony WWW)
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}