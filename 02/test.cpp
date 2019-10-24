#include "Myallocator.cpp"
#include <cassert>

int main() {
    LinearAllocator q(100);

	char *a1 = q.alloc(10);
	assert(a1 != nullptr);

	char *a2 = q.alloc(20);
	assert(a2 != nullptr);
	assert(a2 - a1 == 20);

	a2[0] = 'c';
	assert(a2[0] == 'c');

	q.reset();

	char *a3 = q.alloc(10);
	assert(a3 != nullptr);

	char *a4 = q.alloc(20);
	assert(a4 != nullptr);
	assert(a4 - a3 == 20);

	a3[0] = 'c';
	assert(a3[0] == 'c');


	char *a5 = q.alloc(70);
	assert(a5 != nullptr);

	q.reset();

	char *a6 = q.alloc(1000000);
	assert(a6 == nullptr);

	LinearAllocator q2(1000000000000000000);
	char* a7 = q2.alloc(1);
	assert(a7 == nullptr);

	std::cout << "Success!" << std::endl;
	return 0;

}
