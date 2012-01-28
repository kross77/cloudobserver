#include "http_utils.h"

std::map<std::string, std::string> http_utils::parse_cookie( std::string cookie_data )
{
	std::map<std::string, std::string> parsed_cookie;
	std::string token, token2;
	std::istringstream iss(cookie_data);
	while ( getline(iss, token, ' ') )
	{
		std::string name, val;
		std::istringstream iss2(token);
		int num = 0 ;
		while ( getline(iss2, token2, '=') )
		{
			if ( num == 0)
			{
				name = token2;
				num++;
			}
			else
			{
				val = token2;
				std::string::iterator it = val.end() - 1;
				if (*it == ';')
					val.erase(it);

			}
		}
		parsed_cookie.insert(std::pair<std::string, std::string>(name, val));
	}
	return parsed_cookie;

}

boost::shared_ptr<http_response> http_utils::save_cookie( std::string cookie_data, boost::shared_ptr<http_response> response )
{
	typedef std::pair<std::string, std::string> pair_ss;
	response->headers.insert(pair_ss("Set-Cookie", cookie_data));
	return response;
}

std::string http_utils::map_to_post_without_escape( std::map<std::string, std::string> request_map )
{
	std::map<std::string, std::string>::const_iterator end = request_map.end();
	std::string result = "";
	if(request_map.end() != request_map.begin())
	{
		for (std::map<std::string, std::string>::const_iterator it = request_map.begin(); it != end; ++it)
		{
			result += it->first;
			result += "=";
			result += it->second;
			result += "&";
		}
		return result.substr (0,result.length()-1); 
	}
	else
	{
		return result;
	}
}

std::map<std::string, std::string> http_utils::parse_multipart_form_data( std::string form_data )
{
	std::map<std::string, std::string> parsed_data;
	std::string tag_delimiter_content_disposition= "Content-Disposition: form-data; ";
	std::string taf_argument_name = "name";
	taf_argument_name += "=\"";
	std::vector < std::string > strings;
	std::string  temp;
	http_utils::split(form_data	, tag_delimiter_content_disposition, std::insert_iterator<std::vector<std::string> >(strings, strings.begin()));
	BOOST_FOREACH(std::string str, strings)
	{
		size_t  found_name = str.find(taf_argument_name);
		if (found_name != std::string::npos)
		{
			std::ofstream myfile;

			size_t  end_of_file_name = str.find("\"", found_name + taf_argument_name.length()); 
			if (end_of_file_name != std::string::npos)
			{
				std::string filename(str, found_name + taf_argument_name.length(), end_of_file_name - (found_name + taf_argument_name.length()));
				std::string request_body_from_file_name_to_end(str, found_name + taf_argument_name.length(), str.length() - (found_name + taf_argument_name.length()));
				parsed_data.insert(std::pair<std::string, std::string>(filename, http_utils::parse_file_upload_body(request_body_from_file_name_to_end)));
			}
		}
	}
	return parsed_data;
}

std::string http_utils::parse_file_upload_body( std::string contents )
{
	/* Locate the start point. */
	unsigned startPoint = contents.find("\r\n\r\n");
	if (startPoint == std::string::npos) throw std::runtime_error("Malformed string.");

	/* Locate the end point by finding the last newline, then backing up
	* to the newline before that.
	*/
	unsigned endPoint = contents.rfind('\n');
	if (endPoint == std::string::npos || endPoint == 0) throw std::runtime_error("Malformed string.");
	endPoint = contents.rfind('\n', endPoint - 1);
	if (endPoint == std::string::npos) throw std::runtime_error("Malformed string.");

	/* Hand back that slice of the string. */
	return std::string(contents.begin() + startPoint + 4, contents.begin() + endPoint-1);
}

std::string http_utils::url_encode( std::string sSrc )
{
	const char SAFE[256] =
	{
		/*      0 1 2 3  4 5 6 7  8 9 A B  C D E F */
		/* 0 */ 0,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* 1 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* 2 */ 0,1,0,0, 0,0,0,0, 0,0,0,0, 0,1,1,1,
		/* 3 */ 1,1,1,1, 1,1,1,1, 1,1,0,0, 0,0,0,0,

		/* 4 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
		/* 5 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,1,
		/* 6 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
		/* 7 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,

		/* 8 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* 9 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* A */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* B */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,

		/* C */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* D */ 0,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* E */ 0,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* F */ 0,0,0,0, 0,1,0,0, 0,0,0,0, 0,0,0,0
	};
	const char DEC2HEX[16 + 1] = "0123456789ABCDEF";
	const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
	const int SRC_LEN = sSrc.length();
	unsigned char * const pStart = new unsigned char[SRC_LEN * 3];
	unsigned char * pEnd = pStart;
	const unsigned char * const SRC_END = pSrc + SRC_LEN;

	for (; pSrc < SRC_END; ++pSrc)
	{
		if (SAFE[*pSrc]) 
			*pEnd++ = *pSrc;
		else
		{
			// escape this char
			*pEnd++ = '%';
			*pEnd++ = DEC2HEX[*pSrc >> 4];
			*pEnd++ = DEC2HEX[*pSrc & 0x0F];
		}
	}

	std::string sResult((char *)pStart, (char *)pEnd);
	delete [] pStart;
	return sResult;
}

std::string http_utils::url_decode( std::string sSrc )
{
	// Note from RFC1630:  "Sequences which start with a percent sign
	// but are not followed by two hexadecimal characters (0-9, A-F) are reserved
	// for future extension"

	const char HEX2DEC[256] = 
	{
		/*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
		/* 0 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
		/* 1 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
		/* 2 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
		/* 3 */  0, 1, 2, 3,  4, 5, 6, 7,  8, 9,-1,-1, -1,-1,-1,-1,

		/* 4 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
		/* 5 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
		/* 6 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
		/* 7 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,

		/* 8 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
		/* 9 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
		/* A */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
		/* B */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,

		/* C */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
		/* D */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
		/* E */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
		/* F */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1
	};

	const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
	const int SRC_LEN = sSrc.length();
	const unsigned char * const SRC_END = pSrc + SRC_LEN;
	const unsigned char * const SRC_LAST_DEC = SRC_END - 2;   // last decodable '%' 

	char * const pStart = new char[SRC_LEN];
	char * pEnd = pStart;

	while (pSrc < SRC_LAST_DEC)
	{
		if (*pSrc == '%')
		{
			char dec1, dec2;
			if (-1 != (dec1 = HEX2DEC[*(pSrc + 1)])
				&& -1 != (dec2 = HEX2DEC[*(pSrc + 2)]))
			{
				*pEnd++ = (dec1 << 4) + dec2;
				pSrc += 3;
				continue;
			}
		}

		*pEnd++ = *pSrc++;
	}

	// the last 2- chars
	while (pSrc < SRC_END)
		*pEnd++ = *pSrc++;

	std::string sResult(pStart, pEnd);
	delete [] pStart;
	return sResult;
}

std::wstring http_utils::utf8_to_utf16(const std::string& utf8)
{
	std::vector<unsigned long> unicode;
	size_t i = 0;
	while (i < utf8.size())
	{
		unsigned long uni;
		size_t todo;
		bool error = false;
		unsigned char ch = utf8[i++];
		if (ch <= 0x7F)
		{
			uni = ch;
			todo = 0;
		}
		else if (ch <= 0xBF)
		{
			throw std::logic_error("not a UTF-8 string");
		}
		else if (ch <= 0xDF)
		{
			uni = ch&0x1F;
			todo = 1;
		}
		else if (ch <= 0xEF)
		{
			uni = ch&0x0F;
			todo = 2;
		}
		else if (ch <= 0xF7)
		{
			uni = ch&0x07;
			todo = 3;
		}
		else
		{
			throw std::logic_error("not a UTF-8 string");
		}
		for (size_t j = 0; j < todo; ++j)
		{
			if (i == utf8.size())
				throw std::logic_error("not a UTF-8 string");
			unsigned char ch = utf8[i++];
			if (ch < 0x80 || ch > 0xBF)
				throw std::logic_error("not a UTF-8 string");
			uni <<= 6;
			uni += ch & 0x3F;
		}
		if (uni >= 0xD800 && uni <= 0xDFFF)
			throw std::logic_error("not a UTF-8 string");
		if (uni > 0x10FFFF)
			throw std::logic_error("not a UTF-8 string");
		unicode.push_back(uni);
	}
	std::wstring utf16;
	for (size_t i = 0; i < unicode.size(); ++i)
	{
		unsigned long uni = unicode[i];
		if (uni <= 0xFFFF)
		{
			utf16 += (wchar_t)uni;
		}
		else
		{
			uni -= 0x10000;
			utf16 += (wchar_t)((uni >> 10) + 0xD800);
			utf16 += (wchar_t)((uni & 0x3FF) + 0xDC00);
		}
	}
	return utf16;
}

std::string http_utils::utf16_to_utf8(const std::wstring & in)
{
	std::string out;
	unsigned int codepoint;
	bool completecode = false;
	for (std::wstring::const_iterator p = in.begin();  p != in.end();  ++p)
	{
		if (*p >= 0xd800 && *p <= 0xdbff)
		{
			codepoint = ((*p - 0xd800) << 10) + 0x10000;
			completecode = false;
		}
		else if (!completecode && *p >= 0xdc00 && *p <= 0xdfff)
		{
			codepoint |= *p - 0xdc00;
			completecode = true;
		}
		else
		{
			codepoint = *p;
			completecode = true;
		}
		if (completecode)
		{
			if (codepoint <= 0x7f)
				out.push_back(codepoint);
			else if (codepoint <= 0x7ff)
			{
				out.push_back(0xc0 | ((codepoint >> 6) & 0x1f));
				out.push_back(0x80 | (codepoint & 0x3f));
			}
			else if (codepoint <= 0xffff)
			{
				out.push_back(0xe0 | ((codepoint >> 12) & 0x0f));
				out.push_back(0x80 | ((codepoint >> 6) & 0x3f));
				out.push_back(0x80 | (codepoint & 0x3f));
			}
			else
			{
				out.push_back(0xf0 | ((codepoint >> 18) & 0x07));
				out.push_back(0x80 | ((codepoint >> 12) & 0x3f));
				out.push_back(0x80 | ((codepoint >> 6) & 0x3f));
				out.push_back(0x80 | (codepoint & 0x3f));
			}
		}
	}
	return out;
}

std::string  http_utils::escape ( const std::string& content )
{
	std::string result;
	result.reserve(content.size());
	escape(content.begin(), content.end(), std::back_inserter(result));
	return (result);
}

void  http_utils::escape ( std::istream& in, std::ostream& out )
{
	escape(std::istreambuf_iterator<char>(in),
		std::istreambuf_iterator<char>(),
		std::ostreambuf_iterator<char>(out));
}

void http_utils::send_found_302( const std::string & redirect_lication, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response,  boost::shared_ptr<http_request> request  )
{
	/* if there was no Fire Fox and probably other dull browsers we would do this (Chrome, IE, Safari tested):
	 *
	 *\code
		response->status = 302;
		response->description = "Found";
		response->headers.insert(std::pair<std::string, std::string>("Location", redirect_lication));
		response->send(*socket);
	 * \endcode
	 *
	 * but indeed there are.
	 *
	 * We could also create simple HTML redirection page - would work anywhere.
	 * \code
	std::ostringstream data_stream;
	data_stream << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\"><html><head><script type=\"text/javascript\">location.replace(\"" 
		<< redirect_lication << "\");</script><noscript><meta http-equiv=\"refresh\" content=\"0; url= "
		<< redirect_lication << "\"></noscript></head><body><p>Please turn on JavaScript!</p><a href=\"" 
		<< redirect_lication << "\"><h1>Content awaits you here.</h1></a></body></html>";
	response->headers.insert(std::pair<std::string, std::string>("Cache-Control", "max-age=0"));
	response->headers.insert(std::pair<std::string, std::string>("Pragma", "no-cache"));
	http_utils::send(data_stream.str(), socket, response);
	 * \endcode
	 * 
	 * so we decided to mix - html page and HTTP redirection
	 */

	response->description = "Found";
	response->headers.insert(std::pair<std::string, std::string>("Location", redirect_lication));
	response->headers.insert(std::pair<std::string, std::string>("Content-Location", redirect_lication));
	response->headers.insert(std::pair<std::string, std::string>("Refresh", std::string("0; url=" + redirect_lication)));
	response->headers.insert(std::pair<std::string, std::string>("Cache-Control", "max-age=0"));
	response->headers.insert(std::pair<std::string, std::string>("Pragma", "no-cache"));
	std::ostringstream data_stream;
	data_stream << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\"><html><head><script type=\"text/javascript\">location.replace(\"" 
		<< redirect_lication << "\");</script><noscript><meta http-equiv=\"refresh\" content=\"0; url= "
		<< redirect_lication << "\"></noscript></head><body><p>Please turn on JavaScript!</p><a href=\"" 
		<< redirect_lication << "\"><h1>Content awaits you here.</h1></a></body></html>";

	http_utils::send(302, data_stream.str(), socket, response, request);

}

void http_utils::send_error( const int & error_code, const std::string & description, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response )
{
	response->status = error_code;
	response->description = description;
	response->send(*socket);
}

void http_utils::send( const std::string & data, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response )
{
	http_utils::send(200, data, socket, response);
}

void http_utils::send( const std::string & data, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response,  boost::shared_ptr<http_request> request )
{
	http_utils::send(200, data, socket, response, request);
}

void http_utils::send( const int & code, const std::string & data, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response,  boost::shared_ptr<http_request> request )
{
	std::stringstream body;
	bool encoded = false;
	typedef std::map<std::string, std::string > map_t;
	map_t::iterator it = response->headers.find("Content-Type");
	if (it != response->headers.end())
		if (!((it->second == "application/x-gzip") || (it->second == "application/zip") || (it->second == "application/x-tar")))
			if (std::string::npos != request->headers["Accept-Encoding"].find("gzip"))
			{
				std::stringstream temp_body(data);
				http_utils::set_gzip_content_type(response);
				boost::iostreams::filtering_streambuf< boost::iostreams::input> in;
				in.push( boost::iostreams::gzip_compressor());
				in.push(temp_body);
				boost::iostreams::copy(in, body);
				encoded = true;
				http_utils::send(body.str(), socket, response);
			}
		
	if (!encoded)
		http_utils::send(code, data, socket, response);
}



void http_utils::get_extension_and_mime_type(std::string & file_extenstion, std::string & mime_type )
{
	if (file_extenstion.length() > 1)
	{
		if (boost::iequals(file_extenstion, ".html"))
		{
			file_extenstion = ".html";
			mime_type = "text/html";
		}
		else if ( boost::iequals(file_extenstion, ".css"))
		{
			file_extenstion = ".css";
			mime_type = "text/css";
		}
		else if (boost::iequals(file_extenstion, ".js"))
		{
			file_extenstion = ".js";
			mime_type =  "text/javascript";
		}
		else if (boost::iequals(file_extenstion, ".xml"))
		{
			file_extenstion = ".xml";
			mime_type = "text/xml";
		}
		else if (boost::iequals(file_extenstion, ".jpeg") || boost::iequals(file_extenstion, ".jpg"))
		{
			file_extenstion = ".jpeg";
			mime_type = "image/jpeg";
		}
		else if (boost::iequals(file_extenstion, ".png"))
		{
			file_extenstion = ".png";
			mime_type = "image/png";
		}
		else if (boost::iequals(file_extenstion, ".gif"))
		{
			file_extenstion = ".gif";
			mime_type = "image/gif";
		}
		else if (boost::iequals(file_extenstion, ".svg"))
		{
			file_extenstion = ".svg";
			mime_type =  "image/svg+xml";
		}
		else if (boost::iequals(file_extenstion, ".zip"))
		{
			file_extenstion = ".zip";
			mime_type = "application/zip";
		}
		else if (boost::iequals(file_extenstion, ".gzip"))
		{
			file_extenstion = ".gzip";
			mime_type = "application/x-gzip";
		}
		else if (boost::iequals(file_extenstion, ".pdf"))
		{
			file_extenstion = ".pdf";
			mime_type =  "application/pdf";
		}
	}
}



void http_utils::send( const int & code, const std::string & data, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response )
{
	response->status = code;
	response->body = data;
	response->headers["Content-Length"] = boost::lexical_cast<std::string>(response->body.length());
	response->send(*socket);
}

boost::shared_ptr<http_response> http_utils::set_file_content_type( const std::string & file_name, boost::shared_ptr<http_response> response )
{
	std::string type_extension = boost::filesystem::extension(file_name);
	std::string mime_type;
	http_utils::get_extension_and_mime_type(type_extension, mime_type );
	response->headers.insert(std::pair<std::string, std::string>("Content-Type", mime_type));
	return response;
}

boost::shared_ptr<http_response> http_utils::set_json_content_type( boost::shared_ptr<http_response> response )
{
	response->headers.insert(std::pair<std::string, std::string>("Content-Type", "application/json"));
	response->headers.insert(std::pair<std::string, std::string>("Cache-Control", "max-age=0"));
	response->headers.insert(std::pair<std::string, std::string>("Pragma", "no-cache"));
	return response;
}

void http_utils::send_json( std::pair<std::string, std::string> pair, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request )
{
	std::ostringstream data_stream;
	data_stream << "{\n\t\"" << http_utils::escape(pair.first) << "\": \""	<< http_utils::escape(pair.second)  << "\"\n}";
	http_utils::set_json_content_type(response);
	http_utils::send(data_stream.str(), socket, response, request);
	return;
}

void http_utils::send_json_error( std::string error, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request )
{
	std::ostringstream data_stream;
	data_stream << "{\n\t\"error\": \"" << http_utils::escape(error)  << "\"\n}";
	http_utils::set_json_content_type(response);
	http_utils::send(data_stream.str(), socket, response, request);
	return;
}

boost::shared_ptr<http_response> http_utils::set_gzip_content_type( boost::shared_ptr<http_response> response )
{
	response->headers.insert(std::pair<std::string, std::string>("Content-Encoding", "gzip"));
	return response;
}