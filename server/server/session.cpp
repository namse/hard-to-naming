#include "stdafx.h"
#include "session.h"
#include "session_manager.h"
#include "packet_parser.h"

auto manager = SessionManager::GetManager();

Session::SharedPtr Session::create(tcp::socket socket)
{
	struct make_shared_enabler : public Session {
		make_shared_enabler(tcp::socket socket) : Session(std::move(socket)) {}
	};
	return std::make_shared<make_shared_enabler>(std::move(socket));
}

Session::Session(tcp::socket socket)
	: socket_(std::move(socket))
{
	socket_.set_option(tcp::no_delay(false));
}

void Session::Start()
{
	manager->Join(shared_from_this());
	Read();
}

void Session::Read()
{
	auto self(shared_from_this());
	socket_.async_read_some(asio::buffer(buffer_.End(), buffer_.WriteableLength()),
		[this, self](std::error_code ec, std::size_t bytes_transferred)
	{
		if (ec) {
			Disconnect();
			return;
		}
		
		HandlePacket(bytes_transferred);

		Read();
	});
}

void Session::Disconnect()
{
	manager->Leave(shared_from_this());
}

void Session::HandlePacket(std::size_t bytes_transferred)
{
	buffer_.OnWritten(bytes_transferred);

	// TODO : handle Packet.
	while (buffer_.ReadableLength()) {
		auto length = PacketParser::ParseAndHandlePacket(buffer_.Begin(), buffer_.ReadableLength());

		if (0 == length) {
			break;
		}

		buffer_.Consume(length);
	}

	if (0 == buffer_.WriteableLength()) {
		auto is_shift_success = buffer_.Shift();
		if (!is_shift_success) {
			// error, maybe buffer over-flow.
			Disconnect();
		}
	}
}
