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
		this-> command_create_users_table = "CREATE TABLE IF NOT EXISTS files (errorcode int(10), output TEXT, task TEXT NOT NULL, status varchar(65) NOT NULL, pid varchar(100) NOT NULL, started DATETIME NOT NULL default CURRENT_TIMESTAMP, finished DATETIME, modified DATETIME NOT NULL default CURRENT_TIMESTAMP )";
		this-> post_task = "CREATE TABLE IF NOT EXISTS files (errorcode int(10), output TEXT, task TEXT NOT NULL, status varchar(65) NOT NULL, pid varchar(100) NOT NULL, started DATETIME NOT NULL default CURRENT_TIMESTAMP, finished DATETIME, modified DATETIME NOT NULL default CURRENT_TIMESTAMP )";

	}

	virtual std::string service_check(boost::shared_ptr<http_request> request, boost::shared_ptr<shared> shared_data){
		std::string url= request->url;
		if ((url == "/run.service") || (url == "/run.json")) 
		{
			return "executor";
		}
		return "not for me";
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
	void ThreadFunction(const std::string & pid, utils::task t)
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

			boost::process::child c = this->start_child(pid, args, a->use_shell); 

			boost::process::pistream &os = c.get_stdout();

			std::string line; 
			*lu << "out stream:" << log_util::endl; 
			while (std::getline(os, line)) 
				*lu << line << log_util::endl; 

			while(!c.wait(1000)){
				try
				{ 
					boost::this_thread::interruption_point();
				}
				catch(const boost::thread_interrupted&)
				{
					break;
				}
			}
		}catch(std::exception &e)
		{
			*lu << "error!" << log_util::endl; 
			*lu << e.what() << log_util::endl; 
		}
	}

	void call_app(const std::string & user_name, const std::string & pid, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_response> response, boost::shared_ptr<http_request> request)
	{
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
		uname_therad[user_name] = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&run_service::ThreadFunction, this, pid, t)));
		
		http_utils::set_json_content_type(response);
		http_utils::send_json(std::make_pair("request", "accepted"), socket, response, request);
		return;
		}catch(...)
		{
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
		std::string db_name = config->get<std::string>("database",  "rs.db");
		std::string log_name = config->get<std::string>("log",  "rs.log");
		int threads_per_user = config->get<int>("threading.<xmlattr>.peruser",  2);
		int threads_totall = config->get<int>("threading.<xmlattr>.total",  10);

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
	}



	virtual void start(){}

	virtual void stop(){}

private:
	std::map<std::string, boost::shared_ptr<boost::thread> > uname_therad;

	std::map<std::string, boost::shared_ptr<utils::app> > apps;
	boost::shared_ptr<log_util> lu;
	boost::shared_ptr<sqlite3pp::database> db;
	std::string command_create_users_table;
	std::string post_task;

	void start_work_with_db(const std::string& db_name)
	{
		static bool is_db_set = false;
		if (!is_db_set)
		{
			boost::shared_ptr<sqlite3pp::database> db_( new sqlite3pp::database(db_name.c_str()));
			this->db = db_;

			*lu << "Connected to "<< db_name << " database and created a table with SQLite return code: " << db->execute(command_create_users_table.c_str()) << log_util::endl;
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

	boost::process::child start_child(std::string pid, std::string arguments, bool use_shall = false) 
	{ 
		boost::filesystem::path path_to_exec (apps[pid]->process_name);
		std::string exec = path_to_exec.string();
		boost::process::context ctx; 
		ctx.environment = boost::process::self::get_environment();
		//	ctx.work_directory = app_wd;
		ctx.stdout_behavior =  boost::process::capture_stream(); 

		if(use_shall) 
			return  boost::process::launch_shell(exec + " " + filter_args(arguments), ctx); 

		return  boost::process::launch(exec, split(std::string(path_to_exec.string() + " " + filter_args(arguments)), " "), ctx); 
	} 


};

#endif // RUN_SERVICE_H