#include <iterator>
#include <sstream>
#include <vector>
#include <string>
export module HelperFunctions; // module declaration

// export declaration
export std::string join(std::vector<std::string> const & strings, const char * delim = ", ")
{
	std::ostringstream os;
	auto b = begin(strings), e = end(strings);
	if(b != e) 
	{
		std::copy(b, prev(e), std::ostream_iterator<std::string>(os, delim));
		b = prev(e);
	}
	if (b != e) 
	{
		os << *b;
	}

	return os.str();
}