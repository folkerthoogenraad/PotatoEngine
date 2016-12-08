#pragma once

#include <functional>
#include <iostream>

namespace def {
	class Defer {
		std::function<void()> m_Func;
	public:
		Defer(std::function<void()> f) : m_Func(f){}
		~Defer() { m_Func(); };
	};
}

//For recursive append
#define DEFER_(x, y) x ## y
#define DEFER_2(x, y) DEFER_(x, y)

//defer a lambda expression
#define deferl(lambda) def::Defer DEFER_2(defer_,__LINE__)(lambda)
//Or let the defer handle your lambda for you
#define defer(code) deferl([&](){code;});

namespace def_test {

	void test() {

		std::cout << "1";

		defer(
			std::cout << "4";
			std::cout << "5";
		);

		defer(
			std::cout << "3";
		);

		std::cout << "2";

	}

	void testException() {

		std::cout << "1";

		defer(
			std::cout << "3";
			std::cout << "4";
		);

		defer(
			std::cout << "2";
		);
		
		throw std::exception("Failure or success? Find out next week in the finals.");
	}
}