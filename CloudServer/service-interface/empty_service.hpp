#ifndef EMPTY_SERVICE_HPP
#define EMPTY_SERVICE_HPP

// Cloud Forever
#include <base_service.hpp>

class empty_service : public base_service
{
public:
	virtual service_call_output make_service_call( service_call_input serialized_data){ service_call_output result; return result;}
	virtual service_check_output make_service_check( service_check_input serialized_data){ service_check_output result; return result;}
};

#endif // EMPTY_SERVICE_HPP
