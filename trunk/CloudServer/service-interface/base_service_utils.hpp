#ifndef BASE_SERVICE_UTILS_HPP
#define BASE_SERVICE_UTILS_HPP

namespace base_service_utils
{
	template<class T>
	void delete_ptr(T * ptr)
	{
		delete ptr;
	};
}

#endif // BASE_SERVICE_UTILS_HPP