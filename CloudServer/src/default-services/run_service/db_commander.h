#ifndef DB_COMMANDER
#define DB_COMMANDER
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

class db_commander
{
private:
	friend class run_service;
	friend class user_task_pool;

	boost::shared_ptr<log_util> lu;
	boost::shared_ptr<sqlite3pp::database> db;

	std::string command_create_tasks_table;
	std::string command_post_task;
	std::string command_cancel_task;
	std::string command_start_task;
	std::string command_finish_task;
	std::string command_set_task_output;
	std::string command_find_all_user_tasks;
	std::string command_is_canceled;
	std::string command_get_output;
	std::string command_delete_task;
	std::string command_find_task;
	std::string command_status_task;

	db_commander(const std::string& db_name, boost::shared_ptr<log_util> lu)
	{
		this->lu = lu;

		this->command_create_tasks_table = "CREATE TABLE IF NOT EXISTS tasks (encoded_url varchar(300) UNIQUE NOT NULL primary key, output BLOB default \"starting:\n\", task TEXT NOT NULL, status varchar(65) default \"not ready\", pid varchar(100) NOT NULL, user_name varchar(65) NOT NULL, started DATETIME, finished DATETIME, modified DATETIME NOT NULL default CURRENT_TIMESTAMP, canceled BOOLEAN  NOT NULL default 0)";
		this->command_post_task =  "INSERT INTO tasks (user_name, encoded_url, task, status, pid ) VALUES (:user_name, :encoded_url, :task, :status, :pid)";
		this->command_cancel_task = "UPDATE tasks SET canceled=1, modified=CURRENT_TIMESTAMP WHERE ( user_name=:user_name and encoded_url=:encoded_url )";
		this->command_start_task = "UPDATE tasks SET status=:status, modified=CURRENT_TIMESTAMP, started=CURRENT_TIMESTAMP  WHERE ( user_name=:user_name and encoded_url=:encoded_url )";
		this->command_finish_task = "UPDATE tasks SET status=:status, finished=CURRENT_TIMESTAMP, modified=CURRENT_TIMESTAMP  WHERE ( user_name=:user_name and encoded_url=:encoded_url )";
		this->command_status_task = "UPDATE tasks SET status=:status, modified=CURRENT_TIMESTAMP WHERE ( user_name=:user_name and encoded_url=:encoded_url )";
		this->command_set_task_output = "UPDATE tasks SET output=:output, modified=CURRENT_TIMESTAMP WHERE ( user_name=:user_name and encoded_url=:encoded_url )";
		this->command_find_all_user_tasks = "SELECT encoded_url, status, pid, modified FROM tasks WHERE user_name=:user_name AND canceled=0 ";
		this->command_is_canceled = "SELECT canceled FROM tasks WHERE user_name=:user_name AND encoded_url=:encoded_url ";
		this->command_get_output = "SELECT output FROM tasks WHERE user_name=:user_name AND encoded_url=:encoded_url ";
		this->command_delete_task = "DELETE FROM tasks WHERE encoded_url=:encoded_url";
		this->command_find_task = "SELECT user_name, pid, modified, status, canceled FROM tasks WHERE encoded_url=:encoded_url";

		boost::shared_ptr<sqlite3pp::database> db_( new sqlite3pp::database(db_name.c_str()));
		this->db = db_;
		db->execute(command_create_tasks_table.c_str());

	}

	boost::shared_ptr<sqlite3pp::database> get_db()
	{
		return db;
	}
	void set_task_output( const std::string & encoded_url, const std::string & user_name, const std::string & output )
	{
		sqlite3pp::transaction xct(*db);
		{
			sqlite3pp::command cmd(*db, command_set_task_output.c_str());
			cmd.bind(":encoded_url", encoded_url);
			cmd.bind(":output", output);
			cmd.bind(":user_name", user_name);
			cmd.execute();
		}
		xct.commit();
	}

	void set_finish_task( const std::string & encoded_url, const std::string & user_name )
	{
		sqlite3pp::transaction xct(*db);
		{
			sqlite3pp::command cmd(*db, command_finish_task.c_str());
			cmd.bind(":encoded_url", encoded_url) ;
			cmd.bind(":status", "finished") ;
			cmd.bind(":user_name", user_name) ;
			cmd.execute() ;
		}
		xct.commit();
	}

	void set_status_on_task( const std::string & encoded_url, const std::string & user_name, const std::string & status )
	{
		sqlite3pp::transaction xct(*db);
		{
			sqlite3pp::command cmd(*db, command_status_task.c_str());
			cmd.bind(":encoded_url", encoded_url) ;
			cmd.bind(":status", status) ;
			cmd.bind(":user_name", user_name) ;
			cmd.execute() ;
		}
		xct.commit();
	}

	void set_started_task( const std::string & encoded_url, const std::string & user_name )
	{
		sqlite3pp::transaction xct(*db);
		{
			sqlite3pp::command cmd(*db, command_start_task.c_str());
			cmd.bind(":encoded_url", encoded_url) ;
			cmd.bind(":status", "started") ;
			cmd.bind(":user_name", user_name) ;
			cmd.execute() ;
		}
		xct.commit();
	}

	void set_canceled_task( const std::string & encoded_url, const std::string & user_name )
	{
		sqlite3pp::transaction xct(*db);
		{
			sqlite3pp::command cmd(*db, command_cancel_task.c_str());
			cmd.bind(":encoded_url", encoded_url) ;
			cmd.bind(":user_name", user_name) ;
			cmd.execute() ;
		}
		xct.commit();
	}

	void create_task_table_entry( const std::string & encoded_url, const std::string & user_name, const std::string & task_string, const std::string & pid )
	{
		sqlite3pp::transaction xct(*db);
		{
			sqlite3pp::command cmd(*db, command_post_task.c_str());
			cmd.bind(":encoded_url", encoded_url) ;
			cmd.bind(":status", "waiting") ;
			cmd.bind(":user_name", user_name) ;
			cmd.bind(":pid", pid);
			cmd.bind(":task", task_string);
			cmd.execute() ;
		}
		xct.commit();
	}

	bool get_if_is_canceled(const std::string & user_name, const std::string & encoded_url)
	{
		bool response = false;

		sqlite3pp::query qry(*db, this->command_is_canceled.c_str());
		qry.bind(":user_name", user_name);
		qry.bind(":encoded_url", encoded_url);

		for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
			int canceled;
			(*i).getter() >> canceled;
			if(canceled == 1)
				response = true;
		}

		return response;
	}

	bool get_if_users_task( const std::string & encoded_url, const std::string & user_name, std::string & status, int & canceled)
	{
		sqlite3pp::query qry(*db, this->command_find_task.c_str());
		qry.bind(":encoded_url", encoded_url);
		for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
			std::string  t_user_name, pid, modified;
			(*i).getter() >> t_user_name >> pid >>  modified >> status >>  canceled;

			if(t_user_name == user_name)
			{
				return true;
			}
		}

		return false;
	}

	bool get_if_users_task(const std::string & encoded_url,const std::string & user_name)
	{
		int canceled = 0;
		std::string status = "";
		return this->get_if_users_task(encoded_url, user_name, status, canceled);
	}
	std::string get_task_output(const std::string & user_name, const std::string & encoded_url)
	{
		std::string result = "";
		sqlite3pp::query qry(*db, this->command_get_output.c_str());
		qry.bind(":user_name", user_name);
		qry.bind(":encoded_url", encoded_url);
		for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
			(*i).getter() >>  result;
		}
		return result;
	}
};



#endif //DB_COMMANDER
