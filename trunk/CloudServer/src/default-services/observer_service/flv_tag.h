#ifndef FLV_TAG_H
#define FLV_TAG_H

class flv_tag
{
public:
	unsigned char *header;
	unsigned char *data;
	unsigned int data_size;
	unsigned int timestamp;
};

#endif // FLV_TAG_H
