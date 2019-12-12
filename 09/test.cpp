#include <iostream>
#include <cassert>
#include <string>
#include "ThreadPool.h"

void goodbye(const std::string& s)
{
	std::cout << "Goodbye " << s << '\n';
}

class Object
{
public:
	void hello(const std::string& s1, const std::string& s2)
	{
		std::cout << "Hello " << s1 << s2 <<'\n';
	}
};

struct A {};

void foo(const A&) {}

void foo2() {}

int plusSeven(const int& a)
{
	return a + 7;
}

int main()
{
	typedef std::function<void(const std::string&, const std::string&)> ExampleFunction;
	Object instance;
	std::string str("World");
	ExampleFunction f = std::bind(&Object::hello, &instance,
		std::placeholders::_1, std::placeholders::_2);

	ThreadPool pool(4);
	assert(pool.size() == 4);

	auto task1 = pool.exec(foo, A());
	task1.get();
	
	auto task2 = pool.exec([]() { return 1; });
	task2.get();
	
	auto task3 = pool.exec(f,str,"!");
	task3.get();

	f = std::bind(&goodbye, std::placeholders::_1);

	auto task4 = pool.exec(f, str,"");
	task4.get();

	auto task5 = pool.exec(foo2);
	task5.get();

	auto task6 = pool.exec(plusSeven,35);
	assert(task6.get() == 42);

	pool.~ThreadPool();
	assert(pool.size() == 0);

	try
	{
		auto task7 = pool.exec(plusSeven, 2);
		assert(false);
		task7.get();
		assert(false);
	}
	catch (const std::runtime_error& error)
	{
		std::string er = "No available thread";
		assert(error.what() == er);
	}

	std::cout << "Tests completed successfully!" << '\n';
	system("pause");
	return 0;
}