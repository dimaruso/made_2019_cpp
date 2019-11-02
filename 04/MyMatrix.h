#pragma once
class MyMatrix
{
public:
	MyMatrix(size_t _rows, size_t _cols);
	~MyMatrix();

	const size_t getRows() const;
	const size_t getColumns() const;

	const int* operator[](size_t i) const;
	int* operator[](size_t i);

	bool operator==(const MyMatrix& other) const;
	bool operator!=(const MyMatrix& other) const;

	MyMatrix& operator=(const MyMatrix& m);

	MyMatrix operator*(const int k) const;
	MyMatrix operator*=(const int k) const;

private:
	size_t rows;
	size_t cols;
	int* data;
};