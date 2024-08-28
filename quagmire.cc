#include <iostream>
#include <string>
#include <optional>

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "data.h"

bool g_debug = false;
bool g_verbose = false;
unsigned int g_ratio = 30;

enum {
	MODE_NONE,
	MODE_CREATE,
	MODE_EXTRACT
} g_mode;

std::string g_file;

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

struct option g_options[] = {
	{ "verbose", no_argument, NULL, 'v' },
	{ "debug", no_argument, NULL, 'd' },
	{ "ratio", required_argument, NULL, 'r' },
	{ "create", required_argument, NULL, 'c' },
	{ "extract", no_argument, NULL, 'x' },
	{ NULL, 0, NULL, 0 }
};

int main(int argc, char **argv)
{
	int opt;
	g_mode = MODE_NONE;

	while ((opt = getopt_long(argc, argv, "vdr:c:x:", g_options, NULL)) != -1) {
		switch (opt) {
		case 'd':
			g_debug = true;
			break;
		case 'v':
			g_verbose = true;
			break;
		case 'c':
			g_mode = MODE_CREATE;
			g_file = std::string(optarg);
			break;
		case 'x':
			g_mode = MODE_EXTRACT;
			g_file = std::string(optarg);
			break;
		case 'r':
			g_ratio = atoi(optarg);
			break;
		default:
			usage();
			break;
		}
	}
	std::cout << std::boolalpha << "debug mode: " << g_debug << " verbose mode: " << g_verbose << std::endl;
	std::cout << std::noboolalpha << "ratio: " << g_ratio << " mode: " << g_mode << " file: " << g_file << std::endl;
	for (int i = optind; i < argc; ++i) {
		std::cout << "found additional argument: " << std::string(argv[i]) << std::endl;
	}
	return 0;
}

