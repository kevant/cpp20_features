/*
* Easiest method is to add module through project references
* Right-click Project > Add > References...
* Module project must be static library
* 
* This can be useful for utility functions use by all .vcxproj within a .sln
* e.g. Logger, string util, maths etc
* 
* Becomes a lot less relevant or useful if the module is going to be consumed as an external module
* See ModuleConsumer_FromDisk project settings
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