#include <iostream>
#include <cassert>
#include "MyMatrix.h"

int main() {

	const size_t rows = 2;
	const size_t cols = 3;

	MyMatrix m(rows, cols);
	assert(m.getRows() == 2);
	assert(m.getColumns() == 3);

	m[0][0] = 0;
	m[0][1] = 1;
	m[0][2] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	m[1][2] = 5;

	assert(m[0][0] == 0);
	assert(m[1][0] == 3);
	assert(m[1][2] == 5);

	MyMatrix m2(0, 0);
	m2 = m;
	assert(m2[1][0] == 3);
	assert(m2 == m);

	m[1][0] *= 3;
	assert(m[1][0] == 9);
	assert(m2[1][0] == 3);
	
	m2[1][0] += 2;
	assert(m2[1][0] == 5);
	assert(m[1][0] == 9);

	assert(m2 != m);
	
	m =m * 10; 
	assert(m[1][0] == 90);
	
	m2 *= 2;
	assert(m2[1][0] == 10);

	std::cout << "Tests completed successfully!"<< std::endl;
	//system("pause");
	return 0;
}