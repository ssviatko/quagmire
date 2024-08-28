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

constexpr std::uint16_t data_size = 8106;

// BF7-CBC-HMAC-SHA2-256 encrypted buffer will contain exactly 32 bytes less than the actual plaintext data
// because of the 32 byte HMAC which sits at the beginning of the buffer.

constexpr std::uint16_t pt_data_size = data_size - 32;

// 8192 byte sector
typedef struct __attribute__((__packed__)) {
	std::uint32_t crc;
	std::uint8_t fileindex;
	std::uint8_t namelen;
	std::uint8_t name[62];
	std::uint32_t chunk_id;
	std::uint16_t chunk_len;
	std::uint32_t total_chunks;
	std::uint32_t prev_sector;
	std::uint32_t next_sector;
	std::uint8_t data[data_size];
} sector_t;

void quagmire_create(bool a_debug, bool a_verbose, const std::string& a_file, unsigned int a_ratio, std::deque<std::string>& a_args);
void quagmire_extract(bool a_debug, bool a_verbose, const std::string& a_file, std::deque<std::string>& a_args);

} // namespace qm

#endif // QM_ENGINE_H
