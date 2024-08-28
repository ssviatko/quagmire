#include <iostream>
#include <string>
#include <optional>
#include <deque>

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "data.h"

bool g_debug = false;
bool g_verbose = false;
unsigned int g_ratio = 30;
bool g_ratio_set = false;

enum {
	MODE_NONE,
	MODE_CREATE,
	MODE_EXTRACT
} g_mode;

std::string g_file;
std::deque<std::string> g_additional_args;

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
	{ "help", no_argument, NULL, 'h' },
	{ NULL, 0, NULL, 0 }
};

void error(const std::string& a_message)
{
	std::cout << std::endl << "ERROR: " << a_message << std::endl << std::endl;
	std::cout << "type quagmire -h for help." << std::endl;
}

int main(int argc, char **argv)
{
	int opt;
	g_mode = MODE_NONE;

	while ((opt = getopt_long(argc, argv, "vdr:c:x:h", g_options, NULL)) != -1) {
		switch (opt) {
		case 'd':
			g_debug = true;
			break;
		case 'v':
			g_verbose = true;
			break;
		case 'c':
			if (g_mode == MODE_EXTRACT) {
				error("only one mode can be selected.");
			}
			g_mode = MODE_CREATE;
			g_file = std::string(optarg);
			break;
		case 'x':
			if (g_mode == MODE_CREATE) {
				error("only one mode can be selected.");
			}
			g_mode = MODE_EXTRACT;
			g_file = std::string(optarg);
			break;
		case 'r':
			g_ratio = atoi(optarg);
			g_ratio_set = true;
			break;
		case 'h':
			usage();
			break;
		default:
			usage();
			break;
		}
	}
	if (g_debug) { 
		std::cout << std::boolalpha << "debug mode: " << g_debug << std::endl;
       		std::cout << "verbose mode: " << g_verbose << std::endl;
		std::cout << std::noboolalpha << "ratio: " << g_ratio << std::endl;
		std::cout << "mode: " << g_mode << std::endl;
		std::cout << "file: " << g_file << std::endl;
	}
	for (int i = optind; i < argc; ++i) {
		if (g_debug)
			std::cout << "found additional argument: " << std::string(argv[i]) << std::endl;
		g_additional_args.push_back(std::string(argv[i]));
	}

	// sanity check our options
	if (g_mode == MODE_NONE) {
		error("either the create or extract function must be selected.");
	}
	if (g_mode == MODE_EXTRACT) {
		if (g_additional_args.size() == 0)
			error("must specify at least 1 passphrase to extract plaintext file.");
		if (g_ratio_set)
			error("ratio setting only applies to create mode.");
	}
	if (g_mode == MODE_CREATE) {
		if ((g_ratio < 10) || (g_ratio > 80))
			error("ratio must be set between 10 and 80.");
		if (g_additional_args.size() % 2 == 1)
			error("missing plaintext filename on command line.");
		if (g_additional_args.size() < 2)
			error("must have at least one passphrase/plaintext filename pair to add to quagmire.");
	}

	return 0;
}

