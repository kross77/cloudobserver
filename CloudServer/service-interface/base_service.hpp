#ifndef BASE_SERVICE_HPP
#define BASE_SERVICE_HPP

#include <exception>

// Boost
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>

// Cloud Forever
#include <raw_data.hpp>

class base_service
{
public:
	virtual service_call_output make_service_call( service_call_input serialized_data) = 0;

	virtual service_check_output make_service_check( service_check_input serialized_data) = 0;

	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree>) { throw not_configurable_exception(); };

	virtual void start() { throw not_startable_exception(); };
	virtual void stop() { throw not_stopable_exception(); };

	class not_configurable_exception: public std::exception { };
	class not_startable_exception: public std::exception { };
	class not_stopable_exception: public std::exception { };
};

#endif // BASE_SERVICE_HPP
