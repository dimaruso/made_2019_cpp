#pragma once
#include <iostream>
#include <string>

class MyBigInt
{
public:
	MyBigInt():
		size(1),
		sign(true),
		data(new char[1]{'0'})
	{
	}
	MyBigInt(const int& _data)
	{
		if (_data > 0)
		{
			std::string tmp = std::to_string(_data);
			size = tmp.length();
			data = new char[size];
			for (int i = 0; i <size ; ++i)
			{
				data[i] = tmp[size-1 - i];
			}
			sign = true;
		} 
		else if(_data < 0)
		{
			std::string tmp = std::to_string(-_data);
			size = tmp.length();
			data = new char[size];
			for (int i = 0; i < size; ++i)
			{
				data[i] = tmp[size - 1 - i];
			}
			sign = false;
		}
		else
		{
			sign = true;
			size = 1;
			data = new char('0');
		}
	}
	MyBigInt(const MyBigInt& copied) :
		size(copied.size),
		sign(copied.sign),
		data(new char[size])
	{
		for (size_t i = 0; i<size; ++i)
		{
			data[i] = copied.data[i];
		}
	}
	MyBigInt& operator=(const MyBigInt& copied)
	{
		size = copied.size;
		sign = copied.sign;
		if (data) delete[] data;
		data = new char[size];
		for (size_t i = 0; i < size; ++i)
		{
			data[i] = copied.data[i];
		}
		return *this;
	}
	MyBigInt(MyBigInt&& moved):
		size(std::move(moved.size)),
		sign(std::move(moved.sign)),
		data(std::move(moved.data))
	{
		moved.data = nullptr;
		moved.size = 0;
	}
	MyBigInt& operator=(MyBigInt&& moved)
	{
		
		if (this == &moved)
			return *this;
		size = std::move(moved.size);
		sign = std::move(moved.sign);
		if (data) delete[] data;
		data = std::move(moved.data);
		moved.data = nullptr;
		moved.size = 0;
		return *this;
	}
	~MyBigInt()
	{
		if (data) delete[] data;
		data = nullptr;
		size = 0;
	}

	//print
	friend std::ostream& operator<<(std::ostream& out, const MyBigInt& printed)
	{
		if (!printed.sign) out << '-';
		for (int i = printed.size-1; i >= 0; --i)
			out << printed.data[i];
		return out;
	}
	//scan
	friend std::istream& operator >> (std::istream& in, MyBigInt& NewBigInt)
	{
		delete[] NewBigInt.data;
		std::string tmp;
		in >> tmp;
		NewBigInt.size = tmp.length();
		if (tmp.length() > 0 && tmp[0] == '-')
		{
			NewBigInt.sign = false;
			--NewBigInt.size;
			NewBigInt.data = new char[NewBigInt.size];
			for (int i = 0; i < NewBigInt.size; ++i)
			{
				if(tmp[NewBigInt.size - i] >= '0' && tmp[NewBigInt.size - i] <='9')
				NewBigInt.data[i] = tmp[NewBigInt.size - i];
				else
				{
					delete[] NewBigInt.data;
					NewBigInt.data = nullptr;
					NewBigInt.size = 0;
					break;
				}
			}
		}
		else if (tmp.length() > 0)
		{
			NewBigInt.sign = true;
			NewBigInt.data = new char[NewBigInt.size];
			for (int i = 0; i < NewBigInt.size; ++i)
			{
				if (tmp[NewBigInt.size -1- i] >= '0' && tmp[NewBigInt.size -1 - i] <= '9')
					NewBigInt.data[i] = tmp[NewBigInt.size - 1 - i];
				else
				{
					delete[] NewBigInt.data;
					NewBigInt.data = nullptr;
					NewBigInt.size = 0;
					break;
				}
			}
		}
		return in;
	}
	//unar -
	friend MyBigInt const operator-(const MyBigInt& self)
	{
		MyBigInt tmp(self);
		if (tmp.data[tmp.size-1] != '0') tmp.sign = !tmp.sign;
		return tmp;
	}
	//+
	const MyBigInt operator+(const MyBigInt& second) const;
	const MyBigInt operator+(const int& second) const;
	friend const MyBigInt operator+(const int& x, const MyBigInt& y)
	{
		MyBigInt _x(x);
		return _x + y;
	}
	//-
	const MyBigInt operator-(const MyBigInt& second) const;
	const MyBigInt operator-(const int& second) const;
	friend const MyBigInt operator-(const int& x, const MyBigInt& y)
	{
		MyBigInt _x(x);
		return _x - y;
	}
	//==
	const bool operator==(const MyBigInt& second) const;
	const bool operator==(const int& second) const;
	friend const bool operator==(const int& x, const MyBigInt& y)
	{
		MyBigInt _x(x);
		return (_x == y);
	}
	//!=
	const bool operator!=(const MyBigInt& second) const;
	const bool operator!=(const int& second) const;
	friend const bool operator!=(const int& x, const MyBigInt& y)
	{
		return !(x == y);
	}
	//<
	const bool operator<(const MyBigInt& second) const;
	const bool operator<(const int& second) const;
	friend const bool operator<(const int& x, const MyBigInt& y)
	{
		MyBigInt _x(x);
		return (_x < y);
	}
	//<=
	const bool operator<=(const MyBigInt& second) const;
	const bool operator<=(const int& second) const;
	friend const bool operator<=(const int& x, const MyBigInt& y)
	{
		MyBigInt _x(x);
		return (_x <= y);
	}
	//>
	const bool operator>(const MyBigInt& second) const;
	const bool operator>(const int& second) const;
	friend const bool operator>(const int& x, const MyBigInt& y)
	{
		return !(x <= y);
	}
	//>=
	const bool operator>=(const MyBigInt& second) const;
	const bool operator>=(const int& second) const;
	friend const bool operator>=(const int& x, const MyBigInt& y)
	{
		return !(x < y);
	}

private:
	size_t size;
	bool sign;
	char* data;

	MyBigInt(const size_t _size,const bool _sign, const int& len, const char* _data ) :
		size(_size),
		sign(_sign),
		data(new char[_size])
	{
		for (size_t i = 0; i < len && i<_size; ++i)
		{
			data[i] = _data[i];
		}
		for (size_t i = len; i < _size; ++i)
		{
			data[i] = '0';
		}
	}
};
/*
CC=g++

all: test

test: test.o MyBigInt.o
	$(CC) -o test test.o MyBigInt.o
	./test

MyBigInt.o: MyBigInt.cpp
	$(CC) -c MyBigInt.cpp

test.o: test.cpp MyBigInt.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
*/