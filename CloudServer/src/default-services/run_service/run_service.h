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

namespace utils{
	template<class T>
	inline T &empty_class()
	{
		static T pt;
		return pt;
	}

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


class run_service: public http_service
{ 
public:
	run_service(){
		this->root_path = boost::filesystem::current_path() / "run";
		this->command_create_tasks_table = "CREATE TABLE IF NOT EXISTS tasks (encoded_url varchar(300) UNIQUE NOT NULL primary key, output BLOB default \"starting:\n\", task BLOB NOT NULL, status varchar(65) default \"not ready\", pid varchar(100) NOT NULL, user_name varchar(65) NOT NULL, started DATETIME, finished DATETIME, modified DATETIME NOT NULL default CURRENT_TIMESTAMP, canceled BOOLEAN  NOT NULL default 0)";
		this->command_post_task =  "INSERT INTO tasks (user_name, encoded_url, task, status, pid ) VALUES (:user_name, :encoded_url, :task, :status, :pid)";
		this->command_cancel_task = "UPDATE tasks SET canceled=1, modified=CURRENT_TIMESTAMP WHERE ( user_name=:user_name and encoded_url=:encoded_url )";
		this->command_start_task = "UPDATE tasks SET status=:status, modified=CURRENT_TIMESTAMP, started=CURRENT_TIMESTAMP  WHERE ( user_name=:user_name and encoded_url=:encoded_url )";
		this->command_finish_task = "UPDATE tasks SET status=:status, finished=CURRENT_TIMESTAMP, modified=CURRENT_TIMESTAMP  WHERE ( user_name=:user_name and encoded_url=:encoded_url )";
		this->command_status_task = "UPDATE tasks SET status=:status, modified=CURRENT_TIMESTAMP WHERE ( user_name=:user_name and encoded_url=:encoded_url )";
		this->command_change_task_output = "UPDATE tasks SET output=:output, modified=CURRENT_TIMESTAMP WHERE ( user_name=:user_name and encoded_url=:encoded_url )";
		this->command_find_all_user_tasks = "SELECT encoded_url, status, pid, modified FROM tasks WHERE user_name=:user_name AND canceled=0 ";
		this->command_is_canceled = "SELECT canceled FROM tasks WHERE user_name=:user_name AND encoded_url=:encoded_url ";
		this->command_get_output = "SELECT output FROM tasks WHERE user_name=:user_name AND encoded_url=:encoded_url ";
		this->command_delete_task = "DELETE FROM tasks WHERE encoded_url=:encoded_url";
		this->command_find_task = "SELECT user_name, pid, modified, canceled FROM tasks WHERE encoded_url=:encoded_url";
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
		start_work_with_db(db_name);

		BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
			config->get_child("applications", utils::empty_class<boost::property_tree::ptree>()))
		{
			boost::property_tree::ptree individual_application_tree = (boost::property_tree::ptree) v.second ;
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

	std::map<std::string, boost::shared_ptr<utils::app> > apps;
	boost::shared_ptr<log_util> lu;
	boost::shared_ptr<sqlite3pp::database> db;
	std::string command_create_tasks_table;
	std::string post_task;


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

			if(parent->db_get_if_is_canceled(user_name, tid)){
				parent->db_delete_task(tid,user_name);	
				return;
			}

			parent->internal_tasks.post(boost::bind(&run_service::run_item<task_return_t>, parent, task, started));

			has_started.wait();
			if(has_started.has_exception())
				return;

			boost::thread::id id = has_started.get();

			while( (!(fi.has_value())) && (!(fi.has_exception())) ){
				fi.timed_wait(boost::posix_time::milliseconds(100));
				if(parent->db_get_if_is_canceled(user_name, tid))
				{
					boost::shared_ptr<boost::thread> internal_thread;
					internal_thread = boost::shared_ptr<boost::thread>( new boost::thread(boost::bind(&run_service::internal_run, parent, internal_thread)));
					parent->internal_threads.add(internal_thread);
					parent->internal_threads.remove(id)->interrupt();
					parent->db_delete_task(tid,user_name);
				}
			}
		}
	};

	std::map<std::string, boost::shared_ptr<user_task_pool> > user_threads;
	thread_group internal_threads;
	boost::asio::io_service internal_tasks;
	boost::asio::io_service::work *internal_work;

	int time_limit;
	std::string command_post_task;
	std::string command_cancel_task;
	std::string command_start_task;
	std::string command_finish_task;
	std::string command_change_task_output;
	std::string command_find_all_user_tasks;
	std::string command_is_canceled;
	std::string command_get_output;
	std::string command_delete_task;
	std::string command_find_task;
	boost::filesystem::path root_path;
	std::string command_status_task;
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

	void start_work_with_db(const std::string& db_name)
	{
		static bool is_db_set = false;
		if (!is_db_set)
		{
			boost::shared_ptr<sqlite3pp::database> db_( new sqlite3pp::database(db_name.c_str()));
			this->db = db_;

			*lu << "Connected to "<< db_name << " database and created a table with SQLite return code: " << db->execute(command_create_tasks_table.c_str()) << log_util::endl;
		}
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

	boost::process::child start_child(std::string tid, std::string pid, std::string arguments, bool use_shall = false) 
	{ 
		boost::filesystem::path path_to_exec (apps[pid]->process_name);
		std::string exec = path_to_exec.string();
		boost::process::context ctx; 
		ctx.environment = boost::process::self::get_environment();
		ctx.work_directory = (root_path / tid).normalize().string();
		ctx.stdout_behavior =  boost::process::capture_stream(); 

		if(use_shall) 
			return  boost::process::launch_shell(exec + " " + filter_args(arguments), ctx); 

		return  boost::process::launch(exec, split(std::string(path_to_exec.string() + " " + filter_args(arguments)), " "), ctx); 
	} 


	void db_set_task_output( std::string encoded_url, std::string user_name, std::string output )
	{
		sqlite3pp::transaction xct(*db);
		sqlite3pp::command cmd(*db, command_finish_task.c_str());
		cmd.bind(":encoded_url", encoded_url) ;
		cmd.bind(":output", output) ;
		cmd.bind(":user_name", user_name) ;
		cmd.execute() ;
		xct.commit();
	}

	void db_set_finish_task( std::string encoded_url, std::string user_name )
	{
		sqlite3pp::transaction xct(*db);
		sqlite3pp::command cmd(*db, command_finish_task.c_str());
		cmd.bind(":encoded_url", encoded_url) ;
		cmd.bind(":status", "finished") ;
		cmd.bind(":user_name", user_name) ;
		cmd.execute() ;
		xct.commit();
	}

	void db_set_status_on_task( std::string encoded_url, std::string user_name, std::string status )
	{
		sqlite3pp::transaction xct(*db);
		sqlite3pp::command cmd(*db, command_status_task.c_str());
		cmd.bind(":encoded_url", encoded_url) ;
		cmd.bind(":status", status) ;
		cmd.bind(":user_name", user_name) ;
		cmd.execute() ;
		xct.commit();
	}

	void db_set_started_task( std::string encoded_url, std::string user_name )
	{
		sqlite3pp::transaction xct(*db);
		sqlite3pp::command cmd(*db, command_start_task.c_str());
		cmd.bind(":encoded_url", encoded_url) ;
		cmd.bind(":status", "started") ;
		cmd.bind(":user_name", user_name) ;
		cmd.execute() ;
		xct.commit();
	}

	void db_set_canceled_task( std::string encoded_url, std::string user_name )
	{
		sqlite3pp::transaction xct(*db);
		sqlite3pp::command cmd(*db, command_cancel_task.c_str());
		cmd.bind(":encoded_url", encoded_url) ;
		cmd.bind(":user_name", user_name) ;
		cmd.execute() ;
		xct.commit();
	}

	void db_create_task_table_entry( std::string encoded_url, std::string user_name, std::string task_string, std::string pid )
	{
		sqlite3pp::transaction xct(*db);
		sqlite3pp::command cmd(*db, command_post_task.c_str());
		cmd.bind(":encoded_url", encoded_url) ;
		cmd.bind(":status", "waiting") ;
		cmd.bind(":user_name", user_name) ;
		cmd.bind(":pid", pid);
		cmd.bind(":task", task_string);
		cmd.execute() ;
		xct.commit();
	}

	bool db_get_if_is_canceled( std::string user_name, std::string encoded_url)
	{
		bool response = false;
		sqlite3pp::transaction xct(*db, true);
		{
			sqlite3pp::query qry(*db, this->command_is_canceled.c_str());
			qry.bind(":user_name", user_name);
			qry.bind(":encoded_url", encoded_url);

			for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
				int canceled;
				(*i).getter() >> canceled;
				if(canceled == 1)
					response = true;
			}
		}
		return response;
	}

	bool db_delete_task( std::string encoded_url, std::string user_name)
	{
		sqlite3pp::transaction xct(*db, true);
		{
			sqlite3pp::query qry(*db, this->command_find_task.c_str());
			qry.bind(":encoded_url", encoded_url);
			//file_name, user_name, is_public, modifie
			for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
				int canceled;
				std::string  t_user_name, pid, modified;
				(*i).getter() >> t_user_name >> pid >>  modified >> canceled;

				if((t_user_name == user_name) && (canceled == 1))
				{
					sqlite3pp::command cmd(*db, this->command_delete_task.c_str());
					cmd.bind(":encoded_url", encoded_url);
					if(cmd.execute() == 0)
					{
						boost::filesystem::remove_all(boost::filesystem::path(this->root_path / encoded_url));
						return true;
					}
				}
			}
		}
		return false;
	}

	std::string db_get_task_output( std::string user_name,  std::string encoded_url)
	{
		std::string result = "";
		sqlite3pp::transaction xct(*db, true);
		{
			sqlite3pp::query qry(*db, this->command_get_output.c_str());
			qry.bind(":user_name", user_name);
			qry.bind(":encoded_url", encoded_url);
			for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
				(*i).getter() >>  result;
			}
		}
		return result;
	}

	void list_task_output( std::string user_name,  std::string encoded_url, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request )
	{
		std::ostringstream user_tasks_stream;
		user_tasks_stream << "[";
		user_tasks_stream << "\n\t{\n\t\t\"href\": \""
			<< encoded_url << "\",\n\t\t\"output\": \""
			<< http_utils::escape(db_get_task_output(user_name, encoded_url))  << "\"\n\t}";

		std::string files_ = user_tasks_stream.str();

		http_utils::set_json_content_type(response);
		http_utils::send(files_.append("\n]"), socket, response, request);
		return;
	}

	void list_user_tasks( std::string user_name, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request )
	{
		std::ostringstream user_tasks_stream;
		user_tasks_stream << "[";

		sqlite3pp::transaction xct(*db, true);
		{
			sqlite3pp::query qry(*db, this->command_find_all_user_tasks.c_str());
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

		}
		std::string files_ = user_tasks_stream.str();
		if (files_.length() > 5)
			files_ = files_.substr(0, files_.length() - 1);
		http_utils::set_json_content_type(response);
		http_utils::send(files_.append("\n]"), socket, response, request);
		return;
	}

	void ThreadFunction(std::string tid, std::string user_name,std::string pid, utils::task t)
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

			if(db_get_if_is_canceled(user_name, tid))
				db_delete_task(tid, user_name);

			db_set_started_task(tid, user_name);
			general_utils::create_directory(root_path / tid);
			boost::process::child c = this->start_child(tid, pid, args, a->use_shell); 

			boost::process::pistream &os = c.get_stdout();

			std::string line; 
			*lu << "out stream:" << log_util::endl; 
			while (std::getline(os, line)) {

				*lu << line << log_util::endl; 
				line = db_get_task_output(user_name, tid) + line; 
				db_set_task_output(tid, user_name, line );
			}

			c.wait();

			db_set_finish_task(tid, user_name);

		}catch(std::exception &e)
		{
			*lu << "error!" << log_util::endl; 
			*lu << e.what() << log_util::endl; 

			std::string output_line = db_get_task_output(user_name, tid) + e.what(); 
			db_set_task_output(tid, user_name, output_line );

			db_set_status_on_task(tid, user_name, "error");
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
						t.string_args[v.first]=	request->arguments[v.first];
				}
			}
			std::string tid = user_name + t.serialize_base() + general_utils::get_utc_now_time();
			tid = general_utils::get_sha256(tid);

			db_create_task_table_entry(tid, user_name, t.serialize_base(), pid);

			boost::shared_ptr< boost::packaged_task<void> > pt(new boost::packaged_task<void>(boost::bind(&run_service::ThreadFunction, this, tid, user_name,pid, t)));
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