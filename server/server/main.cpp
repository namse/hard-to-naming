#include "stdafx.h"
#include "acceptor.h"

int main()
{
	try {
		asio::io_service io_service;
		asio::ip::tcp::endpoint endpoint(tcp::v4(), PORT);

		Acceptor acceptor(io_service, endpoint);

		std::vector<std::thread> threads;
		for (int i = 0; i < THREAD_COUNT; i++) {
			threads.push_back(std::thread([&io_service]() {
				io_service.run();
			}));
		}

		io_service.run();

		for (auto& thread : threads) {
			thread.join();
		}

	} catch (std::exception& e)	{
		std::cerr << e.what() << std::endl;
	}
    return 0;
}
