#include <iostream>
#include "general_test_runer.h"

int main()
{
	int tests = 5;
	int tasks_n = 1000;
	
	general_test_runer gt(tests, tasks_n);
	gt.start();

	std::cin.get();
	return 0;
}