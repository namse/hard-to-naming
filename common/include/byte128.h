#pragma once

inline bool ParseFromByte128(
		uint32_t &value,
		char* const buffer,
		const std::size_t max_bytes,
		std::size_t &read) {
	uint32_t ret = 0;
	for (std::size_t i = 0; i < max_bytes; i++) {
		ret += (buffer[i] & 0b01111111) << (7 * i);
		if (!(buffer[i] & 0b10000000)) {
			value = ret;
			read = i + 1;
			return true;
		}
	}
	return false;
}

inline bool SerializeToByte128(
		const uint32_t target,
		char* const buffer,
		const std::size_t max_bytes,
		std::size_t &written) {
	uint32_t copied = target;
	std::size_t index = 0;
	do {
		if (index > 0) {
			buffer[index - 1] |= 0b10000000;
		}
		buffer[index] = copied & 0b01111111;
		copied >>= 7;
		++index;
		if (index > max_bytes) {
			return false;
		}
	} while (copied);
	written = index;
	return true;
}
