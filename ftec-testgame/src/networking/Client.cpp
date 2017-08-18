#include "Client.h"

#if 0

#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <functional>

namespace ftec {

	using boost::asio::ip::tcp;

	boost::asio::io_service &getIOService()
	{
		static boost::asio::io_service io_service;
		return io_service;
	}
	tcp::resolver &getResolver()
	{
		static tcp::resolver resolver(getIOService());
		return resolver;
	}

	Client::Client()
		:m_Connected(false), m_Socket(getIOService())
	{
	}

	bool Client::connect(const std::string & ip, const std::string & service)
	{
		tcp::resolver::query query("localhost", "9898");


		tcp::resolver::iterator endpoint_iterator = getResolver().resolve(query);
		tcp::resolver::iterator end;

		boost::system::error_code error = boost::asio::error::host_not_found;

		while (error && endpoint_iterator != end) {
			m_Socket.close();
			m_Socket.connect(*endpoint_iterator++, error);
		}

		if (error) //TODO better error handling
			return false;

		m_Connected = true;

		std::thread thread([this]() {this->listen(); });
		
		onConnect();

		return true;
	}

	void Client::disconnect()
	{
		if (!m_Connected)
			return;

		m_Socket.close();
		m_Connected = false;

		onDisconnect();
	}

	void Client::listen()
	{
		for (;;)
		{
			std::array<char, 128> buffer;
			boost::system::error_code error;

			size_t len = m_Socket.read_some(boost::asio::buffer(buffer), error);
			
			if (error) {
				disconnect();
				break;
			}

			std::cout.write(buffer.data(), len);

			onMessage();
		}
	}

	void test_client()
	{

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

#endif