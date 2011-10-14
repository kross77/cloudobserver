#include "users_files_service.h"

BOOST_EXTENSION_TYPE_MAP_FUNCTION
{
	std::map<std::string, boost::extensions::factory<service> > &factories(types.get());
	factories["users_files_service"].set<users_files_service>();
}

users_files_service::users_files_service()
{
	general_util = new general_utils();
	http_util = new http_utils();
	this->root_path = boost::filesystem::current_path().string();

	this->expiration_period = boost::posix_time::minutes(200);
	this->max_age = "max-age=" + boost::lexical_cast<std::string>(this->expiration_period.total_seconds());

}

void users_files_service::service_call( boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response )
{

}

void users_files_service::apply_config( boost::property_tree::ptree config )
{
	this->root_path = config.get<std::string>("users_files_directory", this->root_path.string());
}