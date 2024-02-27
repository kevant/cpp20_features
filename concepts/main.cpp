/*
* Concepts are compile time predicated that helps to constraint types
* This allows certain errors to be brought forward and raised during compile,
* reducing the errors that may occur during runtime.
* 
* It made tenplates for readable, which may allow more complex templates to be used.
*/
#include <iostream>
#include <chrono>

/*
* A simple power function using postive integers
* Error of passing in wrong types can be raised during compile-time,
* Without using assert or additional checks during runtime
*/
template <typename T>
concept unsigned_integral = std::is_integral_v<T> && !std::signed_integral<T>;

template<typename T> requires unsigned_integral<T>
T simple_power(T a, T b)
{
	T res = 1;
	for (unsigned int i = 0; i < b; ++i)
	{
		res *= a;
	}
	return res;
}

// Constraint to expression; i.e. functions
template <typename Fn>
concept callable = requires (Fn f) { f(); };

template<typename Fn> requires callable<Fn>
void log_function_call(Fn func)
{
	namespace ch = std::chrono;
	std::cout << "["
		<< std::format("{:%T}", ch::floor<ch::seconds>(ch::system_clock::now()))
		<< "] "
		<< typeid(Fn).name()
		<< " invoked"
		<< std::endl;

	func();
}

struct A
{
	void operator()()
	{
		std::cout << "Hello from struct A" << std::endl;;
	}
};

int main()
{
	{
		unsigned int a = 2, b = 4;

		std::cout << simple_power(a, b) << std::endl; // ok
		//std::cout << simple_power(a, -2) << std::endl; // error, as second argument is signed
		//std::cout << simple_power(1.0, 2.0) << std::endl; // error, as arguments are double
	}
	std::cout << "==============================" << std::endl;
	{
		A a;
		log_function_call(a);
		log_function_call([]() {std::cout << "hello from lambda"; });
		//log_function_call(1); // error
	}
}