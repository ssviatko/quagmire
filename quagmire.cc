#include <iostream>

#include <unistd.h>

#include "data.h"

void usage()
{
	std::cout << "Quagmire" << std::endl << std::endl;
	std::cout << "quagmire -c file.quagmire \"passphrase 1\" file1 \"passphrase2\" file2 ..." << std::endl;
	std::cout << "  Creates new quagmire containing file1, file2, etc. using the specified passphrases" << std::endl;
	std::cout << "  for each file." << std::endl;
	std::cout << "  Options: -r <ratio> will specify the ratio of encrypted data to random data," << std::endl;
	std::cout << "  default is 30." << std::endl;
	std::cout << "quagmire -c file.quagmire -r 40 \"passphrase 1\" file1 \"passphrase2\" file2 ..." << std::endl;
	std::cout << "  In this example, the ratio is set to 40. This means that 40% of the file will" << std::endl;
	std::cout << "  contain file data, while 60% of it will contain random data." << std::endl;
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	usage();
	return 0;
}

