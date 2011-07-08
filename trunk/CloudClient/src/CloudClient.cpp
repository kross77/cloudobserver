// Boost
#include <boost/asio.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random.hpp>
#include <boost/thread.hpp>
#include <boost/timer.hpp>

// OpenCV
#include <opencv2/opencv.hpp>

#include "filters/audio_capturer/audio_capturer.h"
#include "filters/audio_generator/audio_generator.h"
#include "filters/audio_player/audio_player.h"
#include "filters/audio_encoder/audio_encoder.h"
#include "filters/video_capturer/video_capturer.h"
#include "filters/video_generator/video_generator.h"
#include "filters/video_encoder/video_encoder.h"
#include "filters/multiplexer/multiplexer.h"
#include "filters/transmitter/transmitter.h"

#include "utils/selector/selector.h"

#include "list.h"
#include "3rdparty/LSD/LSD.h"

using namespace std;
using boost::asio::ip::tcp;
using namespace boost::posix_time;
using boost::posix_time::ptime;
using boost::posix_time::time_duration;

int audio_capture_device;
int audio_sample_rate;
std::string container;
bool flag_disable_audio;
bool flag_disable_video;
bool flag_echo;
bool flag_generate_audio;
bool flag_generate_video;
bool flag_lsd;
std::string server;
int stream_bitrate;
std::string username;
int video_capture_device;
int video_width;
int video_height;
int video_frame_rate;

audio_capturer* audio_capturer_block;
audio_generator* audio_generator_block;
audio_player* audio_player_block;
audio_encoder* audio_encoder_block;
video_capturer* video_capturer_block;
video_generator* video_generator_block;
video_encoder* video_encoder_block;
multiplexer* multiplexer_block;
transmitter* transmitter_block;

// Boost
boost::mt19937 rng;
boost::uniform_int<> six(-128, 127);
boost::variate_generator<boost::mt19937&, boost::uniform_int<> >die(rng, six);

//void capture_frame(int w, int h, char* buffer, int bytespan)
//{
//	if (flag_generate_video)
//	{
//		cvResize(CVframe, CVframeWithText);
//		ptime now = second_clock::local_time();
//		cvPutText(CVframeWithText, to_simple_string(now.time_of_day()).c_str(), cvPoint(0, (h / 2 + 10)), &font, CV_RGB(1, 1, 1));
//		for (int i = 0; i < w * 4 * h; i = i + 4)
//		{
//			buffer[0] = CVframeWithText->imageData[i];
//			buffer[1] = CVframeWithText->imageData[i + 1];
//			buffer[2] = CVframeWithText->imageData[i + 2];
//			buffer += 3;
//		}
//		//if (rainbow)
//		//{
//		//	int wxh = w * h;
//		//	static float seed = 1.0;
//		//	for (int i = 0; i < h; i++)
//		//	{
//		//		char* line = buffer + i * bytespan;
//		//		for (int j = 0; j < w; j ++)
//		//		{
//		//			// RGB
//		//			line[0] = 255 * sin(((float)i / wxh * seed) * 3.14);
//		//			line[1] = 255 * cos(((float)j / wxh * seed) * 3.14);
//		//			line[2] = 255 * sin(((float)(i + j) / wxh * seed) * 3.14);
//		//			line += 3;
//		//		}
//		//	}
//		//	seed = seed + 2.2;
//		//}
//	}
//	else
//	{
//		CVframe = cvQueryFrame(capture);
//		if (!CVframe)
//		{
//			printf("No CV frame captured!\n");
//			cin.get();
//		}
//
//		cvResize(CVframe, destination);
//		if (flag_lsd)
//		{
//			IplImage *destinationForLSD = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
//			cvCvtColor(destination, destinationForLSD, CV_RGB2GRAY);
//
//			image_double lsdImage;
//			ntuple_list lsdOut;
//			lsdImage = new_image_double(w, h);
//
//			for (int x = 0; x < w; x++)
//				for (int y = 0; y < h; y++)
//					lsdImage->data[x + y * lsdImage->xsize] = cvGetReal2D(destinationForLSD, y, x);
//
//			// call LSD
//			lsdOut = lsd(lsdImage);
//
//			for (unsigned int i = 0; i < lsdOut->size; i++)
//			{
//				CvPoint pt1 = { (int)lsdOut->values[i * lsdOut->dim + 0], (int)lsdOut->values[i * lsdOut->dim + 1] };
//				CvPoint pt2 = { (int)lsdOut->values[i * lsdOut->dim + 2], (int)lsdOut->values[i * lsdOut->dim + 3] };
//				cvLine(destination, pt1, pt2, CV_RGB(240, 255, 255), 1, CV_AA, 0);
//			}
//			cvReleaseImage(&destinationForLSD);
//			free_image_double(lsdImage);
//			free_ntuple_list(lsdOut);
//		}
//
//		for (int i = 0; i < destination->imageSize; i = i + 3)
//		{
//			buffer[2] = destination->imageData[i];
//			buffer[1] = destination->imageData[i + 1];
//			buffer[0] = destination->imageData[i + 2];
//			buffer += 3;
//		}
//
//		//cvSplit(destination, bluechannel, greenchannel, redchannel, NULL);
//		//for(int y = 0; y < destination->height; y++)
//		//{
//		//	char* line = buffer + y * bytespan;
//		//	for(int x = 0; x < destination->width; x++)
//		//	{
//		// 		line[0] = cvGetReal2D(redchannel, y, x);
//		// 		line[1] = cvGetReal2D(greenchannel, y, x);
//		// 		line[2] = cvGetReal2D(bluechannel, y, x);
//		// 		line += 3;
//		//	}
//		//}
//
//		//for (int i = 0; i < w * h * 3; ++i) {
//		// 		buffer[i] = destination->imageData;
//		//}
//	}
//}

// Application entry point.
int main(int argc, char* argv[])
{
	// Initialize default settings.
	audio_capture_device = -1;
	audio_sample_rate = 44100;
	container = "flv";
	flag_disable_audio = false;
	flag_disable_video = false;
	flag_echo = false;
	flag_generate_audio = false;
	flag_generate_video = false;
	flag_lsd = false;
	server = "";
	stream_bitrate = 1048576;
	username = "";
	video_capture_device = -1;
	video_frame_rate = 15;
	video_height = 720;
	video_width = 1280;

	// Parse command line arguments.
	for (int i = 1; i < argc; i++)
	{
		std::string arg = string(argv[i]);
		int pos = arg.find("=");
		if (std::string::npos != pos)
		{
			string key = arg.substr(0, pos);
			string value = arg.substr(pos + 1, arg.length() - pos - 1);

			try
			{
				if (key == "--audio-capture-device")
					audio_capture_device = boost::lexical_cast<int>(value);
				if (key == "--audio-sample-rate")
					audio_sample_rate = boost::lexical_cast<int>(value);
				if (key == "--container")
					container = value;
				if (key == "--server")
					server = value;
				if (key == "--stream-bitrate")
					stream_bitrate = boost::lexical_cast<int>(value);
				if (key == "--username")
					username = value;
				if (key == "--video-capture-device")
					video_capture_device = boost::lexical_cast<int>(value);
				if (key == "--video-frame-rate")
					video_frame_rate = boost::lexical_cast<int>(value);
				if (key == "--video-height")
					video_height = boost::lexical_cast<int>(value);
				if (key == "--video-width")
					video_width = boost::lexical_cast<int>(value);
			}
			catch (boost::bad_lexical_cast const&)
			{
				std::cout << "Error while parsing argument '" << arg << "': value is not valid. Argument skipped." << std::endl;
			}
		}
		else
		{
			if (arg == "--disable-audio")
				flag_disable_audio = true;
			if (arg == "--disable-video")
				flag_disable_video = true;
			if (arg == "--echo")
				flag_echo = true;
			if (arg == "--generate-audio")
				flag_generate_audio = true;
			if (arg == "--generate-video")
				flag_generate_video = true;
			if (arg == "--lsd")
				flag_lsd = true;
			if (arg == "--robot")
			{
				flag_generate_audio = true;
				flag_generate_video = true;
			}
		}
	}

	// Align video width and height so that each dimension divides by 4.
	video_width -= video_width % 4;
	video_height -= video_height % 4;

	// Ask for the username if one wasn't read from command line arguments.
	if (username.empty())
	{
		std::cout << "Please, select a username: ";
		std::cin >> username;
	}

	// Ask for the server URL if one wasn't read from command line arguments.
	if (server.empty())
	{
		std::cout << "Please, specify the server URL: ";
		std::cin >> server;
	}

	// Ask for the audio capture device if it is needed and wasn't read from the command line arguments.
	if (!flag_disable_audio && !flag_generate_audio && (audio_capture_device == -1))
		audio_capture_device = selector::simple_select(audio_capturer::get_capture_devices(), "Please, select the audio capture device:");

	// Initialize the transmitter block.
	transmitter_block = new transmitter();

	// Repeat asking for the username and the server URL until connection is successfully established.
	bool succeed = false;
	while (!succeed)
	{
		try
		{
			// Try to connect to the server.
			transmitter_block->connect(username, server);
			// Connection succeeded.
			succeed = true;
		}
		catch (transmitter::invalid_username_exception&)
		{
			// Server rejected the username. Ask for another username.
			std::cout << "Please, select another username: ";
			std::cin >> username;
		}
		catch (transmitter::server_connection_exception&)
		{
			// Failed to connect to the server. Ask for another server URL.
			std::cout << "Please, specify another server URL: ";
			std::cin >> server;
		}
	}

	multiplexer_block = new multiplexer(container);
	AVFormatContext* format_context = multiplexer_block->get_format_context();

	if (!flag_disable_audio)
	{
		audio_encoder_block = new audio_encoder(audio_sample_rate);
		audio_encoder_block->connect(multiplexer_block);

		if (flag_generate_audio)
		{
			audio_generator_block = new audio_generator(audio_sample_rate, AL_FORMAT_MONO16, audio_sample_rate / video_frame_rate);
			audio_generator_block->connect(audio_encoder_block);
		}
		else
		{
			audio_capturer_block = new audio_capturer(audio_sample_rate, AL_FORMAT_MONO16, audio_sample_rate / video_frame_rate);
			audio_capturer_block->set_capture_device(audio_capture_device);
			audio_capturer_block->connect(audio_encoder_block);
		}

		if (flag_echo)
		{
			audio_player_block = new audio_player(audio_sample_rate, AL_FORMAT_MONO16);
			if (flag_generate_audio)
				audio_generator_block->connect(audio_player_block);
			else
				audio_capturer_block->connect(audio_player_block);
		}
	}
	
	if (!flag_disable_video)
	{
		video_encoder_block = new video_encoder(stream_bitrate, video_frame_rate, video_width, video_height);
		video_encoder_block->connect(multiplexer_block);

		if (flag_generate_video)
		{
			video_generator_block = new video_generator(video_width, video_height, video_frame_rate, username);
			video_generator_block->connect(video_encoder_block);
		}
		else
		{
			video_capturer_block = new video_capturer(video_width, video_height, video_frame_rate);
			video_capturer_block->connect(video_encoder_block);
		}
	}
	
	if (av_set_parameters(format_context, NULL) < 0)
		throw std::runtime_error("av_set_parameters failed.");

	multiplexer_block->connect(transmitter_block);

	if (!flag_disable_audio)
	{
		if (flag_generate_audio)
			audio_generator_block->start();
		else
			audio_capturer_block->start();
	}

	if (!flag_disable_video)
	{
		if (flag_generate_video)
			video_generator_block->start();
		else
			video_capturer_block->start();
	}

	std::cout << "Type 'exit' and hit enter to stop broadcasting and close the application..." << std::endl;
	std::string exit;
	do
	{
		cin >> exit;
		boost::this_thread::sleep(boost::posix_time::milliseconds(250));
	} while (exit != "exit");

	if (!flag_disable_audio)
	{
		audio_encoder_block->disconnect();
		delete audio_encoder_block;

		if (flag_generate_audio)
		{
			audio_generator_block->disconnect();
			delete audio_generator_block;
		}
		else
		{
			audio_capturer_block->disconnect();
			delete audio_capturer_block;
		}

		if (flag_echo)
			delete audio_player_block;
	}

	if (!flag_disable_video)
	{
		video_encoder_block->disconnect();
		delete video_encoder_block;

		if (flag_generate_video)
		{
			video_generator_block->disconnect();
			delete video_generator_block;
		}
		else
		{
			video_capturer_block->disconnect();
			delete video_capturer_block;
		}
	}

	multiplexer_block->disconnect();
	delete multiplexer_block;

	transmitter_block->disconnect();
	delete transmitter_block;

	return 0;
}
