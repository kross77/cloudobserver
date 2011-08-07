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