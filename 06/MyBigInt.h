#pragma once
#include <iostream>
#include <string>

class MyBigInt
{
public:
	MyBigInt();
	MyBigInt(const int& _data);
	MyBigInt(const MyBigInt& copied);
	MyBigInt& operator=(const MyBigInt& copied);
	MyBigInt(MyBigInt&& moved);
	MyBigInt& operator=(MyBigInt&& moved);
	~MyBigInt();

	//print
	friend std::ostream& operator<<(std::ostream& out, const MyBigInt& printed);
	//scan
	friend std::istream& operator >> (std::istream& in, MyBigInt& NewBigInt);
	//unar -
	MyBigInt const operator-() const;
	//+
	const MyBigInt operator+(const MyBigInt& second) const;
	const MyBigInt operator+(const int& second) const;
	friend const MyBigInt operator+(const int& x, const MyBigInt& y);
	//-
	const MyBigInt operator-(const MyBigInt& second) const;
	const MyBigInt operator-(const int& second) const;
	friend const MyBigInt operator-(const int& x, const MyBigInt& y);
	//==
	const bool operator==(const MyBigInt& second) const;
	const bool operator==(const int& second) const;
	friend const bool operator==(const int& x, const MyBigInt& y);
	//!=
	const bool operator!=(const MyBigInt& second) const;
	const bool operator!=(const int& second) const;
	friend const bool operator!=(const int& x, const MyBigInt& y);
	//<
	const bool operator<(const MyBigInt& second) const;
	const bool operator<(const int& second) const;
	friend const bool operator<(const int& x, const MyBigInt& y);
	//<=
	const bool operator<=(const MyBigInt& second) const;
	const bool operator<=(const int& second) const;
	friend const bool operator<=(const int& x, const MyBigInt& y);
	//>
	const bool operator>(const MyBigInt& second) const;
	const bool operator>(const int& second) const;
	friend const bool operator>(const int& x, const MyBigInt& y);
	//>=
	const bool operator>=(const MyBigInt& second) const;
	const bool operator>=(const int& second) const;
	friend const bool operator>=(const int& x, const MyBigInt& y);

private:
	size_t size;
	bool sign;
	char* data;

	MyBigInt(const size_t _size, const bool _sign, const int& len, const char* _data);
};
