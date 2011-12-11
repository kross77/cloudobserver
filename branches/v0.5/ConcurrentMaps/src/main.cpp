#include <iostream>
#include "general_test_runer.h"

int main()
{
	int tests = 5;
	int tasks_n = 10000;
	int cores_x_2 = boost::thread::hardware_concurrency()*2;
	for(int i=0; i<= cores_x_2; i++)
	{
	general_test_runer gt(tests, tasks_n, i);
	gt.start();
	}

	std::cin.get();
	return 0;
}