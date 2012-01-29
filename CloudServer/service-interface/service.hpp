#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <exception>

// Boost
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/map.hpp> 
#include <boost/serialization/string.hpp>

// Cloud Forever
#include <http.h>
#include <pointer_utils.h>

#ifndef SHARED_HPP
#define SHARED_HPP
class shared
{
public:
	std::map<std::string, std::string> data;

	boost::shared_ptr<std::string> serialize()
	{
		std::stringstream oa_ss_data;
		boost::archive::text_oarchive  oa_data(oa_ss_data);
		oa_data << *this;
		return boost::shared_ptr<std::string>(new std::string(oa_ss_data.str()),boost::bind(&pointer_utils::delete_ptr<std::string>, _1) );
	}

	void deserialize( boost::shared_ptr<std::string> request_string)
	{
		std::stringstream ia_ss_data;
		ia_ss_data << *request_string;
		boost::archive::text_iarchive ia_data(ia_ss_data);
		ia_data >> *this;	 
	}

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
struct raw_in {
	raw_in(): raw_request(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1)), 
		shared_data(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1)), 
		error_data(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1)),
		raw_response(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1))
	{
	}
 boost::shared_ptr<std::string> raw_request;
 boost::shared_ptr<std::string> raw_response;
 boost::shared_ptr<std::string> shared_data;
 boost::shared_ptr<std::string> error_data;
 boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
};

struct raw_out {
	raw_out() : raw_request(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1)), 
		shared_data(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1)), 
		error_data(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1))
	{
	}
	boost::shared_ptr<std::string> raw_request;
	boost::shared_ptr<std::string> shared_data;
	boost::shared_ptr<std::string> error_data;
};

#endif // RAW_HPP

class base_service
{
public:
	virtual raw_out make_service_call(raw_in serialized_data) = 0;

	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket>, boost::shared_ptr<http_request>, boost::shared_ptr<http_response>) = 0;
	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree>) { throw not_configurable_exception(); };

	virtual void start() { throw not_startable_exception(); };
	virtual void stop() { throw not_stopable_exception(); };

	class not_configurable_exception: public std::exception { };
	class not_startable_exception: public std::exception { };
	class not_stopable_exception: public std::exception { };
};

class service : public base_service
{
public:
	virtual raw_out make_service_call(raw_in serialized_data)
	{
		
		boost::shared_ptr<boost::asio::ip::tcp::socket> socket = serialized_data.socket;

		boost::shared_ptr<http_request> request (new http_request(),  boost::bind(&pointer_utils::delete_ptr<http_request>, _1));
		request->deserialize(serialized_data.raw_request);

		boost::shared_ptr<http_response> response (new http_response(), boost::bind(&pointer_utils::delete_ptr<http_response>, _1));
		response->deserialize(serialized_data.raw_response);

		boost::shared_ptr<shared> shared_data (new shared(), boost::bind(&pointer_utils::delete_ptr<shared>, _1));
		shared_data->deserialize(serialized_data.shared_data);

		try
		{
			service_call(socket, request, response);
		}
		catch(std::exception &e)
		{
			boost::shared_ptr<std::string> err(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1));
			*err = std::string( e.what());
			raw_out out;
			out.error_data = err;
			return out;
		}
		raw_out out;
		out.raw_request = request->serialize();
		out.shared_data = shared_data->serialize();
		return out;
	}
};

#endif // SERVICE_HPP
