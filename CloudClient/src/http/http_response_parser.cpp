#include "http_response_parser.h"

http_response http_response_parser::parse(boost::asio::ip::tcp::socket& s)
{
	http_response response;
	http_response_parser_state parser_state = VERSION;

	int buffer_size = 1024;
	char* buffer = new char[buffer_size];
	std::string status = "";
	std::string key = "";
	std::string value = "";
	int body_data_index = 0;
	
	try
	{
		int bytes_received = 0;
		do
		{
			int bytes_read = s.read_some(boost::asio::buffer(buffer, buffer_size));
			bytes_received += bytes_read;

			char* position = buffer;
			do
			{
				switch (parser_state)
				{
				case VERSION:
					if (*position != ' ')
						response.version += *position++;
					else
					{
						position++;
						parser_state = STATUS;
					}
					break;
				case STATUS:
					if (*position != ' ')
						status += *position++;
					else
					{
						response.status = boost::lexical_cast<int>(status);
						position++;
						parser_state = DESCRIPTION;
					}
					break;
				case DESCRIPTION:
					if (*position == '\r')
						position++;
					else if (*position != '\n')
						response.description += *position++;
					else
					{
						position++;
						key = "";
						parser_state = HEADER_KEY;
					}
					break;
				case HEADER_KEY:
					if (*position == '\r')
						position++;
					else if (*position == '\n')
					{
						position++;
						std::map<std::string, std::string>::iterator iterator = response.headers.find("Content-Length");
						if (iterator != response.headers.end())
						{
							response.body_size = boost::lexical_cast<int>(iterator->second);
							parser_state = BODY;
						}
						else
							parser_state = OK;
					}
					else if (*position == ':')
						position++;
					else if (*position != ' ')
						key += *position++;
					else
					{
						position++;
						value = "";
						parser_state = HEADER_VALUE;
					}
					break;
				case HEADER_VALUE:
					if (*position == '\r')
						position++;
					else if (*position != '\n')
						value += *position++;
					else
					{
						position++;
						response.headers.insert(std::pair<std::string, std::string>(key, value));
						key = "";
						parser_state = HEADER_KEY;
					}
					break;
				case BODY:
					response.body += *position++;
					if (response.body.length() == response.body_size)
						parser_state = OK;
					break;
				case OK:
					position = buffer + bytes_read;
					break;
				}
			} while (position < buffer + bytes_read);
		} while (s.available());
	}
	catch (std::exception& e)
	{
		std::cout << "Error while parsing HTTP response: " << e.what() << std::endl;
	}
	return response;
}
