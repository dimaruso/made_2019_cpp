#include "MyBigInt.h"

MyBigInt::MyBigInt(const size_t _size, const bool _sign, const int& len, const char* _data) :
	size(_size),
	sign(_sign),
	data(new char[_size])
{
	for (size_t i = 0; i < len && i < _size; ++i)
	{
		data[i] = _data[i];
	}
	for (size_t i = len; i < _size; ++i)
	{
		data[i] = '0';
	}
}

MyBigInt::MyBigInt() :
	size(1),
	sign(true),
	data(new char[1]{ '0' })
{
}

MyBigInt::MyBigInt(const int& _data)
{
	if (_data > 0)
	{
		std::string tmp = std::to_string(_data);
		size = tmp.length();
		data = new char[size];
		for (size_t i = 0; i < size; ++i)
		{
			data[i] = tmp[size - 1 - i];
		}
		sign = true;
	}
	else if (_data < 0)
	{
		std::string tmp = std::to_string(-_data);
		size = tmp.length();
		data = new char[size];
		for (size_t i = 0; i < size; ++i)
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

MyBigInt::MyBigInt(const MyBigInt& copied) :
	size(copied.size),
	sign(copied.sign),
	data(new char[size])
{
	for (size_t i = 0; i < size; ++i)
	{
		data[i] = copied.data[i];
	}
}

MyBigInt& MyBigInt::operator=(const MyBigInt& copied)
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

MyBigInt::MyBigInt(MyBigInt&& moved) :
	size(moved.size),
	sign(moved.sign),
	data(moved.data)
{
	moved.data = nullptr;
	moved.size = 0;
}

MyBigInt& MyBigInt::operator=(MyBigInt&& moved)
{

	if (this == &moved)
		return *this;
	size = moved.size;
	sign = moved.sign;
	if (data) delete[] data;
	data = moved.data;
	moved.data = nullptr;
	moved.size = 0;
	return *this;
}

MyBigInt::~MyBigInt()
{
	if (data) delete[] data;
	data = nullptr;
	size = 0;
}

//print
std::ostream& operator<<(std::ostream& out, const MyBigInt& printed)
{
	if (printed.data && printed.size)
	{
		if (!printed.sign) out << '-';
		for (size_t i = printed.size - 1; i > 0; --i)
			out << printed.data[i];
		out << printed.data[0];
	}
	return out;
}
//scan
std::istream& operator >> (std::istream& in, MyBigInt& NewBigInt)
{
	if(NewBigInt.data) delete[] NewBigInt.data;
	NewBigInt.data = nullptr;
	std::string tmp;
	in >> tmp;
	NewBigInt.size = tmp.length();
	if (tmp.length() > 0 && tmp[0] == '-')
	{
		NewBigInt.sign = false;
		--NewBigInt.size;
		NewBigInt.data = new char[NewBigInt.size];	
		for (size_t i = 0; i < NewBigInt.size; ++i)
		{
			if (tmp[NewBigInt.size - i] >= '0' && tmp[NewBigInt.size - i] <= '9')
				NewBigInt.data[i] = tmp[NewBigInt.size - i];
			else
			{
				if (NewBigInt.data) delete[] NewBigInt.data;
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
		for (size_t i = 0; i < NewBigInt.size; ++i)
		{
			if (tmp[NewBigInt.size - 1 - i] >= '0' && tmp[NewBigInt.size - 1 - i] <= '9')
				NewBigInt.data[i] = tmp[NewBigInt.size - 1 - i];
			else
			{
				if (NewBigInt.data) delete[] NewBigInt.data;
				NewBigInt.data = nullptr;
				NewBigInt.size = 0;
				break;
			}
		}
	}
	else
	{
		if (NewBigInt.data) delete[] NewBigInt.data;
		NewBigInt.data = nullptr;
		NewBigInt.size = 0;
	}
	return in;
}
//unar -
MyBigInt const MyBigInt::operator-() const
{
	MyBigInt tmp(*this);
	if (tmp.data[tmp.size - 1] != '0') tmp.sign = !tmp.sign;
	return tmp;
}
//////////////////////////////////////////////////
//+
const MyBigInt MyBigInt::operator+(const MyBigInt& second) const
{
	int k = 0;
	if (size > second.size)
	{
		if (sign == second.sign)
		{
			//this + second
			MyBigInt tmp(size + 1, sign, size, data);
			size_t i = 0;
			for (; i < second.size; ++i)
			{
				k = (data[i] - 48) + (second.data[i] - 48) + k;
				tmp.data[i] = (k % 10) + 48;
				k /= 10;
			}
			if (k) tmp.data[i] += k;
			else
			{
				char* newdata = new char[tmp.size-1];
				for (i = 0; i < tmp.size-1; ++i)
					newdata[i] = tmp.data[i];
				delete[] tmp.data;
				tmp.data = newdata;
				--tmp.size;
			}
			return tmp;
		}
		else
		{
			// this - second
			MyBigInt tmp(*this);
			size_t i = 0;
			for (; i < second.size; ++i)
			{
				k = (data[i] - '0') - (second.data[i] - '0') + k;
				if (k < 0)
				{
					tmp.data[i] = '0' + 10 + k;
					k = -1;
				}
				else
				{
					tmp.data[i] = '0' + k;
					k = 0;
				}
			}

			for (; i < size && k<0; ++i)
			{
				k = (data[i] - '0') + k;
				if (k < 0)
				{
					tmp.data[i] = '0' + 10 + k;
					k = -1;
				}
				else
				{
					tmp.data[i] = '0' + k;
					k = 0;
				}
			}
			if (i == size)//delete 0
			{
				size_t j;
				for (j = size - 1; j > 0 && tmp.data[j] == '0'; --j);

				tmp.size = j + 1;
				char* newdata = new char[tmp.size];
				for (i = 0; i < tmp.size; ++i)
					newdata[i] = tmp.data[i];

				delete[] tmp.data;
				tmp.data = newdata;
			}
			if (tmp.size == 1 && tmp.data[0] == '0')
				tmp.sign = true;
			return tmp;
		}
	}
	else///////////////////////////////////////////
	{
		if (sign == second.sign)
		{
			//second + this
			MyBigInt tmp(second.size + 1, second.sign, second.size, second.data);
			size_t i = 0;
			for (; i < size; ++i)
			{
				k = (data[i] - 48) + (second.data[i] - 48) + k;
				tmp.data[i] = (k % 10) + 48;
				k /= 10;
			}
			if (k) tmp.data[i] += k;
			else
			{
				char* newdata = new char[tmp.size-1];
				for (i = 0; i < tmp.size-1; ++i)
					newdata[i] = tmp.data[i];
				delete[] tmp.data;
				tmp.data = newdata;
				--tmp.size;
			}
			return tmp;

		}
		else
		{
			//second - this
			if ((second.sign &&second > -*this)|| (sign && -second > *this))
			{
				MyBigInt tmp(second);
				size_t i = 0;
				for (; i < size; ++i)
				{
					k = -(data[i] - '0') + (second.data[i] - '0') + k;
					if (k < 0)
					{
						tmp.data[i] = '0' + 10 + k;
						k = -1;
					}
					else
					{
						tmp.data[i] = '0' + k;
						k = 0;
					}
				}
				for (; i < second.size && k < 0; ++i)
				{
					k = (second.data[i] - '0') + k;
					if (k < 0)
					{
						tmp.data[i] = '0' + 10 + k;
						k = -1;
					}
					else
					{
						tmp.data[i] = '0' + k;
						k = 0;
					}
				}

				if (i == second.size)//delete 0
				{
					size_t j;
					for (j = second.size - 1; j > 0 && tmp.data[j] == '0'; --j);
					tmp.size = j + 1;

					char* newdata = new char[tmp.size];
					for (i = 0; i < tmp.size; ++i)
						newdata[i] = tmp.data[i];
					delete[] tmp.data;
					tmp.data = newdata;
				}
				if (tmp.size == 1 && tmp.data[0] == '0')
					tmp.sign = true;
				return tmp;
			}
			else
			{
				// this - second
				MyBigInt tmp(*this);
				size_t i = 0;
				for (; i < second.size; ++i)
				{
					k = (data[i] - '0') - (second.data[i] - '0') + k;
					if (k < 0)
					{
						tmp.data[i] = '0' + 10 + k;
						k = -1;
					}
					else
					{
						tmp.data[i] = '0' + k;
						k = 0;
					}
				}

				for (; i < size && k < 0; ++i)
				{
					k = (data[i] - '0') + k;
					if (k < 0)
					{
						tmp.data[i] = '0' + 10 + k;
						k = -1;
					}
					else
					{
						tmp.data[i] = '0' + k;
						k = 0;
					}
				}
				if (i == size)//delete 0
				{
					size_t j;
					for (j = size - 1; j > 0 && tmp.data[j] == '0'; --j);

					tmp.size = j + 1;
					char* newdata = new char[tmp.size];
					for (i = 0; i < tmp.size; ++i)
						newdata[i] = tmp.data[i];

					delete[] tmp.data;
					tmp.data = newdata;
				}
				if (tmp.size == 1 && tmp.data[0] == '0')
					tmp.sign = true;
				return tmp;
			}
		}
	}
	


}
const MyBigInt MyBigInt::operator+(const int& second) const
{
	MyBigInt tmp(second);
	return *this+tmp;
}
const MyBigInt operator+(const int& x, const MyBigInt& y)
{
	MyBigInt _x(x);
	return _x + y;
}
//-
const MyBigInt MyBigInt::operator-(const MyBigInt& second) const
{
	return *this+(-second);
}
const MyBigInt MyBigInt::operator-(const int& second) const
{
	MyBigInt tmp(-second);
	return *this+tmp;
}
const MyBigInt operator-(const int& x, const MyBigInt& y)
{
	MyBigInt _x(x);
	return _x - y;
}
//==
const bool MyBigInt::operator==(const MyBigInt& second) const
{
	if (this == &second)
		return true;
	if (size != second.size || sign != second.sign)
		return false;
	for (size_t i = 0; i < size; ++i)
			if (data[i] != second.data[i])
				return false;
	return true;
}
const bool MyBigInt::operator==(const int& second) const
{
	MyBigInt _second(second);
	return (*this == _second);
}
const bool operator==(const int& x, const MyBigInt& y)
{
	MyBigInt _x(x);
	return (_x == y);
}
//!=
const bool MyBigInt::operator!=(const MyBigInt& second) const
{
	return !(*this == second);
}
const bool MyBigInt::operator!=(const int& second) const
{
	return !(*this == second);
}
const bool operator!=(const int& x, const MyBigInt& y)
{
	return !(x == y);
}
//<
const bool MyBigInt::operator<(const MyBigInt& second) const
{
	if (sign != second.sign)
		return second.sign;
	if(sign)
	{
		if (size > second.size)
		{
			return false;
		}
		else if (size < second.size)
		{
			return true;
		}
		else
		{
			for (int i = size - 1; i >= 0; --i)
			{
				if (data[i] < second.data[i]) return true;
				if (data[i] > second.data[i]) return false;
			}
		}
	}
	else
	{
		if (size > second.size)
		{
			return true;
		}
		else if (size < second.size)
		{
			return false;
		}
		else
		{
			for (int i = size - 1; i >= 0; --i)
			{
				if (data[i] < second.data[i]) return false;
				if (data[i] > second.data[i]) return true;
			}
		}
	}
	//this == second
	return false;
}
const bool MyBigInt::operator<(const int& second) const
{
	MyBigInt _second(second);
	return (*this < _second);
}
const bool operator<(const int& x, const MyBigInt& y)
{
	MyBigInt _x(x);
	return (_x < y);
}
//<=
const bool MyBigInt::operator<=(const MyBigInt& second) const
{
	if (sign != second.sign)
		return second.sign;
	if (sign)
	{
		if (size > second.size)
		{
			return false;
		}
		else if (size < second.size)
		{
			return true;
		}
		else
		{
			for (int i = size - 1; i >= 0; --i)
			{
				if (data[i] < second.data[i]) return true;
				if (data[i] > second.data[i]) return false;
			}
		}
	}
	else
	{
		if (size > second.size)
		{
			return true;
		}
		else if (size < second.size)
		{
			return false;
		}
		else
		{
			for (int i = size - 1; i >= 0; --i)
			{
				if (data[i] < second.data[i]) return false;
				if (data[i] > second.data[i]) return true;
			}
		}
	}
	//this == second
	return true;
}
const bool MyBigInt::operator<=(const int& second) const
{
	MyBigInt _second(second);
	return (*this <= _second);
}
const bool operator<=(const int& x, const MyBigInt& y)
{
	MyBigInt _x(x);
	return (_x <= y);
}
//>
const bool MyBigInt::operator>(const MyBigInt& second) const
{
	return !(*this <= second);
}
const bool MyBigInt::operator>(const int& second) const
{
	return !(*this <= second);
}
const bool operator>(const int& x, const MyBigInt& y)
{
	return !(x <= y);
}
//>=
const bool MyBigInt::operator>=(const MyBigInt& second) const
{
	return !(*this < second);
}
const bool MyBigInt::operator>=(const int& second) const
{
	return !(*this < second);
}
const bool operator>=(const int& x, const MyBigInt& y)
{
	return !(x < y);
}
