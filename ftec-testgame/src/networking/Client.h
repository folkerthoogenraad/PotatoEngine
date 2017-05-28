#pragma once

namespace ftec {
	void test_client();

	class Client {
	private:

	public:
		bool m_Connected;

	public:
		Client();
		~Client();

		void connect(const std::string &ip, const std::string &service);
		void disconnect();


	};
}