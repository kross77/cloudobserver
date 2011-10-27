#include "fs_utils.h"

fs_utils::fs_utils()
{
	general_util = new general_utils();
	http_util = new http_utils();
}

void fs_utils::send_404( std::string encoded_url,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{
	std::ostringstream body;
	body << "Error 404! " << http_util->url_decode(request->url) << " does not exist\n <br/> <a href='/'>" << "Dear " << http_util->url_decode(get_user_name(request)) <<", please come again!</a>";

	response->body = "<head></head><body><h1>" + body.str() + "</h1></body>";
	response->send(*socket);
}

std::string fs_utils::get_user_name( boost::shared_ptr<http_request> request )
{
	std::string response = "";
	std::map<std::string, std::string>::iterator it = request->headers.find("email");
	if (it != request->headers.end())
		response = it->second;

	return response;
}

void fs_utils::send_not_modified_304( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response )
{
	response->status = 304;
	response->description = "Not Modified";
	response->send(*socket);
}

void fs_utils::save_string_into_file( std::string contents, std::string s_name, boost::filesystem::path users_path )
{
	general_util->create_directory(users_path);
	boost::filesystem::ofstream datFile;
	boost::filesystem::path name (users_path / s_name);
	datFile.open(name, std::ofstream::binary | std::ofstream::trunc | std::ofstream::out	);
	datFile.write(contents.c_str(), contents.length());
	datFile.close();
}