#include "qm-engine.h"

namespace qm {

void quagmire_create(bool a_debug, bool a_verbose, const std::string& a_file, unsigned int a_ratio, std::deque<std::string>& a_args)
{
	if (a_debug) {
		std::cout << "sizeof sector: " << sizeof(sector_t) << std::endl;
		std::cout << "data_size: " << data_size << std::endl;
		std::cout << "pt_data_size: " << pt_data_size << std::endl;
	}
}

void quagmire_extract(bool a_debug, bool a_verbose, const std::string& a_file, std::deque<std::string>& a_args)
{
	
}

} // namespace qm

