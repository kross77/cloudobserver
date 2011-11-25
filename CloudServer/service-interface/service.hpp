#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <exception>

// Boost
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>

// Cloud Forever
#include <http.h>

// A macro to be included in the declaration of every derived service.
#define CLOUD_SERVICE_AUXILIARIES \
	public: \
	virtual boost::shared_ptr<std::string> make_service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, \
	boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response) { \
	return service::make_service_call(socket, request, response); }

class service
{
public:
	virtual boost::shared_ptr<std::string> make_service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response)
	{
#ifdef WIN
		// The request and response should be copied on Windows because of the separate heaps in
		// every instance of CRT (which is included in every DLL because of the static linking).
		request = boost::shared_ptr<http_request>(new http_request(*request));
		response = boost::shared_ptr<http_response>(new http_response(*response));
#endif
		boost::shared_ptr<std::string> err(new std::string(""));
		try
		{
			service_call(socket, request, response);
		}
		catch(std::exception &e)
		{
			err = boost::shared_ptr<std::string>(new std::string( e.what()));
		}
		return err;
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
