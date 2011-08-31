// Boost
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>

#include "filters/audio_capturer/audio_capturer.h"
#include "filters/audio_encoder/audio_encoder.h"
#include "filters/audio_generator/audio_generator.h"
#include "filters/audio_player/audio_player.h"
#include "filters/line_segment_detector/line_segment_detector.h"
#include "filters/multiplexer/multiplexer.h"
#include "filters/simple_synchronizer/simple_synchronizer.h"
#include "filters/transmitter/transmitter.h"
#include "filters/video_capturer/video_capturer.h"
#include "filters/video_encoder/video_encoder.h"
#include "filters/video_generator/video_generator.h"
#include "filters/video_generator_rainbow/video_generator_rainbow.h"

#include "utils/graph_runner/graph_runner.h"
#include "utils/selector/selector.h"

// Application entry point.
int main(int argc, char* argv[])
{
	// Initialize default settings.
	int audio_capture_device = -1;
	int audio_sample_rate = 44100;
	std::string container = "flv";
	bool flag_disable_audio = false;
	bool flag_disable_video = false;
	bool flag_echo = false;
	bool flag_generate_audio = false;
	bool flag_generate_video = false;
	bool flag_rainbow = false;
	bool flag_lsd = false;
	std::string server = "";
	int stream_bitrate = 1048576;
	std::string username = "";
	int video_capture_device = -1;
	int video_frame_rate = 15;
	int video_height = 720;
	int video_width = 1280;

	// Parse command line arguments.
	for (int i = 1; i < argc; i++)
	{
		std::string arg(argv[i]);
		int pos = arg.find("=");
		if (std::string::npos != pos)
		{
			std::string key = arg.substr(0, pos);
			std::string value = arg.substr(pos + 1, arg.length() - pos - 1);

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
			if (arg == "--rainbow")
				flag_rainbow = true;
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

	// Ask for the video capture device if it is needed and wasn't read from the command line arguments.
	if (!flag_disable_video && !flag_generate_video && (video_capture_device == -1))
		video_capture_device = selector::simple_select(video_capturer::get_capture_devices(), "Please, select the video capture device:");

	synchronizer* synchronizer_block = NULL;

	audio_capturer* audio_capturer_block = NULL;
	audio_encoder* audio_encoder_block = NULL;
	audio_generator* audio_generator_block = NULL;
	audio_player* audio_player_block = NULL;
	line_segment_detector* line_segment_detector_block = NULL;
	multiplexer* multiplexer_block = NULL;
	simple_synchronizer* simple_synchronizer_block = NULL;
	transmitter* transmitter_block = NULL;
	video_capturer* video_capturer_block = NULL;
	video_encoder* video_encoder_block = NULL;
	video_generator* video_generator_block = NULL;
	video_generator_rainbow* video_generator_rainbow_block = NULL;

	// Use the 'simple_synchronizer' by default.
	simple_synchronizer_block = new simple_synchronizer();
	synchronizer_block = simple_synchronizer_block;

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
			if (flag_rainbow)
			{
				video_generator_rainbow_block = new video_generator_rainbow(video_width, video_height, video_frame_rate);
				video_generator_rainbow_block->connect(video_encoder_block);
			}
			else
			{
				video_generator_block = new video_generator(video_width, video_height, video_frame_rate, username);
				video_generator_block->connect(video_encoder_block);
			}
		}
		else
		{
			video_capturer_block = new video_capturer(video_width, video_height, video_frame_rate);
			video_capturer_block->set_capture_device(video_capture_device);
			if (flag_lsd)
			{
				line_segment_detector_block = new line_segment_detector(video_width, video_height);
				line_segment_detector_block->connect(video_encoder_block);

				video_capturer_block->connect(line_segment_detector_block);
			}
			else
				video_capturer_block->connect(video_encoder_block);
		}
	}

	multiplexer_block->connect(transmitter_block);

	synchronizer_block->set_synchronization_period(1000 / video_frame_rate);
	graph_runner* graph_runner_block = new graph_runner(synchronizer_block);

	if (!flag_disable_audio)
	{
		if (flag_generate_audio)
			graph_runner_block->connect(audio_generator_block);
		else
			graph_runner_block->connect(audio_capturer_block);
	}

	if (!flag_disable_video)
	{
		if (flag_generate_video)
		{
			if (flag_rainbow)
				graph_runner_block->connect(video_generator_rainbow_block);
			else
				graph_runner_block->connect(video_generator_block);
		}
		else
			graph_runner_block->connect(video_capturer_block);
	}

	graph_runner_block->start();

	std::cout << "Type 'exit' and hit enter to stop broadcasting and close the application..." << std::endl;
	std::string exit;
	do
	{
		std::cin >> exit;
		boost::this_thread::sleep(boost::posix_time::milliseconds(250));
	} while (exit != "exit");

	graph_runner_block->stop();
	graph_runner_block->disconnect();
	delete graph_runner_block;

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

		if (flag_lsd)
		{
			line_segment_detector_block->disconnect();
			delete line_segment_detector_block;
		}

		if (flag_generate_video)
		{
			if (flag_rainbow)
			{
				video_generator_rainbow_block->disconnect();
				delete video_generator_rainbow_block;
			}
			else
			{
				video_generator_block->disconnect();
				delete video_generator_block;
			}
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
