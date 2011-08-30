#include "graph_runner.h"

graph_runner::graph_runner(int invocation_period)
{
	this->invocation_period = boost::posix_time::milliseconds(invocation_period);

	this->audio_capturer_block = NULL;
	this->audio_generator_block = NULL;
	this->video_capturer_block = NULL;
	this->video_generator_block = NULL;
	this->video_generator_rainbow_block = NULL;
}

graph_runner::~graph_runner()
{
	this->disconnect();
}

void graph_runner::connect(audio_capturer* audio_capturer_block)
{
	this->audio_capturer_block = audio_capturer_block;
}

void graph_runner::connect(audio_generator* audio_generator_block)
{
	this->audio_generator_block = audio_generator_block;
}

void graph_runner::connect(video_capturer* video_capturer_block)
{
	this->video_capturer_block = video_capturer_block;
}

void graph_runner::connect(video_generator* video_generator_block)
{
	this->video_generator_block = video_generator_block;
}

void graph_runner::connect(video_generator_rainbow* video_generator_rainbow_block)
{
	this->video_generator_rainbow_block = video_generator_rainbow_block;
}

void graph_runner::disconnect()
{
	this->audio_capturer_block = NULL;
	this->audio_generator_block = NULL;
	this->video_capturer_block = NULL;
	this->video_generator_block = NULL;
	this->video_generator_rainbow_block = NULL;
}

void graph_runner::start()
{
	this->runner_thread = boost::shared_ptr<boost::thread>(new boost::thread(&graph_runner::runner_loop, this));
}

void graph_runner::stop()
{
	this->runner_thread->interrupt();
}

void graph_runner::runner_loop()
{
	timer time;
	while (true)
	{
		time.restart();
		if (this->audio_capturer_block != NULL)
			this->audio_capturer_block->send();

		if (this->audio_generator_block != NULL)
			this->audio_generator_block->send();

		if (this->video_capturer_block != NULL)
			this->video_capturer_block->send();

		if (this->video_generator_block != NULL)
			this->video_generator_block->send();

		if (this->video_generator_rainbow_block != NULL)
			this->video_generator_rainbow_block->send();

		boost::this_thread::sleep(this->invocation_period - time.elapsed());
	}
}
