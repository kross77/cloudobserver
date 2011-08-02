#include "general_utils.h"

std::string general_utils::to_lower( std::string data )
{
	std::use_facet< std::ctype<char> >(std::locale()).tolower(&data[0], &data[0] + data.size());
	return data;
}

void general_utils::print_map_contents( std::map <std::string, std::string> data )
{
	std::map<std::string, std::string>::const_iterator end = data.end();
	if(data.end() != data.begin())
	{
		std::cout << "Received request contained:\n";
		for (std::map<std::string, std::string>::const_iterator it = data.begin(); it != end; ++it)
		{
			std::cout << it->first << " : " << it->second << '\n';
		}
	}
}

void general_utils::print_map_contents( std::map <std::string, std::string> data, std::string name )
{
	std::map<std::string, std::string>::const_iterator end = data.end();
	if(data.end() != data.begin())
	{
		std::cout << "Received request contained next "<< name << ":\n";
		for (std::map<std::string, std::string>::const_iterator it = data.begin(); it != end; ++it)
		{
			std::cout << it->first << " : " << it->second << '\n';
		}
	}
}

std::string general_utils::get_sha256( std::string value )
{
	char data[65];
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, value.c_str(), value.length());
	SHA256_Final(hash, &sha256);
	int i = 0;
	for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(data + (i * 2), "%02x", hash[i]);
	}
	return std::string(data);
}

std::string general_utils::url_encode( std::string sSrc )
{
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

std::string general_utils::url_decode( std::string sSrc )
{
	// Note from RFC1630:  "Sequences which start with a percent sign
	// but are not followed by two hexadecimal characters (0-9, A-F) are reserved
	// for future extension"

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
