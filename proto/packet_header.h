#pragma once
namespace packet {
	class PacketHeader {
	public:
		PacketHeader();
		PacketHeader(std::size_t length, uint32_t type);
		std::size_t length_;
		uint32_t type_;

		bool SerializeToArray(char* const buffer, const std::size_t max_bytes, std::size_t &written);
		bool ParseFromArray(char* const buffer, const std::size_t max_bytes, std::size_t &read);
	};
}
