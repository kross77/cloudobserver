#include "http_utils.h"

http_utils::http_utils()
{
	tag_set_cookie = "Set-Cookie";
}

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
	response->headers.insert(pair_ss(tag_set_cookie, cookie_data));
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
	this->split(form_data	, tag_delimiter_content_disposition, std::insert_iterator<std::vector<std::string> >(strings, strings.begin()));
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
				parsed_data.insert(std::pair<std::string, std::string>(filename, this->parse_file_upload_body(request_body_from_file_name_to_end)));
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
		/* 0 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* 1 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* 2 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* 3 */ 1,1,1,1, 1,1,1,1, 1,1,0,0, 0,0,0,0,

		/* 4 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
		/* 5 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,
		/* 6 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
		/* 7 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,

		/* 8 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* 9 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* A */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* B */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,

		/* C */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* D */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* E */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
		/* F */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
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