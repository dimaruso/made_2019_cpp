#include <iostream>
#include <sstream>
#include <cassert>
#include "MyBigInt.h"

int main()
{
	MyBigInt a;
	MyBigInt b = 42;
	int c = 77;
	int d = 42;

	a = -b;//a = -42
	std::cout << "a = " << a << " = -42" << '\n';
	std::cout << "b = " << b << " = 42" << '\n';

	assert(a != b);
	assert(a == -42);
	assert(42 == -a);
	assert(a == -b);

	a = 1;
	std::cout << "a = " << a << " == 1" << '\n';
	assert(a == 1);
	a = -a;
	a = 1000+a;
	std::cout << "a = " << a << " == 999" << '\n';
	assert(999 == a);
	a = -42;

	std::cout << "a+b = " << a+b << " == 0" << '\n';
	assert(a+b == 0);
	
	b = c;//b = 77
	std::cout << "b = " << b << " == 77" << '\n';
	assert(b == c);
	assert(a < c);
	assert(c > a);
	assert(a <= c);
	assert(c >= a);

	MyBigInt f(a);//f = -42
	std::cout << "f = " << f << " == -42" << '\n';
	assert(f == a);

	f = -f - d +a ;//f = -42 
	std::cout << "f = " << f << " == -42" << '\n';
	assert(f == -42);
	assert(f == -d);

	f = -f - d - a;//f = 42
	std::cout << "f = " << f << " == 42" << '\n';
	assert(f == 42);

	std::stringstream inp;
	inp << "10000000000";
	inp >> f;
	std::cout << "f = " << f << '\n';
	
	std::stringstream inp2;

	inp2 << "-10000000001";
	inp2 >> a;
	std::cout << "a = " << a << '\n';
	MyBigInt go = a + f;
	std::cout << "a+f = " << a + f << " == -1" << '\n';
	assert(a+f == -1);

	std::cout << "Tests completed successfully!" << '\n';
	system("pause");
	return 0;
}