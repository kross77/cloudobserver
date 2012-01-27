#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <exception>

// Boost
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp> 
#include <boost/serialization/string.hpp>

// Cloud Forever
#include <http.h>

#ifndef SHARED_HPP
#define SHARED_HPP
class shared
{
public: std::map<std::string, std::string> data;
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & data;
	}
};
#endif // SHARED_HPP

#ifndef RAW_HPP
#define RAW_HPP
struct raw {
 boost::shared_ptr<std::string> raw_request;
 boost::shared_ptr<std::string> raw_response;
 boost::shared_ptr<std::string> shared_data;
 boost::shared_ptr<std::string> error_data;
 boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
};
#endif // RAW_HPP


// A macro to be included in the declaration of every derived service.
#define CLOUD_SERVICE_AUXILIARIES \
	public: \
	virtual boost::shared_ptr<std::string> make_service_call(raw serialized_data) { \
	return service::make_service_call(serialized_data); }

class service
{
public:
	virtual boost::shared_ptr<std::string> make_service_call(raw serialized_data)
	{

		boost::shared_ptr<boost::asio::ip::tcp::socket> socket = serialized_data.socket;

		http_request hreq;
		{
			std::stringstream ia_ss_req;
			ia_ss_req << *(serialized_data.raw_request.get());
			boost::archive::text_iarchive ia_req(ia_ss_req);
			ia_req >> hreq;
		}
		boost::shared_ptr<http_request> request = boost::shared_ptr<http_request>(new http_request(hreq));

		http_response hres;
		{
			std::stringstream ia_ss_res;
			ia_ss_res << *(serialized_data.raw_response.get());
			boost::archive::text_iarchive ia_res(ia_ss_res);
			ia_res >> hres;
		}
		boost::shared_ptr<http_response> response = boost::shared_ptr<http_response>(new http_response(hres));

		boost::shared_ptr<std::string> err(new std::string(""), boost::bind(&general_utils::delete_ptr<std::string>, _1));
		try
		{
			service_call(socket, request, response);
		}
		catch(std::exception &e)
		{
			*err = std::string( e.what());
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
