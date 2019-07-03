#include <Windows.h>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

class MyAllocator
{
public:
	void * allocate(size_t size)
	{
		size_t allocate_size = size + sizeof(size_t);
		void * p = VirtualAlloc(nullptr, allocate_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		if(p == nullptr)
		{
			return nullptr;
		}

		*reinterpret_cast<size_t *>(p) = allocate_size;

		mUsed += allocate_size;
		mMaxUsed = max(mMaxUsed, mUsed);

		return reinterpret_cast<uint8_t *>(p) + sizeof(size_t);
	}

	void deallocate(void * p)
	{
		void * ptr = reinterpret_cast<uint8_t *>(p) - sizeof(size_t);
		size_t allocated_size = *reinterpret_cast<size_t *>(ptr);

		VirtualFree(ptr, 0, MEM_RELEASE);

		mUsed -= allocated_size;
	}

	void dump()
	{
		cout << "Used    : " << mUsed << endl;
		cout << "Max Used: " << mMaxUsed << endl;
	}

private:
	size_t mUsed = 0;
	size_t mMaxUsed = 0;
};

MyAllocator my_allocator;

void * my_alloc(size_t size)
{
	return my_allocator.allocate(size);
}

void my_free(void * p)
{
	my_allocator.deallocate(p);
}

int main()
{
	vector<void *> allocated;

	for(int i = 0; i < 256; ++i)
	{
		allocated.push_back(my_alloc(i));
		my_allocator.dump();
	}

	for(auto p : allocated)
	{
		my_free(p);
		my_allocator.dump();
	}
}
