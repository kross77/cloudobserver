#ifndef CLOUD_WRITER_H
#define CLOUD_WRITER_H

#include <exception>
#include <fstream>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "cloud_reader.h"

class cloud_writer
{
public:
	cloud_writer(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::ofstream* dump);
	~cloud_writer();
	void connect_reader(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::ofstream* dump);
	void process();
	int get_width() { return this->width; }
	int get_height() { return this->height; }

	class flv_format_violation_exception: public std::exception { };
private:
	double get_double_variable_from_flv_script_tag(char* script_tag_data, int data_size, std::string variable_name);
	unsigned short to_ui16(unsigned char* value, int start_index);
	unsigned int to_ui24(unsigned char* value, int start_index);
	unsigned int to_ui32(unsigned char* value, int start_index);

	boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
	std::ofstream* dump;

	int width;
	int height;

	std::vector<cloud_reader*> readers;
	std::vector<std::vector<cloud_reader*>::iterator> disconnected_readers;

	char* header;
	std::vector<std::pair<char*, int> > script_data, tags_buffer;
	unsigned int buffered_timestamp;
	bool key_frames;

	boost::mutex mutex;

	const int HEADER_LENGTH;
    const char SIGNATURE1;
    const char SIGNATURE2;
    const char SIGNATURE3;
    const char VERSION;
    const int TAG_HEADER_LENGTH;
    const char TAGTYPE_AUDIO;
    const char TAGTYPE_VIDEO;
    const char TAGTYPE_DATA;
};

#endif // CLOUD_WRITER_H
