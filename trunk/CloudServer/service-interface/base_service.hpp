#ifndef BASE_SERVICE_HPP
#define BASE_SERVICE_HPP

#include <exception>

// Boost
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>

// Cloud Forever
#include <raw_data.hpp>
#include <network_interface.hpp>

class base_service
{
public:
	virtual service_call_output make_service_call( service_call_input) = 0;

	virtual service_check_output make_service_check( service_check_input) = 0;

	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree>) { throw not_configurable_exception(); }

	virtual void start() { throw not_startable_exception(); }
	virtual void stop() { throw not_stopable_exception(); }
	
	virtual service_call_input do_serialize(service_call_input) = 0;

	class not_configurable_exception: public std::exception { };
	class not_startable_exception: public std::exception { };
	class not_stopable_exception: public std::exception { };
	class does_not_serialize: public std::exception { };

	virtual void set_network(boost::shared_ptr<network_interface>) = 0;
};

#endif // BASE_SERVICE_HPP
