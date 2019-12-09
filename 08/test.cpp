#include <iostream>
#include <cassert>
#include <string>
#include "MyVector.h"

void testVoid()
{
	MyVector<int> v;
	assert(v.capacity() == 0);
	assert(v.empty() == true);
	assert(v.size() == 0);

	v.push_back(0);
	assert(v.capacity() == 1);
	assert(v.empty() == false);
	assert(v.size() == 1); 
	assert(v[0] == 0);

	v.push_back(111);
	v[1] = 77;
	assert(v.capacity() == 2);
	assert(v.empty() == false);
	assert(v.size() == 2);
	assert(v[0] == 0);
	assert(v[1] == 77);

	v.push_back(v[1]*2 + 10 + v[0]);
	assert(v.capacity() == 3);
	assert(v.empty() == false);
	assert(v.size() == 3);
	assert(v[0] == 0);
	assert(v[1] == 77);
	assert(v[2] == 164);
	
	v.push_back(1);
	assert(v.capacity() == 4);
	v.push_back(1);
	assert(v.capacity() == 6);
	v.push_back(1);
	assert(v.capacity() == 6);
	v.push_back(1);
	assert(v.capacity() == 9);
	assert(v.size() == 7);

	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	assert(v.capacity() == 13);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	assert(v.capacity() == 19);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	assert(v.capacity() == 28);
}

void testSize()
{
	size_t a = 6;
	MyVector<int> v(a);
	assert(v.capacity() == 6);
	assert(v.empty() == false);
	assert(v.size() == 6);
	assert(v[0] == 0); 
	v[1] = 10;
	assert(v[0] == 0);
	v.push_back(42);
	assert(v.size() == 7);
	assert(v[6] == 42);
}

void testDefVal()
{
	MyVector<int> v(42, 7);
	assert(v.empty() == false);
	assert(v.size() == 42);
	assert(v.capacity() == 42);
	assert(v[0] == 7);
	assert(v[18] == 7);
	assert(v[41] == 7);

	MyVector<std::string> v2(111, "abacaba");
	assert(v2.empty() == false);
	assert(v2.size() == 111);
	assert(v2.capacity() == 111);
	assert(v2[0] == "abacaba");
	assert(v2[18] == "abacaba");
	assert(v2[110] == "abacaba");
	v2[110] += "bada";
	assert(v2[110] == "abacababada");
	v2.resize(200);
	assert(v2[110] == "abacababada");
	v2[150] = "bada";
	assert(v2[150] == "bada");
}

void testList()
{
	MyVector<int> v{1,2,3,4,5,6,7,8,9,0};
	assert(v.empty() == false);
	assert(v.size() == 10);
	assert(v.capacity() == 10);
	assert(v[0] == 1);
	assert(v[6] == 7);
	assert(v[9] == 0);
	
	v.pop_back();
	assert(v.size() == 9);
	assert(v.capacity() == 10);
	assert(v[0] == 1);
	assert(v[6] == 7);
	assert(v[8] == 9);

	v.push_back(11);
	v.push_back(-1007);
	assert(v.size() == 11);
	assert(v.capacity() == 15);
	assert(v[0] == 1);
	assert(v[6] == 7);
	assert(v[8] == 9);
	assert(v[9] == 11);
	assert(v[10] == -1007);
}

void testMem()
{
	MyVector<int> v{ 1,2,3,4,5,6,7,8,9,0 };
	assert(v.empty() == false);
	assert(v.size() == 10);
	assert(v.capacity() == 10);

	v.resize(21);
	assert(v.empty() == false);
	assert(v.size() == 21);
	assert(v.capacity() == 21);

	v.resize(2);
	assert(v.empty() == false);
	assert(v.size() == 2);
	assert(v.capacity() == 21);
	try
	{
		int a = v[2];
		assert(false);
	}
	catch (const std::out_of_range& error)
	{
		assert(true);
	}

	v.clear();
	assert(v.capacity() == 21);
	assert(v.empty() == true);
	assert(v.size() == 0);
	try
	{
		int a = v[0];
		assert(false);
	}
	catch (const std::out_of_range& error)
	{
		assert(true);
	}

	v.push_back(77);
	assert(v.capacity() == 21);
	assert(v.empty() == false);
	assert(v.size() == 1);
	assert(v[0] == 77);

	v.reserve(100);
	assert(v.capacity() == 100);
	assert(v.empty() == false);
	assert(v.size() == 1);
	assert(v[0] == 77);

	v.reserve(10);
	assert(v.capacity() == 100);
	assert(v.empty() == false);
	assert(v.size() == 1);
	assert(v[0] == 77);

	v.~MyVector();
	assert(v.capacity() == 0);
	assert(v.empty() == true);
	assert(v.size() == 0);
}

void testIter()
{
	MyVector<int> v{ 1,2,3,4,5,6,7,8,9 };
	size_t k = 0;
	for (auto i : v)
		assert(++k == i);

	std::for_each(v.begin(), v.end(), [](int x) { std::cout << x << " ";});
	std::cout << '\n';

	std::for_each(v.cbegin(), v.cend(), [](int x) { std::cout << x << " "; });
	std::cout << '\n';

	std::for_each(v.rbegin(), v.rend(), [](int x) { std::cout << x << " "; });
	std::cout << '\n';

	std::for_each(v.crbegin(), v.crend(), [](int x) { std::cout << x << " "; });
	std::cout << '\n';
}

int main()
{
	testVoid();
	testSize();
	testDefVal();
	testList();
	testMem();
	testIter();
	std::cout << "Tests completed successfully!" << '\n';
	system("pause");
	return 0;
}
