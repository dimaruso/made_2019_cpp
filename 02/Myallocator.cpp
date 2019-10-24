#include <iostream>

class LinearAllocator
{
public:

	LinearAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();

private:
	char* myBuffer;
	size_t totalSize;
	size_t currentSize;
};

LinearAllocator::LinearAllocator(size_t maxSize) :
	myBuffer((char *)malloc(maxSize)),
	totalSize(maxSize),
	currentSize(0)
{
}

char* LinearAllocator::alloc(size_t size)
{
	if (myBuffer != nullptr)
	{
		if (size)
		{
			if (currentSize + size <= totalSize)
			{
				currentSize += size;
				return myBuffer + currentSize;
			}
			else
				return nullptr;
		}
		else
			return myBuffer;
	}
	else 
		return nullptr;
}

void LinearAllocator::reset()
{
	currentSize = 0;
}

