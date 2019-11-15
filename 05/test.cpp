#include <iostream>
#include <cassert>
#include <sstream>
#include "MySerializer.h"


struct Data
{
	uint64_t a;
	bool b;
	uint64_t c;
	template <class MySerializer>
	Error serialize(MySerializer& serializer)
	{
		return serializer(a,b,c);
	}
};
struct Data2
{
	uint64_t a;
	bool b;
	int c;
	template <class MySerializer>
	Error serialize(MySerializer& serializer)
	{
		return serializer(a, b, c);
	}
};
struct Data3
{
	uint64_t a;
	bool b;
	template <class MySerializer>
	Error serialize(MySerializer& serializer)
	{
		return serializer(a, b);
	}
};
int main()
{

	Data x{ 1, true, 2 };
	Data y{ 1, false, 0 };
	Data2 z{ 1, false, 0 };
	Data3 w{ 1, false};
	std::stringstream stream;

	MySerializer serializer(stream);
	serializer.save(x);



	MyDeserializer deserializer(stream);
	const Error err = deserializer.load(y);

	assert(err == Error::NoError);

	assert(x.a == y.a);
	assert(x.b == y.b);
	assert(x.c == y.c);

	const Error err2 = deserializer.load(z);

	assert(err2 == Error::CorruptedArchive);

	const Error err3 = deserializer.load(w);

	assert(err3 == Error::CorruptedArchive);

	std::cout << "Tests completed successfully!" << '\n';
	system("pause");
	return 0;
}