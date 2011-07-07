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

	std::vector<std::string> options;
	while (*devices)
	{
		options.push_back(std::string(devices));
		devices += strlen(devices) + 1;
	}

	int selected_index = selector::simple_select(options, "Please, select the audio capture device:");
	this->audio_capturer_block->start((ALCchar*)options[selected_index - 1].c_str());
}
