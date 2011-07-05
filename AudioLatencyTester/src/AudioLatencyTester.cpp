// Boost
#include <boost/lexical_cast.hpp>

#include "filters/audio_selector/audio_selector.h"
#include "filters/audio_capturer/audio_capturer.h"
#include "filters/audio_player/audio_player.h"

#include <iostream>
#include <string>

#define SAMPLE_RATE 44100
#define FORMAT AL_FORMAT_MONO16
#define DEFAULT_CAPTURE_SIZE 1470

audio_selector audio_selector_block;
audio_capturer audio_capturer_block(SAMPLE_RATE, FORMAT, DEFAULT_CAPTURE_SIZE);
audio_player audio_player_block(SAMPLE_RATE, FORMAT);

void print_help()
{
	std::cout << "Audio Latency Tester 1.0" << std::endl;
	std::cout << "Copyright (c) 2011 Cloud Forever. All rights reserved." << std::endl;
	std::cout << std::endl;

	std::cout << "Minimum capture size is 1 sample." << std::endl;
	std::cout << "Maximum capture size is " << SAMPLE_RATE << " samples." << std::endl;
	std::cout << std::endl;

	std::cout << "Default capture size is " << DEFAULT_CAPTURE_SIZE << " samples." << std::endl;
	std::cout << "Default expected latency is " << (1000 * DEFAULT_CAPTURE_SIZE / SAMPLE_RATE) << " ms." << std::endl;
	std::cout << std::endl;

	std::cout << "Type 'csNUM' to set capture size to NUM." << std::endl;
	std::cout << "Type 'elNUM' to set expected latency to NUM." << std::endl;
	std::cout << "Type 'cs-default' to set capture size to its default value." << std::endl;
	std::cout << "Type 'el-default' to set expected latency to its default value." << std::endl;
	std::cout << "Type 'help' to see these help messages again." << std::endl;
	std::cout << "Type 'exit' to close the application." << std::endl;
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	print_help();

	audio_selector_block.connect(&audio_capturer_block);
	audio_capturer_block.connect(&audio_player_block);

	audio_selector_block.select();
	std::cout << std::endl;

	std::string input;
	do
	{
		std::cout << "$ ";
		std::cin >> input;

		if (input == "cs-default")
		{
			audio_capturer_block.set_capture_size(DEFAULT_CAPTURE_SIZE);
			std::cout << "Capture size is set to " << DEFAULT_CAPTURE_SIZE << " samples." << std::endl;
			std::cout << "Expected latency is " << (1000 * DEFAULT_CAPTURE_SIZE / SAMPLE_RATE) << " ms." << std::endl;
			continue;
		}

		if (input == "el-default")
		{
			audio_capturer_block.set_capture_size(DEFAULT_CAPTURE_SIZE);
			std::cout << "Expected latency is set to " << (1000 * DEFAULT_CAPTURE_SIZE / SAMPLE_RATE) << " ms." << std::endl;
			std::cout << "Capture size is " << DEFAULT_CAPTURE_SIZE << " samples." << std::endl;
			continue;
		}

		if (input.substr(0, 2) == "cs")
		{
			input = input.substr(2, input.length() - 2);
			try
			{
				int capture_size = boost::lexical_cast<int>(input);
				if ((capture_size >= 1) && (capture_size <= SAMPLE_RATE))
				{
					audio_capturer_block.set_capture_size(capture_size);
					std::cout << "Capture size is set to " << capture_size << (capture_size > 1 ? " samples." : " sample.") << std::endl;
					std::cout << "Expected latency is " << (1000 * capture_size / SAMPLE_RATE) << " ms." << std::endl;
				}
				else
					std::cout << "Invalid input. " << capture_size << " is out of range [1.." << SAMPLE_RATE << "]." << std::endl;
			}
			catch (boost::bad_lexical_cast)
			{
				std::cout << "Invalid input. ";
				if (input.empty())
					std::cout << "No argument provided." << std::endl;
				else
					std::cout << "'" << input << "' is not an integer." << std::endl;
			}
			continue;
		}

		if (input.substr(0, 2) == "el")
		{
			input = input.substr(2, input.length() - 2);
			try
			{
				int expected_latency = boost::lexical_cast<int>(input);
				if ((expected_latency >= 1) && (expected_latency <= 1000))
				{
					int capture_size = expected_latency * SAMPLE_RATE / 1000;
					audio_capturer_block.set_capture_size(capture_size);
					std::cout << "Expected latency is set to " << expected_latency << " ms." << std::endl;
					std::cout << "Capture size is " << capture_size << (capture_size > 1 ? " samples." : " sample.") << std::endl;
				}
				else
					std::cout << "Invalid input. " << expected_latency << " is out of range [1..1000]." << std::endl;
			}
			catch (boost::bad_lexical_cast)
			{
				std::cout << "Invalid input. ";
				if (input.empty())
					std::cout << "No argument provided." << std::endl;
				else
					std::cout << "'" << input << "' is not an integer." << std::endl;
			}
			continue;
		}

		if (input == "help")
		{
			std::cout << std::endl;
			print_help();
			continue;
		}

		if (input == "exit")
			continue;

		std::cout << "Unknown command '" << input << "'." << std::endl;
	} while (input != "exit");

	return 0;
}
