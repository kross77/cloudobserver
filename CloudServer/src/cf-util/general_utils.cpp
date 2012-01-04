#include "general_utils.h"

std::string general_utils::get_sha256( std::string value )
{
	char data[65];
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, value.c_str(), value.length());
	SHA256_Final(hash, &sha256);
	int i = 0;
	for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(data + (i * 2), "%02x", hash[i]);
	}
	return std::string(data);
}

std::string general_utils::get_utc_now_time()
{
	return  boost::posix_time::to_iso_extended_string( boost::posix_time::second_clock::universal_time() );
}

void general_utils::create_directory( boost::filesystem::path path )
{
	if (boost::filesystem::exists( path ))
	{
		return;
	}
	else
	{
		boost::system::error_code returnedError;
		boost::filesystem::create_directories( path, returnedError );
		if ( returnedError )
		{
			throw std::runtime_error("problem creating directory");
		}
	}
}

std::wstring general_utils::get_dif_path_wstring( boost::filesystem::path base_path, boost::filesystem::path new_path )
{
	boost::filesystem::path sdiffpath;
	boost::filesystem::path stmppath = new_path;
	while(stmppath != base_path) {
		sdiffpath = boost::filesystem::path(stmppath.stem().string() + stmppath.extension().string())/ sdiffpath;
		stmppath = stmppath.parent_path();
	}
	std::wstring diff_path =sdiffpath.wstring();// boost::lexical_cast<string>(sdiffpath);
	diff_path = diff_path.substr(0, (diff_path.length()));
	std::replace(diff_path.begin(), diff_path.end(), '\\', '/');
	return diff_path;
}

std::string general_utils::get_dif_path( boost::filesystem::path base_path, boost::filesystem::path new_path )
{
	boost::filesystem::path sdiffpath;
	boost::filesystem::path stmppath = new_path;
	while(stmppath != base_path) {
		sdiffpath = boost::filesystem::path(stmppath.stem().string() + stmppath.extension().string())/ sdiffpath;
		stmppath = stmppath.parent_path();
	}
	std::string diff_path =sdiffpath.string();// boost::lexical_cast<string>(sdiffpath);
	diff_path = diff_path.substr(0, (diff_path.length()));
	std::replace(diff_path.begin(), diff_path.end(), '\\', '/');
	return diff_path;
}