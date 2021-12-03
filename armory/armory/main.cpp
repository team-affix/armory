#include "controller.h"
#include <iostream>
#include <string>

int main()
{
	while (true)
	{
		std::string l_line;
		std::getline(std::cin, l_line);
		armory::input_line(l_line);
	}
}
