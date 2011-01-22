// Here we show how to use Graph elements to construct a simple graph.
#include <iostream>
#include "GraphElementExample.h"
using namespace std;

static void f0 (char* a , int l) { cout << "f0" << endl; delete[] a; }
static void f1 (char* a, int l) { cout << "f1" << endl; delete[] a; }
static void f0g (char* a, int l) { cout << "f0 (with get)" << endl; delete[] a; }
static void f1g (char* a, int l) { cout << "f1 (with get)" << endl; delete[] a; }

int main()
{
	GraphElementExample a;
	a.Init();
	a.Add (f0) ;
	a.Add (f1) ;
	a.StartThread();

	boost::this_thread::sleep(boost::posix_time::milliseconds(100));

	GraphElementExample::GetResultStructure resultForF0 = a.Get();
	f0g(resultForF0.ptr, resultForF0.length);

	GraphElementExample::GetResultStructure resultForF1 = a.Get();
	f1g(resultForF1.ptr, resultForF1.length);

	a.Clean();
	cin.get();
}