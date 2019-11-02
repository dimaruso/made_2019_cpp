#include <iostream>
#include "MyMatrix.h"

MyMatrix::MyMatrix(size_t _rows, size_t _cols):
	rows(_rows),
	cols(_cols),
	data(nullptr)
{
	if (rows*cols > 0)
		data = (int*)malloc(sizeof(int)*rows*cols);
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

const int* MyMatrix::operator[](size_t i) const
{
	if (i < cols * rows) return (data+(i*cols));
	else
		throw std::out_of_range("wrong index");
}
int* MyMatrix::operator[](size_t i)
{
	if (i < cols * rows) return(data + (i*cols));
	else
		throw std::out_of_range("wrong index");
}

bool MyMatrix::operator==(const MyMatrix& other) const
{
	if (this == &other)
		return true;
	if (cols != other.cols || rows != other.rows)
		return false;
	for (size_t i = 0; i < rows*cols; ++i)
		if (data[i] != other.data[i])
			return false;
	return true;
}

bool MyMatrix::operator!=(const MyMatrix& other) const
{
	if (this == &other)
		return false;
	if (cols != other.cols || rows != other.rows)
		return true;
	for (size_t i = 0; i < rows*cols; ++i)
		if (data[i] != other.data[i])
			return true;
	return false;
}

MyMatrix& MyMatrix::operator=(const MyMatrix& m)
{
	if (this == &m) return *this;

	if (!((this)->rows == m.getRows() && (this)->cols == m.getColumns()))
	{
		if(data != nullptr)	delete[] data;
		data = (int*)malloc(sizeof(int)*m.getRows()*m.getColumns());
	}
	rows = m.getRows();
	cols = m.getColumns();
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
			data[i*cols + j] = m[i][j];

	return *this;
}

MyMatrix MyMatrix::operator*(const int k) const
{
	MyMatrix self = *this;
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)

		self[i][j] = data[i*cols+j]*k;
	return self;
}

MyMatrix MyMatrix::operator*=(const int k) const
{
	MyMatrix self = *this;
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
			self[i][j] = data[i*cols + j] * k;
	return self;
}