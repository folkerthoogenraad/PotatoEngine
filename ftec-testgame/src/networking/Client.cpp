#include "Client.h"

#include <iostream>
#include <boost/asio.hpp>

namespace ftec {
	void test_client()
	{
		using boost::asio::ip::tcp;

		try {
			boost::asio::io_service io_service;
			tcp::resolver resolver(io_service);

			tcp::resolver::query query("localhost", "9898");

			tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
			tcp::resolver::iterator end;

			tcp::socket socket(io_service);
			boost::system::error_code error = boost::asio::error::host_not_found;
			
			while (error && endpoint_iterator != end){
				socket.close();
				socket.connect(*endpoint_iterator++, error);
			}

			if (error)
				throw boost::system::system_error(error);

			for (;;)
			{
				std::array<char, 128> buffer;
				boost::system::error_code error;

				size_t len = socket.read_some(boost::asio::buffer(buffer), error);
				if (error == boost::asio::error::eof)
					break; // Connection closed cleanly by peer.
				else if (error)
					throw boost::system::system_error(error); // Some other error.

				std::cout.write(buffer.data(), len);
			}
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
}
