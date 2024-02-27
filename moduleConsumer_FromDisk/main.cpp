/*
* This uses a external module (on disk)
* It needs .ifc for Project Settings > C/C++ > General > Additional Module Dependencies
* .ifc is generated to Intemediate directory by default
* It also needs the corresponding .lib in Linker input.
* This makes the usage of external modules redundant, since it's easier and more stable to just use a static library
*/

#include <iostream>
#include <string>
#include <vector>

import HelperFunctions; 


int main()
{
	std::vector<std::string> name = { "John", "Doe" };
	std::cout << join(name);
}