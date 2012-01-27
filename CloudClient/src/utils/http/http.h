#ifndef HTTP_H
#define HTTP_H

#include "http_request.h"
#include "http_response.h"

namespace general_utils
{
	template<class T>
	void delete_ptr(T * ptr)
	{
		delete ptr;
	};
}

#endif // HTTP_H
