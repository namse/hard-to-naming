#pragma once
class Acceptor
{
public:
	Acceptor(asio::io_service &io_service, const tcp::endpoint &endpoint)
		: acceptor_(io_service, endpoint),
		socket_(io_service) {
		Accept();
	};

private:
	void Accept();

	tcp::acceptor acceptor_;
	tcp::socket socket_;
};

