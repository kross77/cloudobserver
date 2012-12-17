#ifndef RUN_SERVICE_H
#define RUN_SERVICE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <iterator>
#include <math.h>

//Boost
#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/regex.hpp>
#include <boost/progress.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/stream.hpp>


// Boost Extension
#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>

//SQLite
#include <sqlite3pp.h>

//CF-UTIL
#include <general_utils.h>
#include <http_utils.h>
#include <timer.h>
#include <fs_utils.h>
#include <log_util.h>
#include <thread_group.h>

//SERVICE INTERFACE
#include <http_service.hpp>

// Boost Process
#include <boost/process.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>

#include "db_commander.h"

#ifndef RUN_UTILS
#define RUN_UTILS
namespace utils{

#ifdef WIN 
	static const std::string platform = "Windows";
#else
#ifdef LIN
	static const std::string platform = "Linux";
#else
#ifdef MAC
	static const std::string platform = "Mac";
#endif
#endif
#endif

	template<class T>
	inline T &empty_class()
	{
		static T pt;
		return pt;
	}

#if defined(BOOST_WINDOWS_API)
	std::wstring str(std::string s){
		std::wstring result;
		result.assign(s.begin(), s.end());
		return result;
	}
#elif defined(BOOST_POSIX_API)
	std::string str(std::string s){
		return s;
	}
#endif

#if defined(BOOST_WINDOWS_API)
	std::wstring cmd(std::string s){
		return str("cmd /c ") + str(s);
	}
#elif defined(BOOST_POSIX_API)
	std::string cmd(std::string s){
		return str("sh -c '") + str(s) + str("'");
	}
#endif

	class task
	{
	public:
		std::string base;

		std::map<std::string, std::string> name_type;
		std::map<std::string, std::string> name_label;

		std::map<std::string, int> int_args;
		std::map<std::string, std::string> string_args;

		std::string serialize_base()
		{
			std::stringstream oa_ss_req;
			boost::archive::text_oarchive  oa_request(oa_ss_req);
			oa_request << *this;
			return oa_ss_req.str();
		}

		void deserialize_base( std::string request_string)
		{
			std::stringstream ia_ss_req;
			ia_ss_req << request_string;
			boost::archive::text_iarchive ia_req(ia_ss_req);
			ia_req >> *this;	 
		}
	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & base;

			ar & int_args;
			ar & string_args;

			ar & name_type;
			ar & name_label;
		}
	};

	struct appDescrioption
	{
		std::string name;
		std::string text;
		std::string icon;
	};

	struct app
	{
		std::string process_id;
		bool use_shell;
		std::string process_name;
		appDescrioption description;
		task task_base;
	};
};

#endif // RUN_UTILS

class run_service: public http_service
{
public:
	run_service(){
		this->root_path = boost::filesystem::current_path() / "run";
	}

	virtual std::string service_check(boost::shared_ptr<http_request> request, boost::shared_ptr<shared> shared_data){
		std::string url= request->url;
		if ((url == "/run.service") || (url == "/run.json")) 
		{
			return "executor";
		}
		return "not for me";
	}

	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request,  boost::shared_ptr<shared> shared_data){
		boost::shared_ptr<http_response> response(new http_response());

		std::string user_name = fs_utils::get_user_name(shared_data);

		if( (user_name != "guest") && (user_name != ""))
		{
			if(request->url == "/run.service"){
				if (boost::iequals(request->arguments["action"], "list_apps"))
				{
					list_apps(socket, response, request);
				}else if (boost::iequals(request->arguments["action"], "list_args") && !request->arguments["pid"].empty())
				{
					list_app_args(request->arguments["pid"], socket, response, request);
				}
				else if (boost::iequals(request->arguments["action"], "call") && !request->arguments["pid"].empty())
				{
					call_app(user_name, request->arguments["pid"], socket, response, request);
				}
			}else if(request->url == "/run.json"){

				if (boost::iequals(request->method, "POST"))
				{
					if(request->body.length() > 0)
					{

						std::map<std::string, std::string> save_file; 
						save_file = http_utils::parse_multipart_form_data(request->body);
						if (save_file.empty())
						{
							if (boost::iequals(request->arguments["action"], "remove_tasks"))
							{
								boost::char_separator<char> sep(", ");
								boost::tokenizer<boost::char_separator<char> > tokens(request->body, sep);
								bool good;
								BOOST_FOREACH(std::string t, tokens)
								{

									good = cancel_task( user_name,  t );
									if(!good)
										break;

								}
								if(good)
									return http_utils::send_json(std::pair<std::string, std::string>("success","true"),  socket, response, request); 

								http_utils::send_json(std::pair<std::string, std::string>("success","false"),  socket, response, request); 
								return;
							}
						}
					}
				}

				if (boost::iequals(request->arguments["action"], "list_tasks"))
				{
					list_user_tasks(user_name, socket, response, request );
				}else if (boost::iequals(request->arguments["action"], "list_output") && !request->arguments["encoded_url"].empty())
				{
					list_task_output( user_name,  request->arguments["encoded_url"], socket, response, request );
				}else if (boost::iequals(request->arguments["action"], "remove_task") && !request->arguments["encoded_url"].empty())
				{
					cancel_task( user_name,  request->arguments["encoded_url"], socket, response, request );
				}
			}
			return;
		}

		http_utils::send("Guest, hello from run service!", socket, response, request);
	}

	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree> config){
		this->root_path = config->get<std::string>("run_service_files_directory", this->root_path.string());
		std::string db_name = config->get<std::string>("database",  "rs.db");
		std::string log_name = config->get<std::string>("log",  "rs.log");
		this->threads_per_user = config->get<int>("threading.<xmlattr>.peruser",  2);
		this->threads_totall = config->get<int>("threading.<xmlattr>.total",  10);

		start_work_with_lu(log_name);

		if(!db){
			db = boost::shared_ptr<db_commander> (new db_commander(db_name, lu));
		}

		BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
			config->get_child("applications", utils::empty_class<boost::property_tree::ptree>()))
		{
			boost::property_tree::ptree individual_application_tree = (boost::property_tree::ptree) v.second ;
			std::string platform = individual_application_tree.get<std::string>("description.<xmlattr>.platform",  "");	

			if (platform != utils::platform && !platform.empty())
			{
				continue;
			}

			boost::shared_ptr<utils::app> a(new utils::app());
			a->use_shell = individual_application_tree.get<bool>("<xmlattr>.useShell",  false);
			a->process_name = individual_application_tree.get<std::string>("<xmlattr>.processName");

			a->description.name = individual_application_tree.get<std::string>("description.<xmlattr>.appName",  "default name");	
			a->description.text = individual_application_tree.get<std::string>("description",  "default descroiption");
			a->description.icon = individual_application_tree.get<std::string>("description.<xmlattr>.icon",  "default icon");	

			a->task_base.base = individual_application_tree.get<std::string>("arguments.<xmlattr>.base",  "");	



			BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
				individual_application_tree.get_child("arguments", utils::empty_class<boost::property_tree::ptree>()))
			{

				boost::property_tree::ptree individual_argument = (boost::property_tree::ptree) v.second ;
				std::string arg_type = individual_argument.get<std::string>("<xmlattr>.type",  "");
				std::string arg_name = individual_argument.get<std::string>("<xmlattr>.name",  "");
				std::string arg_label = individual_argument.get<std::string>("<xmlattr>.label",  "");
				boost::algorithm::to_lower(arg_type);
				boost::algorithm::to_lower(arg_name);
				a->task_base.name_type[arg_name] = arg_type;
				a->task_base.name_label[arg_name] = arg_label;
			}

			a->process_id = individual_application_tree.get<std::string>("<xmlattr>.id");
			apps[a->process_id] = a;
		}

		boost::filesystem::remove_all(boost::filesystem::path(this->root_path));
		threads_pool_generator();
	}

	virtual void start(){}

	virtual void stop(){}

private:
	class user_task_pool{
	public:
		std::string user_name;
		boost::asio::io_service tasks;
		boost::asio::io_service::work *work;
		thread_group threads;
		run_service * parent;

		user_task_pool(int create_threads, run_service * parent, std::string user_name): user_name(user_name), parent(parent)
		{
			work = new boost::asio::io_service::work(tasks);
			for (std::size_t i = 0; i < create_threads; ++i)
			{
				boost::shared_ptr<boost::thread> thread;
				thread = boost::shared_ptr<boost::thread>( new boost::thread(boost::bind(&user_task_pool::run, this, thread)));
				threads.add(thread);
			}
		}

		void post(boost::shared_ptr<boost::packaged_task<void> > pt, std::string tid)
		{
			tasks.post(boost::bind(&user_task_pool::pool_item<void>, this, pt, tid, user_name));
		}

	private:
		void run(boost::shared_ptr<boost::thread> thread_ptr)
		{
			try
			{
				tasks.run();
			}		
			catch(std::exception &e)
			{
				std::cout << e.what() << std::endl;
				boost::shared_ptr<boost::thread> thread;
				thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&user_task_pool::run, this, thread)));
				threads.add(thread);
				threads.remove(thread_ptr);
				return;
			}
		}

		template <class task_return_t>
		void pool_item( boost::shared_ptr< boost::packaged_task<task_return_t> > pt, std::string tid, std::string user_name)
		{
			boost::shared_ptr < boost::packaged_task<void> > task (  new boost::packaged_task<void> ( boost::bind(&run_service::run_item<task_return_t>, parent, pt)));
			boost::unique_future<void> fi= task->get_future();

			boost::shared_ptr<boost::promise<boost::thread::id> > started(new boost::promise<boost::thread::id>());
			boost::unique_future<boost::thread::id> has_started = started->get_future();

			if(parent->db->get_if_is_canceled(user_name, tid)){
				parent->remove_task(tid);	
				return;
			}

			parent->internal_tasks.post(boost::bind(&run_service::run_item<task_return_t>, parent, task, started));

			has_started.wait();
			if(has_started.has_exception())
				return;

			boost::thread::id id = has_started.get();

			while( (!(fi.has_value())) && (!(fi.has_exception())) ){
				fi.timed_wait(boost::posix_time::milliseconds(100));
				if(parent->db->get_if_is_canceled(user_name, tid))
				{
					boost::shared_ptr<boost::thread> internal_thread;
					internal_thread = boost::shared_ptr<boost::thread>( new boost::thread(boost::bind(&run_service::internal_run, parent, internal_thread)));
					parent->internal_threads.add(internal_thread);
					parent->internal_threads.remove(id)->interrupt();
					parent->remove_task(tid);
				}
			}
		}
	};
	friend class db_commander;

	boost::shared_ptr<db_commander> db;
	std::map<std::string, boost::shared_ptr<utils::app> > apps;
	boost::shared_ptr<log_util> lu;


	std::map<std::string, boost::shared_ptr<user_task_pool> > user_threads;
	thread_group internal_threads;
	boost::asio::io_service internal_tasks;
	boost::asio::io_service::work *internal_work;

	boost::filesystem::path root_path;
	int threads_totall;
	int threads_per_user;

	void threads_pool_generator()
	{
		internal_work = new boost::asio::io_service::work(internal_tasks);

		for (std::size_t i = 0; i < this->threads_totall; ++i)
		{
			boost::shared_ptr<boost::thread> internal_thread;
			internal_thread = boost::shared_ptr<boost::thread>( new boost::thread(boost::bind(&run_service::internal_run, this, internal_thread)));
			internal_threads.add(internal_thread);
		}

	}

	void internal_run(boost::shared_ptr<boost::thread> internal_thread_ptr)
	{
		try
		{
			internal_tasks.run();
		}		
		catch(std::exception &e)
		{
			boost::shared_ptr<boost::thread> internal_thread;
			internal_thread = boost::shared_ptr<boost::thread>( new boost::thread(boost::bind(&run_service::internal_run, this, internal_thread)));
			internal_threads.add(internal_thread);
			internal_threads.remove(internal_thread_ptr);
			return;
		}
	}

	template <class task_return_t>
	void run_item( boost::shared_ptr< boost::packaged_task<task_return_t> > pt, boost::shared_ptr<boost::promise<boost::thread::id> > started)
	{
		started->set_value(boost::this_thread::get_id());

		run_item<task_return_t>(pt);
	}

	template <class task_return_t>
	void run_item( boost::shared_ptr< boost::packaged_task<task_return_t> > pt)
	{
		(*pt)();
	}

	void start_work_with_lu( std::string lu_path )
	{
		static bool is_lu_set = false;
		if (!is_lu_set)
		{
			this->lu = boost::shared_ptr<log_util>(new log_util(1, false, true, true, lu_path));
			is_lu_set = true;
		}

	}

	std::vector<std::string> split(const std::string& s, const std::string& delim, const bool keep_empty = false) {
		std::vector<std::string> result;
		if (delim.empty()) {
			result.push_back(s);
			return result;
		}
		std::string::const_iterator substart = s.begin(), subend;
		while (true) {
			subend = search(substart, s.end(), delim.begin(), delim.end());
			std::string temp(substart, subend);
			if (keep_empty || !temp.empty()) {
				result.push_back(temp);
			}
			if (subend == s.end()) {
				break;
			}
			substart = subend + delim.size();
		}
		return result;
	}

	std::string filter_args(std::string args)
	{
		return boost::erase_all_regex_copy(args, boost::regex("[^a-zA-Z0-9=\"/.: -]+"));
	}

	boost::process::child start_child(
		const std::string & tid,
		const std::string & pid,
		std::string arguments,
		boost::iostreams::file_descriptor_sink sink,
		boost::iostreams::file_descriptor_sink sinkerr,
		boost::filesystem::path work_directory,
		bool use_shall = false) 
	{ 
		using namespace boost::process;
		using namespace boost::process::initializers;
		boost::filesystem::path path_to_exec;
		if (use_shall)
		{
			path_to_exec = shell_path();
			return execute(
				run_exe(path_to_exec),
				set_cmd_line(utils::cmd(apps[pid]->process_name + " " + filter_args(arguments))), //set_cmd_line(L"cmd /c echo %CD%"),
				start_in_dir(work_directory),
				inherit_env(),
				bind_stdout(sink),
				bind_stderr(sinkerr)
				);
		}
		else
		{
			path_to_exec = apps[pid]->process_name;
			return execute(
				run_exe(path_to_exec),
				set_cmd_line(utils::str(path_to_exec.string()) + utils::str(" ") + utils::str(filter_args(arguments))), //set_cmd_line(L"cmd /c echo %CD%"),
				start_in_dir(work_directory),
				inherit_env(),
				bind_stdout(sink),
				bind_stderr(sinkerr)
				);
		}
	}

	//remove by encoded_url
	bool remove_task(const std::string & encoded_url )
	{	bool result = false;	
	sqlite3pp::transaction xct(*(db->get_db()), true);
	{
		sqlite3pp::command cmd(*(db->get_db()), db->command_delete_task.c_str());
		cmd.bind(":encoded_url", encoded_url);
		if(cmd.execute() == 0)
		{
			boost::filesystem::remove_all(boost::filesystem::path(this->root_path / encoded_url));
			result = true;
		}
	}
	xct.commit();
	return result;
	}

	//remove if canceled or finished; cancel in other case
	bool remove_task(const std::string & encoded_url,const std::string & user_name)
	{
		int canceled=0;
		std::string status = "";
		if(db->get_if_users_task(encoded_url, user_name, status, canceled)){
			if( (canceled == 1) || boost::iequals(status, "finished"))
				return remove_task(encoded_url);

			db->set_canceled_task(encoded_url, user_name);
			return true;
		}
		return false;
	}

	bool cancel_task(const std::string & user_name, const std::string & pid)
	{
		if(db->get_if_users_task(pid, user_name))
			return remove_task(pid, user_name);
		return false;
	}

	void cancel_task(const std::string & user_name, const std::string & pid, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request)
	{
		http_utils::set_json_content_type(response);
		if(cancel_task(user_name, pid))
			return http_utils::send_json(std::make_pair("request", "accepted"), socket, response, request);

		return http_utils::send_json(std::make_pair("request", "declined"), socket, response, request);
	}

	void list_task_output( const std::string & user_name,  const std::string & encoded_url, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request )
	{
		std::ostringstream user_tasks_stream;
		user_tasks_stream << "\n\t{\n\t\t\"href\": \""
			<< encoded_url << "\",\n\t\t\"output\": \""
			<< http_utils::url_encode(http_utils::escape(db->get_task_output(user_name, encoded_url)))  << "\"\n\t}";

		std::string files_ = user_tasks_stream.str();

		http_utils::set_json_content_type(response);
		http_utils::send(files_, socket, response, request);
		return;
	}

	void list_user_tasks( const std::string & user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request )
	{
		std::ostringstream user_tasks_stream;
		user_tasks_stream << "[";

		sqlite3pp::query qry(*(db->get_db()), db->command_find_all_user_tasks.c_str());
		qry.bind(":user_name", user_name);

		for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
			std::string encoded_url, status, pid, modified;
			(*i).getter() >>  encoded_url >> status >> pid >> modified ;

			user_tasks_stream << "\n\t{\n\t\t\"encoded_url\": \""
				<< encoded_url << "\",\n\t\t\"status\": \""
				<< status << "\",\n\t\t\"pid\": \""
				<< pid << "\",\n\t\t\"modified\": \""
				<< modified << "\"\n\t},";
		}

		std::string files_ = user_tasks_stream.str();
		if (files_.length() > 5)
			files_ = files_.substr(0, files_.length() - 1);
		http_utils::set_json_content_type(response);
		http_utils::send(files_.append("\n]"), socket, response, request);
		return;
	}

	void execute_task(const std::string & tid, const std::string & user_name, const std::string & pid, utils::task t)
	{
		try{
			boost::shared_ptr<utils::app> a = apps[pid];

			typedef std::pair<std::string, std::string > ss_pair;
			std::string args = t.base;
			BOOST_FOREACH(ss_pair p, t.name_type ){
				if((boost::iequals(p.second, "int")) && (t.int_args[p.first] != 0))
					boost::algorithm::replace_all(args, ":" +  p.first, boost::lexical_cast<std::string>(t.int_args[p.first]));
				else if((boost::iequals(p.second, "string")) && (!t.string_args[p.first].empty()))
					boost::algorithm::replace_all(args, ":" + p.first, t.string_args[p.first]);
			}

			if(db->get_if_is_canceled(user_name, tid))
				remove_task(tid);

			db->set_started_task(tid, user_name);

			boost::filesystem::path work_directory = root_path / tid;
			general_utils::create_directory(work_directory);
			boost::iostreams::file_descriptor_sink sink(work_directory / "stdout.txt" );
			boost::iostreams::file_descriptor_sink sinkerr(work_directory / "stderr.txt" );

			boost::process::child c = this->start_child(tid, pid, args, sink, sinkerr, work_directory, a->use_shell); 

			boost::process::wait_for_exit(c);

			boost::filesystem::path err_path = work_directory / "stderr.txt";
			if(boost::filesystem::file_size(err_path) != 0)
			{

				boost::filesystem::ifstream out;
				out.open(err_path);
				std::string out_str;
				while ( out )
				{
					std::string s;
					std::getline( out, s );
					out_str+=s;
				}
				std::string out_line = db->get_task_output(user_name, tid) + "\Output: " + out_str;
				db->set_task_output(tid, user_name, out_line);
			}

			boost::filesystem::path out_path = work_directory / "stdout.txt";
			if(boost::filesystem::file_size(out_path) != 0)
			{

				boost::filesystem::ifstream out;
				out.open(out_path);
				std::string out_str;
				while ( out )
				{
					std::string s;
					std::getline( out, s );
					out_str+=s;
				}
				std::string out_line = db->get_task_output(user_name, tid) + "\Output: " + out_str;
				db->set_task_output(tid, user_name, out_line);
			}

			db->set_finish_task(tid, user_name);

		}catch(std::exception &e)
		{
			*lu << "error!" << log_util::endl; 
			*lu << e.what() << log_util::endl; 

			std::string output_line = db->get_task_output(user_name, tid) + e.what(); 
			db->set_task_output(tid, user_name, output_line );

			db->set_status_on_task(tid, user_name, "error");
		}
	}

	void call_app(const std::string & user_name, const std::string & pid, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request)
	{
		if (!user_threads[user_name])
		{
			user_threads[user_name] = boost::shared_ptr<user_task_pool>(new user_task_pool(this->threads_per_user, this, user_name));
		}

		try{
			boost::shared_ptr<utils::app> a= apps[pid];
			typedef std::pair<std::string, std::string > name_type_pair;
			utils::task t;
			t = a->task_base;
			BOOST_FOREACH(name_type_pair v, a->task_base.name_type){
				if((!v.first.empty()) && (!request->arguments[v.first].empty())){
					if(boost::iequals(v.second, "int" ))
						t.int_args[v.first]=	boost::lexical_cast<int>(request->arguments[v.first]);
					else if(boost::iequals(v.second, "string" ))
						t.string_args[v.first]=	http_utils::url_decode(request->arguments[v.first]);
				}
			}
			std::string tid = user_name + t.serialize_base() + general_utils::get_utc_now_time();
			tid = general_utils::get_sha256(tid);

			db->create_task_table_entry(tid, user_name, t.serialize_base(), pid);

			boost::shared_ptr< boost::packaged_task<void> > pt(new boost::packaged_task<void>(boost::bind(&run_service::execute_task, this, tid, user_name,pid, t)));
			user_threads[user_name]->post(pt, tid);

			http_utils::set_json_content_type(response);
			http_utils::send_json(std::make_pair("request", "accepted"), socket, response, request);
			return;
		}catch(std::exception &e)
		{
			*lu << e.what() <<log_util::endl;
			http_utils::send_json(std::make_pair("request", "declined"), socket, response, request);
		}
	}

	void list_apps(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request )
	{
		std::ostringstream apps_stream;
		apps_stream << "[";

		typedef std::pair<std::string, boost::shared_ptr<utils::app> > pid_app;
		BOOST_FOREACH(pid_app v, apps){
			boost::shared_ptr<utils::app> a= v.second;
			apps_stream << "\n\t{\n\t\t\"text\": \""
				<< a->description.name << "\",\n\t\t\"description\": \""
				<< a->description.text << "\",\n\t\t\"imageSrc\": \""
				<< a->description.icon << "\",\n\t\t\"pid\": \""
				<< a->process_id << "\"\n\t},";

		}

		std::string files_ = apps_stream.str();
		if (files_.length() > 5)
			files_ = files_.substr(0, files_.length() - 1);
		http_utils::set_json_content_type(response);
		http_utils::send(files_.append("\n]"), socket, response, request);
		return;
	}

	void list_app_args(const std::string & pid, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request)
	{
		std::ostringstream apps_stream;
		apps_stream << "[";
		boost::shared_ptr<utils::app> a= apps[pid];
		typedef std::pair<std::string, std::string > name_label_pair;
		BOOST_FOREACH(name_label_pair v, a->task_base.name_label){
			if(!v.first.empty())
				apps_stream << "\n\t{\n\t\t\"name\": \""
				<< v.first << "\",\n\t\t\"description\": \""
				<< v.second << "\",\n\t\t\"type\": \""
				<< a->task_base.name_type[v.first] << "\"\n\t},";

		}

		std::string files_ = apps_stream.str();
		if (files_.length() > 5)
			files_ = files_.substr(0, files_.length() - 1);
		http_utils::set_json_content_type(response);
		http_utils::send(files_.append("\n]"), socket, response, request);
		return;
	}

};

#endif // RUN_SERVICE_H