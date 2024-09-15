// cpp.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

typedef unsigned long long ull;
const ull workStart{ 0 };
const ull workEnd{ 1900000000 };
ull findodd(ull start = workStart, ull end = workEnd)
{
	ull sum{0};
	for (ull i = start; i <= end; i++)
	{
		if((i & 1) == 1)
			sum += i;
	}

	return sum;
}

ull findeven(ull start = workStart, ull end = workEnd)
{
	ull sum{ 0 };
	for (ull i = start; i <= end; i++)
	{
		if ((i & 1) == 0)
			sum += i;
	}

	return sum;
}

void LongRunningFunction(std::stop_token st, int max)
{
	int i = 0;
	while (!st.stop_requested() && i <max)
	{
		findodd();
		std::cout << std::endl << std::this_thread::get_id() << " is doing work for iteration " << ++i << " ";
	}
	std::cout << std::this_thread::get_id() << "cancel is requested at iteration "<< i <<" ";

}

//:TBD 
//Convert the above to lambda
//Convert the above to fucntor ?


// Observation
// Static fucntion can also be used in threads

// TODO: Reference additional headers your program requires here.
