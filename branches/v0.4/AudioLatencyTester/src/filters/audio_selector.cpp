#include "audio_selector.h"

audio_selector::audio_selector()
{
	this->audio_capturer_block = NULL;
}

audio_selector::~audio_selector()
{
	this->disconnect();
}

void audio_selector::connect(audio_capturer* audio_capturer_block)
{
	this->audio_capturer_block = audio_capturer_block;
}

void audio_selector::disconnect()
{
}

void audio_selector::select()
{
	const ALCchar* devices = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
	if (devices == NULL)
	{
		std::cout << "Audio capturer: cannot enumerate audio capture devices." << std::endl;
		throw internal_exception();
	}

	if (*devices == NULL)
	{
		std::cout << "Audio capturer: no audio capture devices found." << std::endl;
		throw internal_exception();
	}

	selector audio_selector("Please, select the audio capture device:");
	while (*devices)
	{
		audio_selector.add_option(std::string(devices), (void*)devices);
		devices += strlen(devices) + 1;
	}
	audio_selector.select();

	this->audio_capturer_block->start((ALCchar*)audio_selector.get_selection());
}
