#include "stdafx.h"
#include "packet_header.h"
#include "byte128.h"
namespace packet {
	PacketHeader::PacketHeader()
	{

	}

	PacketHeader::PacketHeader(std::size_t length, uint32_t type)
		: length_(length), type_(type)
	{

	}
	bool PacketHeader::SerializeToArray(char * const buffer, const std::size_t max_bytes, std::size_t & written)
	{
		std::size_t length_written = 0;
		if (false == SerializeToByte128(
				length_, 
				buffer,
				max_bytes,
				length_written)) {
			return false;
		}
		std::size_t type_written = 0;
		if (max_bytes <= length_written ||
			false == SerializeToByte128(
				type_,
				buffer + length_written,
				max_bytes - length_written,
				type_written)) {
			return false;
		}

		written = length_written + type_written;
		return true;
	}
	bool PacketHeader::ParseFromArray(char * const buffer, const std::size_t max_bytes, std::size_t & read)
	{
		std::size_t length_read = 0;
		if (false == ParseFromByte128(
				length_,
				buffer,
				max_bytes,
				length_read)) {
			return false;
		}

		std::size_t type_read = 0;
		if (max_bytes <= length_read ||
			false == ParseFromByte128(
				type_,
				buffer + length_read,
				max_bytes - length_read,
				type_read)) {
			return false;
		}

		read = length_read + type_read;

		return true;
	}
}
