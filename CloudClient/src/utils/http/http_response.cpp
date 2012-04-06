#include "http_response.h"

http_response::http_response()
{
	this->reset();
}

http_response::http_response(boost::asio::ip::tcp::socket& socket)
{
	this->receive(socket);
}

http_response::~http_response()
{
}

void http_response::clear()
{
	this->version = "";
	this->status = 0;
	this->description = "";
	this->headers.clear();
	this->body_size = 0;
	this->body = "";
}

void http_response::reset()
{
	this->version = "HTTP/1.1";
	this->status = 200;
	this->description = "OK";
	this->headers.clear();
	this->body_size = 0;
	this->body = "";
}


void http_response::receive(boost::asio::ip::tcp::socket& socket)
{
	this->clear();

	http_response_parser_state parser_state = VERSION;

	int buffer_size = 1024;
	char* buffer = new char[buffer_size];
	std::string status = "";
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
				case VERSION:
					if (*position != ' ')
						this->version += *position++;
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
						this->status = boost::lexical_cast<int>(status);
						position++;
						parser_state = DESCRIPTION;
					}
					break;
				case DESCRIPTION:
					if (*position == '\r')
						position++;
					else if (*position != '\n')
						this->description += *position++;
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
						std::map<std::string, std::string>::iterator iterator = this->headers.find("Content-Length");
						if (iterator != this->headers.end())
						{
							this->body_size = boost::lexical_cast<int>(iterator->second);
							parser_state = (this->body_size == 0) ? OK : BODY;
						}
						else
						{
							this->body_size = 0;
							parser_state = BODY;
						}
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
		} while (parser_state != OK);
	}
	catch (boost::system::system_error& e)
	{
		std::cout << e.what() << std::endl;
		if (e.code() == boost::asio::error::eof)
			this->body_size = body.length();
		else
		{
			delete buffer;
			throw;
		}
	}
	catch (...)
	{
		delete buffer;
		throw;
	}
	delete buffer;
}

void http_response::send(boost::asio::ip::tcp::socket& socket)
{
	std::string response = this->version + ' ' + boost::lexical_cast<std::string>(this->status) + ' ' + this->description + "\r\n";
	for (std::map<std::string, std::string>::iterator header = this->headers.begin(); header != this->headers.end(); ++header)
		response += header->first + ": " + header->second + "\r\n";
	response += "\r\n" + this->body;
	socket.send(boost::asio::buffer(response.c_str(), response.length()));
}

boost::shared_ptr<std::string> http_response::serialize()
{
	std::stringstream oa_ss_res;
	boost::archive::text_oarchive  oa_response(oa_ss_res);
	oa_response << *this;
	return boost::shared_ptr<std::string>(new std::string(oa_ss_res.str()), boost::bind(&pointer_utils::delete_ptr<std::string>, _1) );
}

void http_response::deserialize( boost::shared_ptr<std::string> response_string)
{
	std::stringstream ia_ss_res;
	ia_ss_res << *response_string;
	boost::archive::text_iarchive ia_res(ia_ss_res);
	ia_res >> *this;
}