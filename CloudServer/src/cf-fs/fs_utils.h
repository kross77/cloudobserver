#ifndef FS_UTIL_H
#define FS_UTIL_H

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/date_time.hpp>

#include <http_utils.h>
#include <general_utils.h>
#include "fs_file.h"

class fs_utils
{
public:
	fs_utils();

	boost::shared_ptr<fs_file> create_file( boost::filesystem::path p );

	bool was_modified( boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);

	void send_uncachable_file(boost::shared_ptr<fs_file> f ,  boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);

	void insert_file_headers( boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket > socket, boost::shared_ptr<http_response> response );

	void send_uncachable_file( boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response );

	std::string get_user_name(boost::shared_ptr<http_request> request);

	void save_string_into_file( std::string contents, std::string s_name, boost::filesystem::path users_path );

	void send_404( std::string encoded_url,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response );
	void send_not_modified_304( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response );

private:
	std::string max_age;
	boost::posix_time::time_duration expiration_period;


};

#endif //FS_UTIL_H
