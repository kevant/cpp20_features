#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>
#include <functional>

// Rot13 encryption for example. Not relevant to <ranges>
char encrypt_rot13(const char x, const char a);
char encrypt_rot13(const char x);

int main()
{
	// Simple example
	{
		std::vector<int> numbers = { 1,2,3,4,5 };
		auto even = [](int i) -> bool {return i % 2 == 0; };
		auto square = [](int i) -> int {return i * i; };

		// "functional" composing syntax
		for (int i : std::views::transform(std::views::filter(numbers, even), square))
			std::cout << i << ' ';
		std::cout << '\n';

		// new "pipe" composing syntax
		for (int i : numbers | std::views::filter(even) | std::views::transform(square))
			std::cout << i << ' ';
		std::cout << '\n';

		// std::ranges::for_each + "pipes"
		using namespace std::views;
		auto show = [](int i) {std::cout << i << " "; };
		std::ranges::for_each(
			numbers
			| filter(even)
			| transform(square)
			, show);
		std::cout << '\n';
	}

	std::cout << "===========================\n";

	// more relevant example, with simplified functions
	{
		std::string us_password = " %#Hello&* "; // unsanitized text
		std::string s_password; // sanitized text

		auto non_white_space = [](unsigned char c) -> bool { return c != ' '; };
		auto alpha_numeric = [](unsigned char c) -> bool {
			if ((c >= 48 && c <= 57) || // digits
				(c >= 65 && c <= 90) || // uppercase
				(c >= 97 && c <= 122)) // lowercase
				return true;
			else
				return false;
			};
		auto encrypt = [](unsigned char c) -> unsigned char { return encrypt_rot13(c); };

		// std::ranges::copy is similar to std::copy, 
		// with functionality to compose functions
		std::ranges::copy(
			us_password
			| std::views::filter(non_white_space)
			| std::views::filter(alpha_numeric)
			| std::views::transform(encrypt)
			, std::back_inserter(s_password));

		std::cout << "before:\'" << us_password << "\'" << std::endl;
		std::cout << " after:\'" << s_password << "\'" << std::endl; // prints "Uryyb"
	}
}

char encrypt_rot13(const char x, const char a)
{
	return ((x - a + 13) % 26) + a;
}

char encrypt_rot13(const char x)
{
	char start;
	if (x >= 'A' && x <= 'Z')
		return encrypt_rot13(x, 'A');
	else if (x >= 'a' && x <= 'z')
		return encrypt_rot13(x, 'a');
	else
		return x;
}
