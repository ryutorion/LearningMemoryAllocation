#include <Windows.h>
#include <iostream>

using namespace std;

void * my_alloc(size_t size)
{
	void * p = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	cerr << "Allocate " << size << " at " << p << endl;

	return p;
}

void my_free(void * p)
{
	cerr << "Deallocate " << p << endl;

	VirtualFree(p, 0, MEM_RELEASE);

}

int main()
{
	size_t size = 1;
	for(int i = 0; i < 32; ++i, size <<= 1)
	{
		void * p = my_alloc(size);
		my_free(p);
	}
}
