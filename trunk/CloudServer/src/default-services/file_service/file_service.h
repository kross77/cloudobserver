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

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/stream.hpp>

// Boost Extension
#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>

#include <general_utils.h>
#include <http_utils.h>

#include <service.hpp>

#include <fs_file.h>
#include <fs_map.h>
#include <fs_concurrent_queued_map.h>
#include <fs_utils.h>


class file_service: public service
{
public:
	file_service();
	virtual std::string service_check(boost::shared_ptr<http_request>, boost::shared_ptr<shared>);
	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request,  boost::shared_ptr<shared> shared_data);
	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree> config);
	virtual void start(){}
	virtual void stop(){}
private:
	std::string get_user_name(boost::shared_ptr<http_request> request);

	boost::filesystem::path root_path;
	bool show_directory_contents;

	boost::filesystem::path users_directory_path;

	bool first_time;

	boost::uintmax_t cach_size_limit;
	boost::uintmax_t current_cach_size;
	boost::uintmax_t cachable_file_size_limit;

	boost::timer timerFame;
	long long desiredTimeFame;
	long long spendedTimeFame;
	boost::posix_time::ptime oldTime;
	boost::posix_time::ptime nowTime;

	fs_map fs;
	std::set<std::string> new_fs;
	fs_concurrent_queued_map cached_files;

	boost::shared_ptr<std::string> cach_file(boost::shared_ptr<fs_file> f);
	boost::shared_ptr<fs_file> create_file( boost::filesystem::path p );
	void create_file(boost::filesystem::path p, fs_map &m1, std::set<std::string> &m2);
	void create_file(boost::filesystem::path p, std::set<std::string> &m);
	std::string encode_path(boost::filesystem::path &p);
	void files_walker();
	void is_dir( boost::filesystem::path dir, fs_map &old_fs, std::set<std::string> &new_fs );
	bool is_directory_call(std::string &s);
	void is_file(boost::filesystem::path p, fs_map &old_fs, std::set<std::string> &new_fs);

	boost::shared_ptr<std::string> load_file_into_memory(boost::shared_ptr<fs_file> f);
	void process_request(std::string encoded_url,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);

	//void send_cached_file(boost::uintmax_t size, boost::shared_array<char> buffer, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response);
	void send_cached_file( boost::uintmax_t size, boost::shared_ptr<std::string> buffer, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request );
	void send_directory_contents(std::set<std::string> list,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response);
	bool if_is_modified(boost::shared_ptr<fs_file> f, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request);
	bool try_send_info( boost::shared_ptr<fs_file> f,boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response );
};

#endif // FILE_SERVICE_H
