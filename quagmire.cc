#include <iostream>
#include <string>
#include <optional>

#include <unistd.h>

#include "data.h"

void usage()
{
	std::cout << "Quagmire v" << RELEASE_NUMBER << " build " << BUILD_NUMBER << std::endl;
	std::cout << "Built on: " << BUILD_DATE << std::endl << std::endl;
	ss::data l_help;
	try {
		l_help.load_file("help.txt");
		std::optional<std::string> line;
		do {
			line = l_help.read_std_str_delim();
			if (line.has_value())
				std::cout << line.value() << std::endl;
		} while (line.has_value());
	} catch (ss::data_exception& e) {
		std::cout << "unable to display help file." << std::endl;
		std::cout << "reason: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	usage();
	return 0;
}

