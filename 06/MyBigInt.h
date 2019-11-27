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
	struct Buffer
	{
		explicit Buffer(size_t size) :
			data_(new char[size])
		{
			if (!size) data_ = nullptr;
		}
		Buffer() :
			data_(nullptr)
		{
		}
		void copy(char* copied)
		{
			if (data_)
				delete[] data_;
			data_ = copied;
		}
		~Buffer()
		{
			if (data_)
				delete[] data_;
			data_ = nullptr;
		}
		char& operator[](const size_t& i)
		{
			return data_[i];
		}
		const char& operator[](const size_t& i) const
		{
			return data_[i];
		}
		void resize(size_t size)
		{
			if (data_)
				delete[] data_;
			if (!size) data_ = nullptr;
			else
				data_ = new char[size];
		}
		void lock()
		{
			data_ = nullptr;
		}
		char* data_;
	};
	Buffer data;
	MyBigInt(const size_t& _size, const bool _sign, const size_t& len, const Buffer& _data);
};
