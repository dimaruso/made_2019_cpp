#include <iostream>
#include <cassert>
#include "Formatter.h"

int main()
{
	Formatter format;

	auto text = format("{1}+{1} = {0}", 2, "one");
	assert(text == "one+one = 2");

	int a = 1;
	bool b = 0;
	std::string c = "42";

	text = format("{0} / {0} + {2} = {1}", b, c, a);
	assert(text == "0 / 0 + 1 = 42");

	assert(format("{0}+{0} + {1} + 0*{2}={2}", 1, '2', 4) == "1+1 + 2 + 0*4=4");

	std::cout << "Error test 1" << '\n';
	try
	{
		text = format("{1}+{12} = {0}", 2, "one");
	}
	catch (const std::runtime_error& error)
	{
		std::cout << error.what() << '\n';
	}

	std::cout << "Error test 2" << '\n';
	try
	{
		text = format("{1}+{-1} = {0}", 2, "one");
	}
	catch (const std::runtime_error& error)
	{
		std::cout << error.what() << '\n';
	}

	std::cout << "Error test 3" << '\n';
	try
	{
		text = format("{1+{1} = {0}", 2, "one");
	}
	catch (const std::runtime_error& error)
	{
		std::cout << error.what() << '\n';
	}

	std::cout << "Error test 4" << '\n';
	try
	{
		text = format("1}+{1} = {0}", 2, "one");
	}
	catch (const std::runtime_error& error)
	{
		std::cout << error.what() << '\n';
	}

	std::cout << "Tests completed successfully!" << '\n';
	system("pause");
	return 0;
}