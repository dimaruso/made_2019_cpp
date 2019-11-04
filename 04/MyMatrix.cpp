#include <iostream>
#include "MyMatrix.h"

MyMatrix::MyMatrix(size_t _rows, size_t _cols):
	rows(_rows),
	cols(_cols)
{
	for (size_t i = 0; i < rows; ++i)
		Data.push_back(Row(cols));
}

MyMatrix::~MyMatrix()
{
}

const size_t MyMatrix::getRows() const
{
	return rows;
}
const size_t MyMatrix::getColumns() const
{
	return cols;
}

const MyMatrix::Row& MyMatrix::operator[](size_t i) const
{
	if (i < rows && Data.size() != 0) return Data[i];
	else
		throw std::out_of_range("wrong row index");
}
MyMatrix::Row& MyMatrix::operator[](size_t i)
{
	if (i < rows && Data.size() != 0) return Data[i];
	else
		throw std::out_of_range("wrong row index");
}

bool MyMatrix::operator==(const MyMatrix& other) const
{
	if (this == &other)
		return true;
	if (cols != other.cols || rows != other.rows)
		return false;
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
			if (Data[i][j] != other[i][j])
			return false;
	return true;
}

bool MyMatrix::operator!=(const MyMatrix& other) const
{
	return !(*this == other);
}

MyMatrix& MyMatrix::operator=(const MyMatrix& m)
{
	if (this == &m) return *this;

	if (!((this)->rows == m.getRows() && (this)->cols == m.getColumns()))
	{
		if(Data.size() != 0) Data.clear();
		rows = m.getRows();
		cols = m.getColumns();
		for (int i = 0; i < rows; ++i)
			Data.push_back(Row(cols));
	} 
	else
	{
		rows = m.getRows();
		cols = m.getColumns();
	}
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
			Data[i][j] = m[i][j];

	return *this;
}

MyMatrix MyMatrix::operator*(const int k) const
{
	MyMatrix self = *this;
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)

		self[i][j] = Data[i][j]*k;
	return self;
}

MyMatrix MyMatrix::operator*=(const int k)
{
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
			Data[i][j] *= k;
	return *this;
}
