#ifndef FLV_TAG_H
#define FLV_TAG_H

#include <boost/shared_array.hpp>

class flv_tag
{
public:
	boost::shared_array<unsigned char> header;
	boost::shared_array<unsigned char> data;
	unsigned int data_size;
	unsigned int timestamp;
};

#endif // FLV_TAG_H
