#pragma once

class Heap
{
private:
	struct MemoryInfo
	{
		struct MemoryInfo* nextMemBlock;
		size_t size;
		bool isFree;
	};

	MemoryInfo* heapMemInfo;
	char* endOfHeap;
private:
	Heap();
	static void* operator new (size_t size);
public:
	~Heap();
	void ClearHeapMemory();
	void* AddBytesAllocated(size_t bytes);
	bool RemoveBytesAllocated(void* memBlock);
	void ExecHeapDump();
	static Heap* GetHeapInstance(void);
};

