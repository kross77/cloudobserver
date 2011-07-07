#ifndef AUDIO_SELECTOR_H
#define AUDIO_SELECTOR_H

// OpenAL
#include <AL/alc.h>

#include "../audio_capturer/audio_capturer.h"

#include "../../utils/selector/selector.h"

#include <vector>

class audio_selector
{
public:
	audio_selector();
	~audio_selector();
	void connect(audio_capturer* audio_capturer_block);
	void disconnect();
	void select();

	class internal_exception: public std::exception { };
private:
	audio_capturer* audio_capturer_block;
};

#endif // AUDIO_SELECTOR_H
