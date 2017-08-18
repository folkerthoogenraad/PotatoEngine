#pragma once

#if 0
#include <boost/asio.hpp>		//TODO try to remove this

#include "util/CallbackHandler.h"

//TODO way better error handling

namespace ftec {

	class Client {
	private:
		boost::asio::ip::tcp::socket m_Socket;
		bool m_Connected;
	public:
		CallbackHandler<void()> onConnect;
		CallbackHandler<void()> onDisconnect;
		CallbackHandler<void()> onMessage;
	public:
		Client();

		bool connect(const std::string &ip, const std::string &service);
		void disconnect();

		bool isConnected() const { return m_Connected; };

	private:
		void listen();
	};

	void test_client();
}

#endif