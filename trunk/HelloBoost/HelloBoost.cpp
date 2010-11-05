// HelloBoost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <boost/thread.hpp>
#include <boost/timer.hpp>

namespace this_thread = boost::this_thread;

int a = 0;
int b = 0;
int c = 0;

class BaseThread
{
public:
	BaseThread()
	{ }
	virtual ~BaseThread()
	{ }

	void operator()()
	{
		try
		{
			for (;;)
			{
				// Check if the thread should be interrupted
				this_thread::interruption_point();

				DoStuff();
			}
		}
		catch (boost::thread_interrupted)
		{
			// Thread end
		}
	}

protected:
	virtual void DoStuff() = 0;
};

class ThreadA : public BaseThread
{
protected:
	virtual void DoStuff()
	{
		a += 1000;
		// Sleep a little while (0.5 second)
		this_thread::sleep(boost::posix_time::milliseconds(500));
	}
};

class ThreadB : public BaseThread
{
protected:
	virtual void DoStuff()
	{
		b++;
		// Sleep a little while (0.5 second)
		this_thread::sleep(boost::posix_time::milliseconds(100));
	}
};

int main()
{
	ThreadA thread_a_instance;
	ThreadB thread_b_instance;

	boost::thread threadA = boost::thread(thread_a_instance);
	boost::thread threadB = boost::thread(thread_b_instance);

	// Do this for 10 seconds (0.25 seconds * 40 = 10 seconds)
	for (int i = 0; i < 40; i++)
	{
		boost::timer t;
		c = a + b;
		std::cout << " And the summ is: " << c << std::endl;
		double elapsed_time = t.elapsed();
		std::cout << " Time wasted: \n " <<  elapsed_time << std::endl;

		// Sleep a little while (0.25 second)
		this_thread::sleep(boost::posix_time::milliseconds(250));
	}

	threadB.interrupt();
	threadB.join();

	threadA.interrupt();
	threadA.join();
	std::cin.get();
}
