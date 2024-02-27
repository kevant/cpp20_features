/*
* span: non-owning view of contiguous memory
* 
* Main use case for span seems to for handling buffers size through the compiler
* Supports STL containers or C arrays
* This is recommended to use in CppCoreGuidelines https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md
*/
#include <iostream>
#include <span>
#include <vector>
#include <array>

void printNumbers_span(std::span<int> numbers)
{
	for (auto const& i : numbers)
		std::cout << i;
	std::cout << std::endl;
}

void printNumbers_C(int* numbers, size_t bufferSize)
{
	for (size_t i = 0; i < bufferSize; ++i)
		std::cout << numbers[i];
	std::cout << std::endl;
}

int main()
{
	const size_t BUFFER_SIZE = 5;
	int numbers[BUFFER_SIZE] = { 1, 2, 3, 4, 5 };
	printNumbers_C(numbers, BUFFER_SIZE);

	// buffer size not needed
	// less error prone to out-of-range errors
	printNumbers_span(numbers); 

	// supports STL containers
	std::vector<int> vec_numbers{ 1, 2, 3, 4, 5 };
	printNumbers_span(vec_numbers);
	std::array<int, 5> arr_numbers{ 1, 2, 3, 4, 5 };
	printNumbers_span(arr_numbers);

	// can pass in count for span
	printNumbers_span({ numbers, 2 }); // print 12
}