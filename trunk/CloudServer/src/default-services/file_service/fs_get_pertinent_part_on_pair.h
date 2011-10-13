#ifndef FS_GET_PERTINENT_PART_ON_PAIR_H
#define FS_GET_PERTINENT_PART_ON_PAIR_H

#include <string>
#include <map>

struct fs_get_pertinent_part_on_pair
{
	const std::string given_string;

	fs_get_pertinent_part_on_pair(std::string s)
		:given_string(s)
	{
	}

	std::string operator()(const std::pair<std::string,  boost::shared_ptr<fs_file> > &s)
	{
		std::string::size_type first = 0;

		if (s.first.find(given_string) == 0)
		{
			first = given_string.length();
		}
		else
		{
			return "";
		}

		std::string::size_type count = std::string::npos;
		std::string::size_type pos = s.first.find_last_of("/");
		if (pos != std::string::npos && pos > first)
		{
			count = pos + 1 - first;
		}

		return s.first.substr(first, count);
	}
};

#endif //FS_GET_PERTINENT_PART_ON_PAIR_H
