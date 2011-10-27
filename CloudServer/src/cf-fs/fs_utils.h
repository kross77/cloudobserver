#ifndef FS_UTIL_H
#define FS_UTIL_H

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <http_utils.h>
#include <general_utils.h>

class fs_utils
{
public:
	fs_utils();

	void send_404( std::string encoded_url,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response );

	std::string get_user_name(boost::shared_ptr<http_request> request);

	void send_not_modified_304( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response );

	void save_string_into_file( std::string contents, std::string s_name, boost::filesystem::path users_path );

private:
	general_utils *general_util;
	http_utils *http_util;


};

#endif //FS_UTIL_H
