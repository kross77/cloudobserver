#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <exception>

// Boost
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
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
	// you can values post only once
	bool post(const std::string & key, const std::string & val)
	{
		return post(key, val, false);
	}

	// you can values post only once
	bool post(const std::string & key, const std::string & val, bool editable)
	{
		std::map<std::string, item>::iterator it;
		boost::mutex::scoped_lock lock(mut_);
		it = data.find(key);
		if (it != data.end())
		{
			return false;
		} 
		item post_data;
		post_data.editable = editable;
		post_data.data = val;
		data[key] = post_data;
		return true;
	}

	// you can update values only if you posted them as editable, note that other services can also edit such data
	bool update(const std::string & key, const std::string & val)
	{
		std::map<std::string, item>::iterator it;
		boost::mutex::scoped_lock lock(mut_);
		it = data.find(key);
		if (it != data.end())
		{
			if(it->second.editable)
			{
				it->second.data = val;
				return true;
			}
		} 
	return false;
		
	}

	// get safely any time
	std::string get(const std::string & key)
	{
		std::map<std::string, item>::iterator it;
		boost::mutex::scoped_lock lock(mut_);
		it = data.find(key);
		if (it != data.end())
		{
			return it->second.data;
		}
		return "";
	}

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
	class item  
	{
		public:
			std::string data;
			bool editable;

		private:
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive & ar, const unsigned int version)
			{
				ar & data;
				ar & editable;
			}
	};

	std::map<std::string, item> data;
	mutable boost::mutex mut_;

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
struct  service_call_input {
	 service_call_input(): shared_data(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1)), 
		error_data(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1))
	{}
 boost::shared_ptr<std::string> shared_data;
 boost::shared_ptr<std::string> error_data;
 boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
};

struct service_call_output {
	service_call_output() : shared_data(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1)), 
		error_data(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1))
	{}
	boost::shared_ptr<std::string> shared_data;
	boost::shared_ptr<std::string> error_data;
};

struct service_check_input {
	service_check_input() : shared_data(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1))
	{}
	boost::shared_ptr<std::string> shared_data;
};

struct service_check_output {
	service_check_output() : call_me_as(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1)),
		error_data(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1)),
		shared_data(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1))
	{}
	boost::shared_ptr<std::string> call_me_as;
	boost::shared_ptr<std::string> error_data;
	boost::shared_ptr<std::string> shared_data;
};

#endif // RAW_HPP

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

class http_service : public base_service
{
public:

	virtual std::string service_check(boost::shared_ptr<http_request>, boost::shared_ptr<shared>) = 0;

	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket>, boost::shared_ptr<http_request>, boost::shared_ptr<shared>) = 0;

	virtual service_check_output make_service_check( service_check_input serialized_data)
	{
		boost::shared_ptr<shared> shared_data (new shared(), boost::bind(&pointer_utils::delete_ptr<shared>, _1));
		shared_data->deserialize(serialized_data.shared_data);

		boost::shared_ptr<http_request> request (new http_request(),  boost::bind(&pointer_utils::delete_ptr<http_request>, _1));
		request->deserialize_base(shared_data->get("http_request"));

		boost::shared_ptr<std::string> check_result(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1));
		try
		{
			*check_result = service_check(request, shared_data);
		}
		catch(std::exception &e)
		{
			boost::shared_ptr<std::string> err(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1));
			*err = std::string( e.what());
			service_check_output out;
			out.error_data = err;
			return out;
		}
		service_check_output out;
		out.call_me_as = check_result;
		out.shared_data = shared_data->serialize();
		return out;
	}

	virtual service_call_output make_service_call( service_call_input serialized_data)
	{
		
		boost::shared_ptr<boost::asio::ip::tcp::socket> socket = serialized_data.socket;

		boost::shared_ptr<shared> shared_data (new shared(), boost::bind(&pointer_utils::delete_ptr<shared>, _1));
		shared_data->deserialize(serialized_data.shared_data);

		boost::shared_ptr<http_request> request (new http_request(),  boost::bind(&pointer_utils::delete_ptr<http_request>, _1));
		request->deserialize_base(shared_data->get("http_request"));

		try
		{
			service_call(socket, request, shared_data);
		}
		catch(std::exception &e)
		{
			boost::shared_ptr<std::string> err(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1));
			*err = std::string( e.what());
			service_call_output out;
			out.error_data = err;
			return out;
		}
		service_call_output out;
		shared_data->update("http_request", request->serialize_base());
		out.shared_data = shared_data->serialize();
		return out;
	}


};

class empty_service : public http_service
{
public:
	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket>, boost::shared_ptr<http_request>, boost::shared_ptr<shared>){}
	virtual std::string service_check(boost::shared_ptr<http_request>, boost::shared_ptr<shared>){ return "";}
};

#endif // SERVICE_HPP
