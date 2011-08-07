#include "http_utils.h"

template<typename _OutputIterator>
void http_utils::split(std::string str, std::string delim, _OutputIterator result) {
	typedef boost::algorithm::split_iterator<std::string::iterator> string_split_iterator;
	for(string_split_iterator iter=boost::algorithm::make_split_iterator(str,
		boost::algorithm::first_finder(delim, boost::algorithm::is_equal()));
		iter!=string_split_iterator();
	++iter) {

		std::string component = boost::copy_range<std::string>(*iter);
		*result = component;
		++result;
	}
}