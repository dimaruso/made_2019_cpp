#include "MyBigInt.h"

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
				tmp.data = std::move(newdata);
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
					tmp.data[i] = '0' + 10 + k;
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
					tmp.data[i] = '0' + 10 + k;
				else
				{
					tmp.data[i] = '0' + k;
					k = 0;
				}
			}
			if (i == size)//delete 0
			{
				int j;
				for (j = size - 1; j > 0 && tmp.data[j] == '0'; --j);

				tmp.size = j + 1;
				char* newdata = new char[tmp.size];
				for (i = 0; i < tmp.size; ++i)
					newdata[i] = tmp.data[i];

				delete[] tmp.data;
				tmp.data = std::move(newdata);
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
				tmp.data = std::move(newdata);
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
						tmp.data[i] = '0' + 10 + k;
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
						tmp.data[i] = '0' + 10 + k;
					else
					{
						tmp.data[i] = '0' + k;
						k = 0;
					}
				}

				if (i == second.size)//delete 0
				{
					int j;
					for (j = second.size - 1; j > 0 && tmp.data[j] == '0'; --j);
					tmp.size = j + 1;

					char* newdata = new char[tmp.size];
					for (i = 0; i < tmp.size; ++i)
						newdata[i] = tmp.data[i];
					delete[] tmp.data;
					tmp.data = std::move(newdata);
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
						tmp.data[i] = '0' + 10 + k;
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
						tmp.data[i] = '0' + 10 + k;
					else
					{
						tmp.data[i] = '0' + k;
						k = 0;
					}
				}
				if (i == size)//delete 0
				{
					int j;
					for (j = size - 1; j > 0 && tmp.data[j] == '0'; --j);

					tmp.size = j + 1;
					char* newdata = new char[tmp.size];
					for (i = 0; i < tmp.size; ++i)
						newdata[i] = tmp.data[i];

					delete[] tmp.data;
					tmp.data = std::move(newdata);
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

const MyBigInt MyBigInt::operator-(const MyBigInt& second) const
{
	return *this+(-second);
}
const MyBigInt MyBigInt::operator-(const int& second) const
{
	MyBigInt tmp(-second);
	return *this+tmp;
}

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

const bool MyBigInt::operator!=(const MyBigInt& second) const
{
	return !(*this == second);
}
const bool MyBigInt::operator!=(const int& second) const
{
	return !(*this == second);
}

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

const bool MyBigInt::operator>(const MyBigInt& second) const
{
	return !(*this <= second);
}
const bool MyBigInt::operator>(const int& second) const
{
	return !(*this <= second);
}

const bool MyBigInt::operator>=(const MyBigInt& second) const
{
	return !(*this < second);
}
const bool MyBigInt::operator>=(const int& second) const
{
	return !(*this < second);
}