#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/optional.hpp>

#include <boost/shared_array.hpp>

#include <boost/bind.hpp>
#include <boost/date_time.hpp>

#include <boost/interprocess/detail/move.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp> 
#include <boost/serialization/string.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <exception>
#include <map>
#include <string>
#include <vector>

#include "pointer_utils.h"

class http_request
{
public:
	http_request();
	http_request(boost::asio::ip::tcp::socket& socket);
	~http_request();

	void clear();
	void reset();
	void receive(boost::asio::ip::tcp::socket& socket);
	bool timed_receive(boost::asio::ip::tcp::socket& socket, int& seconds_to_wait);
	void send(boost::asio::ip::tcp::socket& socket);
	boost::asio::ip::tcp::socket& send(std::string absolute_url, boost::asio::ip::tcp::socket& socket);
	void deserialize( boost::shared_ptr<std::string> request_string);
	boost::shared_ptr<std::string> serialize();
	std::string serialize_base();
	void deserialize_base( std::string request_string);

	std::string method;
	std::string url;
	std::string version;
	std::map<std::string, std::string> arguments;
	std::map<std::string, std::string> headers;
	std::map<std::string, std::string> cookies;
	int body_size;
	std::string body;

	class connection_exception: public std::exception { };
	class policy_file_request_exception: public std::exception { };
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version_)
	{
		ar & body;
		ar & body_size;
		ar & headers;
		ar & arguments;
		ar & cookies;
		ar & version;
		ar & url;
		ar & method;
	}

	typedef enum { METHOD, URL, URL_PARAM, URL_VALUE, VERSION, HEADER_KEY, HEADER_VALUE, BODY, OK } http_request_parser_state;

	void parse_buffer(char* buffer, http_request_parser_state &parser_state, std::string &key, std::string &value, int bytes_read);
	bool timed_receive_base(boost::asio::ip::tcp::socket& socket, size_t& buffer_size, int& seconds_to_wait);
	int read_some( boost::asio::ip::tcp::socket *sock, char* buffer, size_t& buffer_size );

	/*!
	 * \brief  Parses cookie string into map of pairs - `cookie name` : `cookie value`
	 *
	 * \n FullName:  http_utils::parse_cookie
	 * \n Access:    public  
	 *
	 * \param cookie_data std::string 
	 * \return std::map<std::string, std::string> map cookie name <-> cookie value
	 *
	 */
	std::map<std::string, std::string> parse_cookie(std::string cookie_data);
	
	template <class task_return_t>
	void run_item(  boost::shared_ptr<boost::packaged_task<task_return_t> > pt)
	{
		(*pt)();
	}
};

#endif // HTTP_REQUEST_H
