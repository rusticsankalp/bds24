// cpp.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

typedef unsigned long long ull;
ull findodd(ull start, ull end)
{
	ull sum{0};
	for (ull i = start; i <= end; i++)
	{
		if((i & 1) == 1)
			sum += i;
	}

	return sum;
}

ull findeven(ull start, ull end)
{
	ull sum{ 0 };
	for (ull i = start; i <= end; i++)
	{
		if ((i & 1) == 0)
			sum += i;
	}

	return sum;
}

// TODO: Reference additional headers your program requires here.
