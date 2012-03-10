#include "observer_service.h"

observer_service::observer_service()
{
	this->max_streams = 10;
	this->dumps_location = (boost::filesystem::current_path() /= "dumps").string();
	this->dump_writers = false;
	this->dump_readers = false;
}

observer_service::~observer_service()
{
	for (std::map<std::string, writer*>::iterator i = writers.begin(); i != writers.end(); ++i)
		delete i->second;
}

void observer_service::service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request,  boost::shared_ptr<shared> shared_data)
{
	boost::shared_ptr<http_response> response(new http_response(), boost::bind(&pointer_utils::delete_ptr<http_response>, _1));

	if (request->url == "/users.json")
	{
		std::ostringstream users_stream;
		users_stream << "[";
		for (std::map<std::string, writer*>::iterator i = this->writers.begin(); i != this->writers.end(); ++i)
			users_stream << "\n\t{\n\t\t\"nickname\": \""
				<< i->first << "\",\n\t\t\"width\": "
				<< i->second->get_width() << ",\n\t\t\"height\": "
				<< i->second->get_height() << "\n\t},";
		std::string users = users_stream.str();
		if (this->writers.size() > 0)
			users = users.substr(0, users.length() - 1);

		http_utils::set_json_content_type(response);
		http_utils::send(users.append("\n]"), socket, response, request);
		return;
	}

	std::string action = request->arguments["action"];
	client_type type = GENERAL_CLIENT;
	if (action == "write")
		type = WRITER_CLIENT;
	if (action == "read")
		type = READER_CLIENT;

	std::string nickname = request->url.substr(1);
	boost::shared_ptr<std::ofstream> dump;
	switch (type)
	{
	case GENERAL_CLIENT:
		response->status = 400;
		response->description = "Bad Request";
		response->body =
			"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n"
			"<HTML><HEAD>\n"
			"<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n"
			"</HEAD>\n"
			"<BODY>Unknown action \"" + action +
			"\"!</BODY></HTML>\n";
		break;
	case WRITER_CLIENT:
		if (!check_nickname(nickname))
		{
			response->status = 400;
			response->description = "Bad Request";
			response->body =
				"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n"
				"<HTML><HEAD>\n"
				"<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n"
				"</HEAD>\n"
				"<BODY>Nickname \"" + nickname +
				"\" is not valid! Nickname must contain only alphabetic characters and decimal digits.</BODY></HTML>\n";
		}
		else if (this->writers.find(nickname) != this->writers.end())
		{
			response->status = 403;
			response->description = "Forbidden";
			response->body =
				"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n"
				"<HTML><HEAD>\n"
				"<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n"
				"</HEAD>\n"
				"<BODY>Nickname \"" + nickname +
				"\" is already in use!</BODY></HTML>\n";
		}
		else if (this->writers.size() >= (unsigned int)this->max_streams)
		{
			response->status = 403;
			response->description = "Forbidden";
			response->body =
				"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n"
				"<HTML><HEAD>\n"
				"<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n"
				"</HEAD>\n"
				"<BODY>You have reached the maximum number of streams available in this demo. Try stopping some streams to create the new ones.</BODY></HTML>\n";
		}
		else
		{
			response->body =
				"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n"
				"<HTML><HEAD>\n"
				"<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n"
				"</HEAD>\n"
				"<BODY>Ready to receive stream from user with nickname \"" + nickname +
				"\".</BODY></HTML>\n";

			if (this->dump_writers)
			{
				if (!boost::filesystem::exists(this->dumps_location))
					boost::filesystem::create_directory(this->dumps_location);
				dump.reset(new std::ofstream((this->dumps_location.string() + '/' + get_current_date_time() + '-' + nickname + "-writer.flv").c_str(), std::ofstream::binary));
			}
		}
		break;
	case READER_CLIENT:
		if (this->writers.find(nickname) == this->writers.end())
		{
			response->status = 404;
			response->description = "Not Found";
			response->body =
				"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n"
				"<HTML><HEAD>\n"
				"<META http-equiv=Content-Type content=\"text/html; charset=windows-1252\">\n"
				"</HEAD>\n"
				"<BODY>User with nickname \"" + nickname +
				"\" is not found!</BODY></HTML>\n";
		}
		else
		{
			response->headers.insert(std::pair<std::string, std::string>("Content-type", "video/x-flv"));
			response->headers.insert(std::pair<std::string, std::string>("Cache-Control", "no-cache"));

			if (this->dump_readers)
			{
				if (!boost::filesystem::exists(this->dumps_location))
					boost::filesystem::create_directory(this->dumps_location);
				dump.reset(new std::ofstream((this->dumps_location.string() + '/' + get_current_date_time() + '-' + nickname + "-reader.flv").c_str(), std::ofstream::binary));
			}
		}
		break;
	}

	if (type != READER_CLIENT)
	{
		response->body_size = response->body.length();
		response->headers.insert(std::pair<std::string, std::string>("Content-Length", boost::lexical_cast<std::string>(response->body_size)));
	}

	response->send(*socket);
	if (response->status != 200)
		return;

	writer* new_writer = NULL;
	switch (type)
	{
	case WRITER_CLIENT:
		new_writer = new writer(socket, dump);
		this->writers[nickname] = new_writer;

		new_writer->process();

		this->writers.erase(nickname);
		delete new_writer;

		break;
	case READER_CLIENT:
		this->writers[nickname]->connect_reader(socket, dump);
		break;
	}
}

void observer_service::apply_config(boost::shared_ptr<boost::property_tree::ptree> config)
{
	this->max_streams = config->get<int>("max_streams", this->max_streams);
	this->dumps_location = config->get<std::string>("dumps_location", this->dumps_location.string());
	this->dump_writers = config->get<bool>("dump_writers", this->dump_writers);
	this->dump_readers = config->get<bool>("dump_readers", this->dump_readers);
}

bool observer_service::check_nickname(std::string& nickname)
{
	if (nickname.empty())
		return false;

	bool result = true;
	for (char* c = const_cast<char*>(nickname.c_str()); *c != '\0'; ++c)
		if (!isalnum(*c))
			result = false;

	return result;
}

std::string observer_service::get_current_date_time()
{
	boost::local_time::local_date_time now = boost::local_time::local_sec_clock::local_time(boost::local_time::time_zone_ptr());
	boost::local_time::local_time_facet* facet(new boost::local_time::local_time_facet("%Y-%m-%d-%H-%M-%S"));

	std::ostringstream result;
	result.imbue(std::locale(std::cout.getloc(), facet));
	result << now;

	return result.str();
}

std::string observer_service::service_check( boost::shared_ptr<http_request> request, boost::shared_ptr<shared> shared_data )
{
	std::string url= request->url;
	if ((url == "/users.json" ) || (request->arguments["action"] == "write") || (request->arguments["action"] == "read" ) )
	{
		return "executor";
	}
	return "not for me";
}
BOOST_EXTENSION_TYPE_MAP_FUNCTION
{
	std::map<std::string, boost::extensions::factory<base_service> > &factories(types.get());
	factories["observer_service"].set<observer_service>();
}
