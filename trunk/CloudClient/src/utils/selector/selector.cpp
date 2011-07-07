#include "selector.h"

selector::selector(std::string greeting, bool autoselection)
{
	this->reset();
	this->set_greeting(greeting);
	this->set_autoselection(autoselection);
}

selector::~selector()
{
}

void selector::add_option(std::string description, void* identifier)
{
	// Add the option.
	this->options.insert(std::pair<std::string, void*>(description, identifier));
}

void* selector::get_selection()
{
	// Check whether the selection have been performed.
	if (!this->selected)
	{
		std::cout << "Selector: the selection haven't been performed yet." << std::endl;
		throw internal_exception();
	}

	// Return the selected identifier.
	return this->selection;
}

void selector::reset()
{
	this->autoselection = true;
	this->greeting = "";
	this->selected = false;
	this->selection = NULL;
}

void selector::select()
{
	// Check whether there are options to select from.
	if (this->options.begin() == this->options.end())
	{
		std::cout << "Selector: no options to select from." << std::endl;
		throw internal_exception();
	}

	// Print the greeting message if it is present.
	if (!this->greeting.empty())
		std::cout << this->greeting << std::endl;

	// Print the options to select from.
	int counter = 0;
	for (std::map<std::string, void*>::iterator iterator = this->options.begin(); iterator != this->options.end(); ++iterator)
		std::cout << "  " << ++counter << ". " << iterator->first << std::endl;

	// Prepare for selection.
	int selected_index = 0;

	// Check if there is any choice.
	if (this->autoselection && (counter == 1))
	{
		// Select the option if there is no choice and auto selection is enabled.
		std::cout << "Automatically choosing the only available option." << std::endl;
		selected_index = 1;
	}
	else
	{
		// Repeat asking for selection until an acceptable value is received.
		do
		{
			std::cout << "Your choice: ";
			std::string line;
			std::getline(std::cin, line);
			try
			{
				selected_index = boost::lexical_cast<int>(line);
			}
			catch (boost::bad_lexical_cast&)
			{
				std::cout << "Invalid input. Try again." << std::endl;
			}
		} while ((selected_index <= 0) || (selected_index > counter));
	}

	// Find an identifier of the selected option.
	std::map<std::string, void*>::iterator iterator = this->options.begin();
	for (int i = 1; i < selected_index; i++)
		iterator++;

	// Remember the selected identifier.
	this->selection = iterator->second;
	this->selected = true;
}

void selector::set_autoselection(bool autoselection)
{
	this->autoselection = autoselection;
}

void selector::set_greeting(std::string greeting)
{
	this->greeting = greeting;
}
