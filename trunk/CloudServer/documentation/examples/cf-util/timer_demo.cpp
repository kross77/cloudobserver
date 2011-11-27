#include <timer.h>

int main()
{
	timer t;
	std::cout << "started a timer" << std::endl << "please hit ENTER" << std::endl;
	std::cin.get();

	std::cout << "time passed: " << t.elapsed() << std::endl ;

	std::cout << "we will restart timer now" << std::endl ;
	t.restart();

	std::cout << "please hit ENTER" << std::endl;
	std::cin.get();

	std::cout << "time passed: " << t.elapsed() << std::endl ;
	std::cin.get();
}