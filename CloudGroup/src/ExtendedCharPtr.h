//this is simpliest data class possible.
//any data class you create should  implement "copy constructor" and "assignment operator" to work correctly with IGraphElement 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#ifndef _ExtendedCharPtr_h_
#define _ExtendedCharPtr_h_

class ExtendedCharPtr
{
public:
	ExtendedCharPtr(): length(0), data(0) {}
	ExtendedCharPtr(size_t l, char* d): length(0), data(0)
	{
		if (!d) { return; }

		data = new char[l]; // this may throw, so we do it first

		length = l;
		memcpy(data, d, l);
	}
	// Swap
	void swap(ExtendedCharPtr& other)
	{
		using std::swap;
		swap(length, other.length);
		swap(data, other.data);
	}
	// Copy Constructor
	ExtendedCharPtr(const ExtendedCharPtr& other)
		: data(new char[other.length]), length(other.length)
	{
		std::copy(other.data, other.data+other.length, data);
	}
	// Assignemt Operator
	ExtendedCharPtr& operator=(ExtendedCharPtr other)
	{
		this->swap(other);
		return *this;
	}
	~ExtendedCharPtr()
	{
		delete[] data;
		// use the array form of delete
		// no need to test for nullity, it's handled
	}
	size_t length; // can't really be negative, right ?
	char* data;
};


#endif // _ExtendedCharPtr_h_