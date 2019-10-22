#include <iostream>

class LinearAllocator
{
public:
	LinearAllocator();
	LinearAllocator(size_t maxSize);
	//~LinearAllocator();
	char* alloc(size_t size);
	void reset();

	//void prin();

private:
	char* myBuffer;
	size_t totalSize;
};
/*
void LinearAllocator::prin() {

	for (int i = 0; i < totalSize; i++)
		std::cout << myBuffer[i] << " ";
	std::cout << std::endl;
};
*/
LinearAllocator::LinearAllocator() :
	myBuffer(new char[8]),
	totalSize(8)
{	
}
LinearAllocator::LinearAllocator(size_t maxSize):
	myBuffer(new char[maxSize]),
	totalSize(maxSize)
{
}
/*
LinearAllocator::~LinearAllocator()
{
	delete[] myBuffer;
	//free(myBuffer);
}
*/
char* LinearAllocator::alloc(size_t size)
{
	if (size)
	{
		if (size <= totalSize)
			return myBuffer;
		else
			return nullptr; 
	} 
	else
		return myBuffer;
}

void LinearAllocator::reset()
{
	delete[] myBuffer;
	
	//free(myBuffer);

	myBuffer = new char[totalSize];

}

int main() {
	/*
	size_t n = 10;
	LinearAllocator q(n);
	char* c = q.alloc(n);
	c[0]= '1';
	c[4] = '5';
	for (int i = 0;i<n;i++)
		std::cout << c[i] << " ";
	std::cout << std::endl;

	q.prin();
	q.reset();
	std::cout << c[0] << std::endl;

	q.prin();
	char*p = q.alloc(n);
	p[0] = '1';
	p[2] = 'o';
	p[4] = '5';
	for (int i = 0; i < n; i++)
		std::cout << c[i] << " ";
	std::cout << std::endl;


	q.prin();
	q.reset();
	*/
	//q.~LinearAllocator();
	//system("pause");
	return 0;
}
