#ifndef OBSERVER_SERVICE_H
#define OBSERVER_SERVICE_H

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
#include <http_utils.h>

#include <http_service.hpp>

#include "writer.h"

class observer_service: public http_service
{
public:
	observer_service();
	~observer_service();

	virtual std::string service_check(boost::shared_ptr<http_request> request, boost::shared_ptr<shared> shared_data);

	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request,  boost::shared_ptr<shared> shared_data);
	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree> config);
	virtual void start(){} // TODO: implement
	virtual void stop(){} // TODO: implement
private:
	static bool check_nickname(std::string& nickname);
	static std::string get_current_date_time();

	enum client_type { GENERAL_CLIENT, WRITER_CLIENT, READER_CLIENT };

	int max_streams;
	boost::filesystem::path dumps_location;
	bool dump_writers;
	bool dump_readers;

	std::map<std::string, writer*> writers;
};

#endif // OBSERVER_SERVICE_H
