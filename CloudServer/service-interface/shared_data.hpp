#ifndef SHARED_DATA_HPP
#define SHARED_DATA_HPP

#include <string>
// Boost
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/bind.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/map.hpp> 
#include <boost/serialization/string.hpp>

#include <base_service_utils.hpp>

class shared
{
public:
	// you can values post only once
	bool post(const std::string & key, const std::string & val)
	{
		return post(key, val, false);
	}

	// you can values post only once
	bool post(const std::string & key, const std::string & val, bool editable)
	{
		std::map<std::string, item>::iterator it;
		boost::mutex::scoped_lock lock(mut_);
		it = data.find(key);
		if (it != data.end())
		{
			return false;
		} 
		item post_data;
		post_data.editable = editable;
		post_data.data = val;
		data[key] = post_data;
		return true;
	}

	// you can update values only if you posted them as editable, note that other services can also edit such data
	bool update(const std::string & key, const std::string & val)
	{
		std::map<std::string, item>::iterator it;
		boost::mutex::scoped_lock lock(mut_);
		it = data.find(key);
		if (it != data.end())
		{
			if(it->second.editable)
			{
				it->second.data = val;
				return true;
			}
		} 
	return false;
		
	}

	// get safely any time
	std::string get(const std::string & key)
	{
		std::map<std::string, item>::iterator it;
		boost::mutex::scoped_lock lock(mut_);
		it = data.find(key);
		if (it != data.end())
		{
			return it->second.data;
		}
		return "";
	}

	boost::shared_ptr<std::string> serialize()
	{
		std::stringstream oa_ss_data;
		boost::archive::text_oarchive  oa_data(oa_ss_data);
		oa_data << *this;
		return boost::shared_ptr<std::string>(new std::string(oa_ss_data.str()),boost::bind(&base_service_utils::delete_ptr<std::string>, _1) );
	}

	void deserialize( boost::shared_ptr<std::string> request_string)
	{
		std::stringstream ia_ss_data;
		ia_ss_data << *request_string;
		boost::archive::text_iarchive ia_data(ia_ss_data);
		ia_data >> *this;	 
	}

private:
	class item  
	{
		public:
			std::string data;
			bool editable;

		private:
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive & ar, const unsigned int version)
			{
				ar & data;
				ar & editable;
			}
	};

	std::map<std::string, item> data;
	mutable boost::mutex mut_;

	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & data;
	}
};
#endif // SHARED_DATA_HPP