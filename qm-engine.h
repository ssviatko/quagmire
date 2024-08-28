#ifndef QM_ENGINE_H
#define QM_ENGINE_H

#include <iostream>
#include <string>
#include <deque>
#include <exception>
#include <stdexcept>

#include <cstdint>

#include "data.h"

namespace qm {

// 8192 byte sector
typedef struct {
	// 64 bytes
	std::uint8_t fileindex;
	std::uint8_t namelen;
	std::uint8_t name[62];
	// 16 bytes
	std::uint32_t chunk_id;
	std::uint32_t total_chunks;
	std::uint32_t prev_sector;
	std::uint32_t next_sector;
	// 8112 byte data buffer
	std::uint8_t data[8112];
} sector_t;

void quagmire_create(bool a_debug, bool a_verbose, const std::string& a_file, unsigned int a_ratio, std::deque<std::string>& a_args);
void quagmire_extract(bool a_debug, bool a_verbose, const std::string& a_file, std::deque<std::string>& a_args);

} // namespace qm

#endif // QM_ENGINE_H
