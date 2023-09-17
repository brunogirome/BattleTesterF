#include "FancyDialog.h"

void FancyDialog(std::string text, int milliseconds)
{
	for (std::size_t i = 0; i < text.length(); i++) {
		std::string letter = text.substr(i, 1);

		std::cout << letter;

		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	std::cout << '\n';
}
