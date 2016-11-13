#include "stdafx.h"
#include "google/protobuf/io/zero_copy_stream_impl_lite.h"
#include "packet.pb.h"
#include "byte128.h"
#include "packet_header.h"

struct membuf : std::streambuf
{
	membuf(char* begin, char* end) {
		this->setg(begin, begin, end);
	}
};

int main()
{
	
	asio::io_service io_service;
	tcp::socket socket(io_service);
	tcp::endpoint endpoint(asio::ip::address::from_string("127.0.0.1"), 12345);
	char out_buffer[1024];
	try {
		socket.connect(endpoint);
		std::size_t total_size;
		{	
			packet::TestPacket packet;
			packet.set_id(300);

			packet::PacketHeader header(packet.ByteSize(), packet::PacketType::TEST_PACKET);

			std::size_t buffer_size = 1024;
			std::size_t header_size = 0;
			std::size_t index = 0;
			auto success = header.SerializeToArray(out_buffer, buffer_size, header_size);
			success = packet.SerializeToArray(out_buffer + header_size, buffer_size - header_size);
			std::size_t body_size = packet.ByteSize();
			total_size = header_size + body_size;
		}

		
		{
			packet::PacketHeader header;
			std::size_t header_size = 0;
			auto success = header.ParseFromArray(out_buffer, total_size, header_size);

			packet::TestPacket new_packet;
			success = new_packet.ParseFromArray(out_buffer + header_size, total_size - header_size);
		}


		socket.write_some(asio::buffer(out_buffer, total_size));
	}
	catch (std::exception exception) {
		std::cout << exception.what() << std::endl;
	}

    return 0;
}
