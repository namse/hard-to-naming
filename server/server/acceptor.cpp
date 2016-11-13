#include "stdafx.h"
#include "acceptor.h"
#include "session.h"

void Acceptor::Accept()
{
	acceptor_.async_accept(socket_, [this](std::error_code ec) {
		if (!ec) {
			Session::create(std::move(socket_))->Start();
		}

		Accept();
	});
}
