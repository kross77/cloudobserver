// Boost
#include <boost/lexical_cast.hpp>

#include "filters/audio_selector/audio_selector.h"
#include "filters/audio_capturer/audio_capturer.h"
#include "filters/audio_player/audio_player.h"

#include <iostream>
#include <string>

#define SAMPLE_RATE 44100
#define FORMAT AL_FORMAT_MONO16
#define CAPTURE_SIZE 1470

audio_selector audio_selector_block;
audio_capturer audio_capturer_block(SAMPLE_RATE, FORMAT, CAPTURE_SIZE);
audio_player audio_player_block(SAMPLE_RATE, FORMAT);

int main(int argc, char* argv[])
{
	std::cout << "Audio Latency Tester" << std::endl;
	std::cout << "Copyright (c) 2011 Cloud Forever. All rights reserved." << std::endl;
	std::cout << std::endl;

	audio_selector_block.connect(&audio_capturer_block);
	audio_capturer_block.connect(&audio_player_block);

	audio_selector_block.select();
	std::cout << std::endl;

	std::cout << "Minimum capture size is 1." << std::endl;
	std::cout << "Maximum capture size is " << SAMPLE_RATE << "." << std::endl;
	std::cout << std::endl;

	std::cout << "Default capture size is " << CAPTURE_SIZE << "." << std::endl;
	std::cout << "Expected latency is " << (1000 * CAPTURE_SIZE / SAMPLE_RATE) << " ms." << std::endl;
	std::cout << std::endl;

	std::cout << "Type 'exit' to close the application." << std::endl;
	std::cout << std::endl;

	std::string input;
	do
	{
		std::cout << "Set capture size: ";
		std::cin >> input;
		try
		{
			int capture_size = boost::lexical_cast<int>(input);
			if ((capture_size >= 1) && (capture_size <= SAMPLE_RATE))
			{
				audio_capturer_block.set_capture_size(capture_size);
				std::cout << "Expected latency is " << (1000 * capture_size / SAMPLE_RATE) << " ms." << std::endl;
			}
			else
				std::cout << "Invalid input." << std::endl;
		}
		catch (boost::bad_lexical_cast)
		{
			std::cout << "Invalid input." << std::endl;
		}

	} while (input != "exit");
}
