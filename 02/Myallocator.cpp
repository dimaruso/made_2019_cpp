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
	size_t currentSize;
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
	totalSize(8),
	currentSize(0)
{	
}
LinearAllocator::LinearAllocator(size_t maxSize):
	myBuffer(new char[maxSize]),
	totalSize(maxSize),
	currentSize(0)
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
		if (currentSize+size <= totalSize)
		{
			currentSize += size;
			return myBuffer+currentSize;
		}
		else
			return nullptr; 
	} 
	else
		return myBuffer;
}

void LinearAllocator::reset()
{
	//delete[] myBuffer;
	
	free(myBuffer);

	//myBuffer = new char[totalSize];

}

