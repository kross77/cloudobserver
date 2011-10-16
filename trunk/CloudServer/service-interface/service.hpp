#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <exception>

// Boost
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>

// Cloud Forever
#include <http.h>

class service
{
public:
	virtual void make_service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response)
	{
		service_call(socket, request, response);
	}

	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket>, boost::shared_ptr<http_request>, boost::shared_ptr<http_response>) = 0;
	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree>) { throw not_configurable_exception(); };

	virtual void start() { throw not_startable_exception(); };
	virtual void stop() { throw not_stopable_exception(); };

	class not_configurable_exception: public std::exception { };
	class not_startable_exception: public std::exception { };
	class not_stopable_exception: public std::exception { };
};

#endif // SERVICE_HPP
