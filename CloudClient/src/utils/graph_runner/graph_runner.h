#ifndef GRAPH_RUNNER_H
#define GRAPH_RUNNER_H

// Boost
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include "../../filters/audio_capturer/audio_capturer.h"
#include "../../filters/audio_generator/audio_generator.h"
#include "../../filters/video_capturer/video_capturer.h"
#include "../../filters/video_generator/video_generator.h"
#include "../../filters/video_generator_rainbow/video_generator_rainbow.h"

#include "../timer/timer.h"

class graph_runner
{
public:
	graph_runner(int invocation_period);
	~graph_runner();
	void connect(audio_capturer* audio_capturer_block);
	void connect(audio_generator* audio_generator_block);
	void connect(video_capturer* video_capturer_block);
	void connect(video_generator* video_generator_block);
	void connect(video_generator_rainbow* video_generator_rainbow_block);
	void disconnect();
	void start();
	void stop();
private:
	void runner_loop();

	boost::posix_time::time_duration invocation_period;

	boost::shared_ptr<boost::thread> runner_thread;

	audio_capturer* audio_capturer_block;
	audio_generator* audio_generator_block;
	video_capturer* video_capturer_block;
	video_generator* video_generator_block;
	video_generator_rainbow* video_generator_rainbow_block;
};

#endif // GRAPH_RUNNER_H
