// cpp.cpp : Defines the entry point for the application.
//

#include "cpp.h"

using namespace std;
using namespace std::chrono;

int main()
{
	cout << "Hello CMake." << endl;

	auto startTime = high_resolution_clock::now();
	
	cout << findodd(0, 1900000000) << endl;
	cout << findeven(0, 1900000000) <<endl ;

	auto endTime = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(endTime - startTime);
	cout << duration << endl;

	startTime = high_resolution_clock::now();
	std::jthread t1(findodd, workStart, workEnd);
	std::jthread t2(findeven, workStart, workEnd);

	
	t1.join();
	t2.join();
	endTime = high_resolution_clock::now();
	duration = duration_cast<microseconds>(endTime - startTime);
	cout << duration <<endl;
	return 0;
}
