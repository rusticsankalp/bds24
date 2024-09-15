// cpp.cpp : Defines the entry point for the application.
//

#include "cpp.h"

using namespace std;
using namespace std::chrono;

int main()
{
	cout << "Hello : Thread id for main is." << std::this_thread::get_id() << endl;

	auto lambdaA = []() {
		findodd(0, 1900000000);
		};

	auto startTime = high_resolution_clock::now();
	


	auto endTime = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(endTime - startTime);
	cout << duration << endl;

	startTime = high_resolution_clock::now();
	std::jthread t1(findodd, workStart, workEnd);
	std::jthread t2(findeven, workStart, workEnd);
	std::jthread t3(lambdaA);
	std::jthread t4(LongRunningFunction,10);

	std::stop_callback callback(t4.get_stop_token(), []
		{
			cout << endl << "Stop callback executed by thread: "
				<< std::this_thread::get_id() << '\n';
		});

	// Stop_callback objects can be destroyed prematurely to prevent execution.
	{
		std::stop_callback scoped_callback(t4.get_stop_token(), []
			{
				// This will not be executed.
				std::cout << "Scoped stop callback executed by thread: "
					<< std::this_thread::get_id() << '\n';
			});
	}

	
	t1.join();
	t2.join();
	t3.join();
	cout << findodd(0, 1900000000) << endl;
	t4.request_stop();

	cout << findeven(0, 1900000000) << endl;

	endTime = high_resolution_clock::now();
	duration = duration_cast<microseconds>(endTime - startTime);



	cout << duration <<endl;
	return 0;
}
