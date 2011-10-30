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

// Helper for null-terminated ASCII strings (no end of string iterator).
template<typename InIter, typename OutIter>
OutIter  http_utils::copy_asciiz ( InIter begin, OutIter out )
{
	while ( *begin != '\0' ) {
		*out++ = *begin++;
	}
	return (out);
}

// XML escaping in it's general form.  Note that 'out' is expected
// to an "infinite" sequence.
template<typename InIter, typename OutIter>
OutIter  http_utils::escape ( InIter begin, InIter end, OutIter out )
{
	static const char bad[] = "&<>\"\'";
	static const char* rep[] = {"&amp;", "&lt;", "&gt;", "&quot;", "&apos;"};
	static const std::size_t n = sizeof(bad)/sizeof(bad[0]);

	for ( ; (begin != end); ++begin )
	{
		// Find which replacement to use.
		const std::size_t i =
			std::distance(bad, std::find(bad, bad+n, *begin));

		// No need for escaping.
		if ( i == n ) {
			*out++ = *begin;
		}
		// Escape the character.
		else {
			out = copy_asciiz(rep[i], out);
		}
	}
	return (out);
}