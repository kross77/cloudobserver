#include "http_request.h"

http_request::http_request()
{
}

http_request::http_request(boost::asio::ip::tcp::socket& socket)
{
	this->receive(socket);
}

http_request::~http_request()
{
}

void http_request::receive(boost::asio::ip::tcp::socket& socket)
{
	http_request_parser_state parser_state = METHOD;

	int buffer_size = 1024;
	char* buffer = new char[buffer_size];
	std::string key = "";
	std::string value = "";

	try
	{
		do
		{
			int bytes_read = socket.read_some(boost::asio::buffer(buffer, buffer_size));

			char* position = buffer;
			do
			{
				switch (parser_state)
				{
				case METHOD:
					if (*position != ' ')
						this->method += *position++;
					else
					{
						position++;
						parser_state = URL;
					}
					break;
				case URL:
					if (*position == '?')
					{
						position++;
						key = "";
						this->execute = true;
						parser_state = URL_PARAM;
					}
					else if (*position != ' ')
						this->url += *position++;
					else
					{
						position++;
						parser_state = VERSION;
					}
					break;
				case URL_PARAM:
					if (*position == '=')
					{
						position++;
						value = "";
						parser_state = URL_VALUE;
					}
					else if (*position == ' ')
					{
						position++;
						parser_state = VERSION;
					}
					else
						key += *position++;
					break;
				case URL_VALUE:
					if (*position == '&')
					{
						position++;
						this->arguments[key] += value;
						key = "";
						parser_state = URL_PARAM;
					}
					else if (*position == ' ')
					{
						position++;
						this->arguments[key] += value;
						parser_state = VERSION;
					}
					else
						value += *position++;
					break;
				case VERSION:
					if (*position == '\r')
						position++;
					else if (*position != '\n')
						this->version += *position++;
					else
					{
						position++;
						key = "";
						parser_state = HEADER_KEY;
					}
				case HEADER_KEY:
					if (*position == '\r')
						position++;
					else if (*position == '\n')
					{
						position++;
						std::map<std::string, std::string>::iterator iterator = this->headers.find("Content-Length");
						if (iterator != this->headers.end())
						{
							this->body_size = boost::lexical_cast<int>(iterator->second);
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
						this->headers.insert(std::pair<std::string, std::string>(key, value));
						key = "";
						parser_state = HEADER_KEY;
					}
					break;
				case BODY:
					this->body += *position++;
					if (this->body.length() == this->body_size)
						parser_state = OK;
					break;
				case OK:
					position = buffer + bytes_read;
					break;
				}
			} while (position < buffer + bytes_read);
		} while (socket.available());
	}
	catch (...)
	{
		delete buffer;
		throw;
	}
	delete buffer;
}

void http_request::send(boost::asio::ip::tcp::socket& socket)
{
	std::string request = this->method + ' ' + this->url;
	if (this->execute)
	{
		request += '?';
		bool first = true;
		for (std::map<std::string, std::string>::iterator argument = this->arguments.begin(); argument != this->arguments.end(); ++argument)
		{
			std::vector<std::string> values;
			boost::split(values, argument->second, boost::is_any_of(", "));
			for (std::vector<std::string>::iterator value = values.begin(); value != values.end(); ++value)
			{
				if (!first)
					request += '&';
				else
					first = false;
				request += argument->first + '=' + *value;
			}
		}
	}
	request += ' ' + this->version + '\n';
	for (std::map<std::string, std::string>::iterator header = this->headers.begin(); header != this->headers.end(); ++header)
		request += header->first + ": " + header->second + '\n';
	request += '\n' + this->body;
	socket.send(boost::asio::buffer(request.c_str(), request.length()));
}
