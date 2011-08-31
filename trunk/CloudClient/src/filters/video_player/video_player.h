#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H

// OpenCV
#include <opencv2/opencv.hpp>

#include <exception>
#include <string>

class video_player
{
public:
	video_player(std::string window_name, int width, int height);
	~video_player();

	void send(IplImage* frame);

	class internal_exception: public std::exception { };
private:
	std::string window_name;
	int width;
	int height;

	bool created;
};

#endif // VIDEO_PLAYER_H
