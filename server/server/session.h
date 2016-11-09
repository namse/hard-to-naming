#pragma once
#include "buffer.h"

class Session : public std::enable_shared_from_this<Session>
{
public:
	using SharedPtr = std::shared_ptr<Session>;
	static SharedPtr create(tcp::socket socket);

protected:
	Session(tcp::socket socket);

private:
	void Start();
	void Read();
	void Disconnect();
	void HandlePacket(std::size_t bytes_transferred);

	tcp::socket socket_;
	Buffer buffer_;
};
