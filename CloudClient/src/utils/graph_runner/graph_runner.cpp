#include "graph_runner.h"

graph_runner::graph_runner(synchronizer* synchronizer_block)
{
	this->synchronizer_block = synchronizer_block;
	this->synchronizer_block->set_synchronization_callback(boost::bind(&graph_runner::run, this));

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
	this->synchronizer_block->start();
}

void graph_runner::stop()
{
	this->synchronizer_block->stop();
}

void graph_runner::run()
{
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
}
