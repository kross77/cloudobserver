#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>

// Boost
#include <boost/cstdint.hpp> //boost::uintmax_t
#include <boost/asio.hpp>
#include <boost/timer.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/shared_array.hpp>
#include <boost/foreach.hpp>
// Boost Extension
#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>

#include <general_utils.h>
#include <http_utils.h>

#include <service.hpp>

#include "fs_file.h"
#include "fs_map.h"
#include "fs_concurrent_queued_map.h"


class file_service: public service
{
public:
	file_service();
	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);
	virtual void apply_config(boost::property_tree::ptree config);
	virtual void start(){}
	virtual void stop(){}
private:
	std::string get_user_name(boost::shared_ptr<http_request> request);

	boost::filesystem::path root_path;
	bool show_directory_contents;
	boost::posix_time::time_duration expiration_period;
	general_utils *general_util;
	http_utils *http_util;
	boost::filesystem::path users_directory_path;
	std::string max_age;
	bool first_time;

	boost::uintmax_t cach_size_limit;
	boost::uintmax_t current_cach_size;
	boost::uintmax_t cachable_file_size_limit;

	boost::timer timerFame;
	int64_t desiredTimeFame;
	int64_t spendedTimeFame;
	boost::posix_time::ptime oldTime;
	boost::posix_time::ptime nowTime;

	fs_map fs;
	std::set<std::string> new_fs;
	concurrent_queued_map<std::string, boost::shared_ptr<fs_file> > cached_files;

	boost::shared_array<char> cach_file(boost::shared_ptr<fs_file> f);
	boost::shared_ptr<fs_file> create_file(boost::filesystem::path p);
	void create_file(boost::filesystem::path p, fs_map &m1, std::set<std::string> &m2);
	void create_file(boost::filesystem::path p, std::set<std::string> &m);
	std::string encode_path(boost::filesystem::path &p);
	void files_walker();
	void is_dir( boost::filesystem::path dir, fs_map &old_fs, std::set<std::string> &new_fs );
	bool is_directory_call(std::string &s);
	void is_file(boost::filesystem::path p, fs_map &old_fs, std::set<std::string> &new_fs);
	void insert_file_headers( boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response );
	boost::shared_array<char> load_file_into_memory(boost::shared_ptr<fs_file> f);
	void process_request(std::string encoded_url,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);
	void send_not_modified_304( boost::shared_ptr<boost::asio::ip::tcp::socket> socket,  boost::shared_ptr<http_response> response );
	void save_string_into_file(std::string contents, std::string name);
	void send_cached_file(boost::uintmax_t size, boost::shared_array<char> buffer, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response);
	void send_uncachable_file(boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response);
	void send_directory_contents(std::set<std::string> list,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);
	void send_404(std::string encoded_url,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);
	void send_info(boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);
};

#endif // FILE_SERVICE_H
