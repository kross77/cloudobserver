#ifndef HTTP_UTILITIES_H
#define HTTP_UTILITIES_H

//STD
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <functional>
#include <locale>
#include <set>
#include <vector>
#include <iterator>

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/foreach.hpp>

// Cloud Forever
#include <http.h>

#include "general_utils.h"
/*!
 *  \addtogroup Utilities
 *  @{
 */

//! contains diferent http utilities. from string encoding/decoding to parsing multipart form data.
namespace http_utils
{

	/*!
	 * \brief URL Encodes string 
	 *
	 *
	 * \n FullName:  http_utils::url_encode
	 * \n Access:    public  
	 *
	 * \param data std::string raw string
	 * \return std::string encoded string
	 * \sa http_utils::escape( const std::string& content );
	 * \sa http_utils::escape ( std::istream& in, std::ostream& out );
	 *
	 */
	std::string url_encode(std::string data);

	/*!
	 * \brief Decodes URL encoded string
	 *
	 *
	 * \n FullName:  http_utils::url_encode
	 * \n Access:    public  
	 *
	 * \param data std::string encoded string
	 * \return std::string raw string
	 * \sa http_utils::escape( const std::string& content );
	 * \sa http_utils::escape ( std::istream& in, std::ostream& out );
	 * \sa http_utils::url_encode(std::string data);
	 *
	 */
	std::string url_decode(std::string data);

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

	/*!
	 * \brief Parses form request body string with enctype: `multipart/form-data` 
	 * Parses form request body string with enctype: `multipart/form-data` 
	 * into map of pairs - `Content-Disposition field name` : `field data`  
	 * Use parse_file_upload_body on each 
	 *
	 *
	 * \n FullName:  http_utils::parse_multipart_form_data
	 * \n Access:    public  
	 *
	 * \param form_data std::string
	 * \return std::map<std::string, std::string>
	 *
	 */
	std::map<std::string, std::string> parse_multipart_form_data(std::string form_data);

	/*!
	 * \brief Saves cookie as `Set-Cookie` `Your string` into http_response headers
	 * modifies http response by adding 
	 *
	 * \n FullName:  http_utils::save_cookie
	 * \n Access:    public  
	 *
	 * \param cookie_data std::string cookie data
	 * \param response boost::shared_ptr<http_response> response
	 * \return boost::shared_ptr<http_response>
	 *
	 */
	boost::shared_ptr<http_response> save_cookie(std::string cookie_data, boost::shared_ptr<http_response> response);

	/*!
	 * \brief turns map of <std::string, std::string> into string formated as POST request
	 *
	 * \n FullName:  http_utils::map_to_post_without_escape
	 * \n Access:    public  
	 *
	 * \param  request_map std::map<std::string , std::string> 
	 * \return std::string 
	 *
	 */
	std::string map_to_post_without_escape(std::map<std::string, std::string> request_map); // you shall provide one with automated escape and one without. Because escape(escape(str)) will produce bad results.

	/*!
	 * \brief reads std::string with utf8 encoded charecters into utf16 encoded std::wstring
	 *
	 * \n FullName:  http_utils::utf8_to_utf16
	 * \n Access:    public  
	 *
	 * \param utf8 const std::string & 
	 * \return std::wstring
	 *
	 */
	std::wstring utf8_to_utf16(const std::string& utf8);

	/*!
	 * \brief 	 reads std::wstring with utf16 encoded charecters into utf8 encoded std::string 
	 *
	 *
	 * \n FullName:  http_utils::utf16_to_utf8
	 * \n Access:    public  
	 *
	 * \param in const std::wstring & 
	 * \return std::string 
	 *
	 */
	std::string utf16_to_utf8(const std::wstring & in);
	
	/*!
	 * \brief Get escaped version of "content".
	 *
	 *
	 * \n FullName:  http_utils::escape
	 * \n Access:    public  
	 *
	 * \param content const std::string & 
	 * \return std::string 
	 *
	 */
	std::string escape ( const std::string& content );

	/*!
	 * \brief  Escape data on the fly, using "constant" memory.
	 *
	 * \n FullName:  http_utils::escape
	 * \n Access:    public  
	 *
	 * \param in std::istream & 
	 * \param out std::ostream & 
	 * \return void
	 *
	 */
	void escape ( std::istream& in, std::ostream& out );

	/*!
	* \brief XML escaping in it's general form.  Note that 'out' is expected to an "infinite" sequence.
	 *
	 * \n FullName:  http_utils<InIter, OutIter>::escape
	 * \n Access:    public  
	 *
	 * \param begin InIter 
	 * \param end InIter 
	 * \param out OutIter 
	 * \return OutIter 
	 *
	 */
	template<typename InIter, typename OutIter>
	OutIter escape ( InIter begin, InIter end, OutIter out );

	/*!
	 * \brief redirect user to specific URL location
	 *
	 * \n FullName:  http_utils::send_found_302
	 * \n Access:    public  
	 *
	 * \param redirect_lication std::string 
	 * \param socket boost::shared_ptr<boost::asio::ip::tcp::socket> 
	 * \param response boost::shared_ptr<http_response>
	 * \return void 
	 *
	 */
	void send_found_302( std::string redirect_lication, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response ); // This shall be turned into 303 for pure HTTP/1.1.

	/*!
	 * \brief  send HTTP /1.1 error
	 *
	 * \n FullName:  http_utils::send_error
	 * \n Access:    public  
	 *
	 * \param error_code const int & 
	 * \param description const std::string & 
	 * \param socket boost::shared_ptr<boost::asio::ip::tcp::socket> 
	 * \param response boost::shared_ptr<http_response> 
	 * \return void 
	 *
	 */
	void send_error( const int & error_code, const std::string & description,   boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response );

	/*!
	 * \brief send data over HTTP /1.1
	 *
	 * \n FullName:  http_utils::send
	 * \n Access:    public  
	 *
	 * \param data const std::string &
	 * \param socket boost::shared_ptr<boost::asio::ip::tcp::socket>
	 * \param response boost::shared_ptr<http_response>
	 * \return void
	 *
	 */
	void send( const std::string & data,   boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response);

	/*!
	 * \brief send data with some response code ( HTTP /1.1 )
	 *
	 * \n FullName:  http_utils::send
	 * \n Access:    public  
	 *
	 * \param code const int &
	 * \param data const std::string &
	 * \param socket boost::shared_ptr<boost::asio::ip::tcp::socket>
	 * \param response boost::shared_ptr<http_response>
	 * \return void 
	 * 
	 */
	void send( const int & code, const std::string & data, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response );

	std::string parse_file_upload_body(std::string contents);

	template<typename _OutputIterator>
	inline void split(std::string str, std::string delim, _OutputIterator result);

	template<typename InIter, typename OutIter>
	OutIter copy_asciiz ( InIter begin, OutIter out );

}
/*! @} */

#include "http_utils_inl.h"
#endif HTTP_UTILITIES_H
