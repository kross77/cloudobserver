#ifndef RAW_DATA_HPP
#define RAW_DATA_HPP

#include <string>

// Boost
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

// Cloud Forever
#include <pointer_utils.h>
#include <shared_data.hpp>

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

#endif // RAW_DATA_HPP

