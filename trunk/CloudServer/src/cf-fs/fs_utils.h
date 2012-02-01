#ifndef FS_UTIL_H
#define FS_UTIL_H

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time.hpp>

#include <http_utils.h>
#include <general_utils.h>
#include <service.hpp>
#include "fs_file.h"

/*!
 *  \addtogroup Utilities
 *  @{
 */
namespace fs_utils
{

	boost::shared_ptr<fs_file> create_file( boost::filesystem::path p );

	bool was_modified( boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);

	void send_uncachable_file(boost::shared_ptr<fs_file> f ,  boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);

	
	/*!
	 * \brief appends standart headers to file requests such as "Last-Modified", "Content-Length", "Cache-Control", "Expires". It also inserts "Content-Type" to some comon web type files
	 *
	 * For list of existing Internet media types please refer to http://en.wikipedia.org/wiki/Internet_media_type
	 * For the description on why we shall sign some of media files in there content type see info IE warning SEC7113 http://blogs.msdn.com/b/ie/archive/2010/10/26/mime-handling-changes-in-internet-explorer.aspx
	 *
	 * \n FullName:  fs_utils::insert_file_headers
	 * \n Access:    public  
	 *
	 * \param f boost::shared_ptr<fs_file>
	 * \param socket boost::shared_ptr<boost::asio::ip::tcp::socket >
	 * \param response boost::shared_ptr<http_response>
	 * \return void 
	 * \note Currently adds "Content-Type" to CSS, files
	 *
	 */
	void insert_file_headers( boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket > socket, boost::shared_ptr<http_response> response );

	void send_uncachable_file( boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response );

	std::string get_user_name( boost::shared_ptr<shared> shared_data );
	void save_string_into_file( std::string contents, std::string s_name, boost::filesystem::path users_path );

	void send_404( std::string encoded_url,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response, boost::shared_ptr<shared> shared_data );
	void send_not_modified_304( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response );

	void send_info( boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response );
	const std::string  max_age = "max-age=240";
	const int expiration_period = 4;
};
/*! @} */

#endif //FS_UTIL_H
