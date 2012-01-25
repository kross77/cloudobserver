//if service needs access to server main database it shall be presented with shared_ptr to User Controll class and service shall call request method to search thru DB.

#ifndef GENERAL_UTILITIES_H
#define GENERAL_UTILITIES_H

//STD
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <functional>
#include <locale>
#include <assert.h>
#include <stdio.h>

//OpenSSL
#include <openssl/sha.h>

//Boost
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


/*!
 *  \addtogroup Utilities
 *  @{
 */

//! contains diferent general utilities. directory, time, checksumm manipulation.
namespace general_utils
{
	/*!
	 * \brief creates a directory if one does not exist
	 *
	 * \n FullName:  general_utils::create_directory
	 * \n Access:    public  
	 *
	 * \param path boost::filesystem::path
	 * \return void 
	 *
	 */
	void create_directory( boost::filesystem::path path);

	/*!
	 * \brief gets path difference (std::string based)
	 *
	 * \n FullName:  general_utils::get_dif_path
	 * \n Access:    public  
	 *
	 * \param base_path boost::filesystem::path
	 * \param new_path boost::filesystem::path
	 * \return std::string 
	 * \sa get_dif_path_wstring
	 *
	 */
	std::string get_dif_path(boost::filesystem::path base_path, boost::filesystem::path new_path);

	/*!
	 * \brief gets path difference (std::wstring based)
	 *
	 * \n FullName:  general_utils::get_dif_path_wstring
	 * \n Access:    public  
	 *
	 * \param base_path boost::filesystem::path
	 * \param new_path boost::filesystem::path
	 * \return std::wstring 
	 * \sa get_dif_path
	 *
	 */
	std::wstring get_dif_path_wstring(boost::filesystem::path base_path, boost::filesystem::path new_path);

	/*!
	 * \brief gets SHA256 from string
	 *
	 * \n FullName:  general_utils::get_sha256
	 * \n Access:    public  
	 *
	 * \param value std::string
	 * \return std::string
	 *
	 */
	std::string get_sha256( std::string value);

	/*!
	 * \brief gets iso extended string from second_clock::universal_time
	 *
	 * \n FullName:  general_utils::get_utc_now_time
	 * \n Access:    public  
	 *
	 * \return std::string 
	 * \sa [see also section]
	 * \note [any note about the function you might have]
	 * \warning [any warning if necessary]
	 *
	 */
	std::string get_utc_now_time();
}
/*! @} */
#endif // GENERAL_UTILITIES_H
