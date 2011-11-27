#include <stdio.h>
#include <iostream>
#include <boost/asio.hpp>
#include <thread_pool.h>

int calculate_the_answer_to_life_the_universe_and_everything(int i)
{
	boost::this_thread::sleep(boost::posix_time::milliseconds(i));
	std::cout << "Task outputs its argument: " << i << std::endl;
	return i;
}

template <class task_return_t>
void run_item( boost::shared_ptr< boost::packaged_task<task_return_t> > pt)
{
	(*pt)();
}

int main()
{
	int argument = 800;
	int time_to_waist = 100;

	// Lets create a thread_pool
	boost::shared_ptr< thread_pool > tp(new thread_pool(time_to_waist));

	// Will create pt - packaged_task that would bind calculate_the_answer_to_life_the_universe_and_everything to some argument
	boost::shared_ptr< boost::packaged_task<int> > pt(new
		boost::packaged_task<int>(
		boost::bind(calculate_the_answer_to_life_the_universe_and_everything, argument
		)));

	//Lets wrap packaged_task pt to a packaged_task wrapper_pt2 so that it would return void 
	// We shall always wrap our task into wrappers from which we shall not take any futures.
	boost::shared_ptr< boost::packaged_task<void> > wrapper_pt(new
		boost::packaged_task<void>(boost::bind(run_item<int>, pt)));

	//Lets post our task into thread pool
	tp->post(wrapper_pt);

	//And let the main thread sleep for a while
	boost::this_thread::sleep(boost::posix_time::milliseconds(time_to_waist*10));

	std::cin.get();
	return 0;
}
