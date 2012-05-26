#ifndef THREADING_UTILITIES_H
#define THREADING_UTILITIES_H 
//STD
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <boost/thread.hpp>
#include <boost/unordered_map.hpp>

/*!
 *  \addtogroup Utilities
 *  @{
 */

/*!
 * \brief provides data independent, thread safe, search/insert/delete
 *
 * template based class with mutex protected search/insert/delete \n
 * std::map/set tested.
 * 
 * \note threading_utils class requires boost_thread library
 *
 */
class threading_utils
{
public:
	/*!
	 * \brief safe insert, std::set and std::map oriented
	 * 
	 * uses threading_utils class mutex fro thread safety \n
	 * uses group.insert to add variable into group
	 *
	 * \n FullName:  threading_utils<variable_T, group_T>::safe_insert 
	 * \n Access:    public 
	 *
	 * \param variable variable_T - given into<T> this shall be T type object
	 * \param into group_T & group<T> - for example set<std::string> a
	 * \return void
	 *
	 */
	template <class variable_T, class group_T>
	void safe_insert(variable_T variable, group_T &into)
	{
		boost::mutex::scoped_lock lock(mut);
		into.insert(variable);
	}

	/*!
	 * \brief thread safly erases object from a std::set like type
	 *
	 * \n FullName:  threading_utils<variable_T, group_T>::safe_erase
	 * \n Access:    public  
	 *
	 * \param variable variable_T
	 * \param into group_T &
	 * \return void 
	 * \sa  threading_utils<variable_T, group_T>::safe_erase_in_map
	 * \warning use  threading_utils<variable_T, group_T>::safe_erase_in_map for erasing from into std::map
	 *
	 */
	template <class variable_T, class group_T>
	void safe_erase(variable_T variable, group_T &into)
	{
		boost::mutex::scoped_lock lock(mut);
		into.erase(into.find(variable));
	}

	/*!
	 * \brief returns value for given key
	 * strictly std::map and boost::unordered_map  oriented
	 * uses threading_utils class mutex fro thread safety \n
	 * uses [] to return variable
	 *
	 * \n FullName:  threading_utils<first_variable_T, second_variable_T, iterator_T>::safe_search_in_map
	 * \n Access:    public  
	 *
	 * \param variable first_variable_T
	 * \param  into std::map<first_variable_T , second_variable_T> & 
	 * \return second_variable_T 
	 *
	 */
	template <class first_variable_T,class second_variable_T, class iterator_T>
	second_variable_T safe_search_in_map(first_variable_T variable, std::map<first_variable_T, second_variable_T> &into)
	{
		boost::mutex::scoped_lock lock(mut);
		return into[variable];
	}

	/*!
	 * \brief returns value for given key
	 * strictly std::map and boost::unordered_map oriented
	 * uses threading_utils class mutex fro thread safety \n
	 * uses [] to return variable
	 *
	 * \n FullName:  threading_utils<first_variable_T, second_variable_T, iterator_T>::safe_search_in_map
	 * \n Access:    public  
	 *
	 * \param variable first_variable_T
	 * \param  into std::map<first_variable_T , second_variable_T> & 
	 * \return second_variable_T 
	 *
	 */
	template <class first_variable_T,class second_variable_T, class iterator_T>
	second_variable_T safe_search_in_map(first_variable_T variable, boost::unordered_map<first_variable_T, second_variable_T> &into)
	{
		boost::mutex::scoped_lock lock(mut);
		return into[variable];
	}

	/*!
	 * \brief thread safly erases object from a std::map like type
	 *
	 *
	 * \n FullName:  threading_utils<variable_T, group_T>::safe_erase_in_map
	 * \n Access:    public  
	 *
	 * \param variable variable_T
	 * \param into group_T & std::map like type
	 * \return void 
	 * \sa  threading_utils<variable_T, group_T>::safe_erase
	 *
	 */
	template <class variable_T,class group_T>
	void safe_erase_in_map(variable_T variable, group_T &into)
	{
		boost::mutex::scoped_lock lock(mut);
		into[variable];
		into.erase(into.find(variable));
	}

private:
	mutable boost::mutex mut;
};

/*! @} */
#endif //THREADING_UTILITIES_H 
