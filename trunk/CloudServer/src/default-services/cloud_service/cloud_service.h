#ifndef CLOUD_SERVICE_H
#define CLOUD_SERVICE_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>

// Boost
#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

// Boost Extension
#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>

// CF
#include <http.h>

#include "../../../service-interface/service.hpp"

#include "cloud_writer.h"

class cloud_service: public service
{
public:
	cloud_service(boost::property_tree::ptree config);
	~cloud_service();
	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, http_request request, http_response response);
private:
	static bool check_nickname(std::string& nickname);
	static std::string get_current_date_time();

	enum client_type { GENERAL_CLIENT, WRITER_CLIENT, READER_CLIENT };

	int max_streams;
	boost::filesystem::path dumps_location;
	bool dump_writers;
	bool dump_readers;

	std::map<std::string, cloud_writer*> writers;
};

#endif // CLOUD_SERVICE_H
