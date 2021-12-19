#include "Heap.h"
#include <iostream>

using namespace std;

static const size_t maxHeapSize = (10 * 1024);
static char heapMemory[maxHeapSize];
static char heapObject[sizeof(Heap)];

Heap::Heap()
{
	ClearHeapMemory();

	//setup heap memory info
	heapMemInfo = reinterpret_cast<MemoryInfo*>(&heapMemory[0]);
	heapMemInfo->nextMemBlock = nullptr;
	heapMemInfo->size = maxHeapSize;
	heapMemInfo->isFree = true;

	endOfHeap = &heapMemory[maxHeapSize - 1];

	cout << "Heap Initialisation Complete!" << endl;
}

Heap::~Heap()
{
	ClearHeapMemory();
	cout << "Heap Memory Cleared!" << endl;
}

void Heap::ClearHeapMemory()
{
	for (auto& byte : heapMemory)
		byte = static_cast<char>(0); //set all bytes to 0/null

	return;
}

void* Heap::AddBytesAllocated(size_t bytes)
{
	char* memory = nullptr;
	MemoryInfo* blockInfo = heapMemInfo;

	//check if block is free and big enough
	do
	{
		if ( (blockInfo->isFree == true) && (blockInfo->size >= bytes))
		{
			//allocate block of memory
			memory = reinterpret_cast<char*>(blockInfo + 1);

			//disble access to block and update its size
			blockInfo->size = bytes;
			blockInfo->isFree = false;

			//update blockInfo next
			if (blockInfo->nextMemBlock != nullptr)
			{
				MemoryInfo* tempNext = reinterpret_cast<MemoryInfo*>(blockInfo->nextMemBlock);

				//check space to house next block
				size_t remSize = size_t(((size_t)tempNext) - ((size_t)(memory + bytes)) + ((size_t)1));

				if (remSize > sizeof(MemoryInfo))
				{
					MemoryInfo* tempNew = reinterpret_cast<MemoryInfo*>(memory + bytes);
					tempNew->nextMemBlock = tempNext;
					tempNew->isFree = true;
					tempNew->size = remSize - sizeof(MemoryInfo);
					blockInfo->nextMemBlock = tempNew;
				}
			}
			else if (size_t(memory) + bytes < size_t(endOfHeap))
			{
				size_t remSize = size_t(endOfHeap) - (size_t(memory) + bytes) + ((size_t)1);

				if (remSize > sizeof(MemoryInfo))
				{
					MemoryInfo* tempNew = reinterpret_cast<MemoryInfo*>(memory + bytes);
					tempNew->nextMemBlock = nullptr;
					tempNew->isFree = true;
					tempNew->size = remSize - sizeof(MemoryInfo);
					blockInfo->nextMemBlock = tempNew;
				}
			}
			break;
		}

		blockInfo = blockInfo->nextMemBlock;

	} while (blockInfo != nullptr);

	return reinterpret_cast<void*>(memory);
}

bool Heap::RemoveBytesAllocated(void* memBlock)
{
	char* memory = reinterpret_cast<char*>(memBlock); //get start of memory block to deallocate
	bool state = false;

	if ( (unsigned int)memory < (unsigned int)heapMemory)
		return state;

	MemoryInfo* blockInfo = heapMemInfo;
	MemoryInfo* requiredBlock = reinterpret_cast<MemoryInfo*>(memory) - 1;

	do
	{
		if (blockInfo == requiredBlock) //if blockInfo is the block required to be deallocated
		{
			blockInfo->isFree = true;

			for (int ch = 0; ch < blockInfo->size; ++ch)
				memory = (char*)char(0); //set memory bit to 0 (deallocate)

			state = true;
			break;
		}

		blockInfo = blockInfo->nextMemBlock; //move to next block
	} while (blockInfo != nullptr);

	return state;
}

void Heap::ExecHeapDump()
{
	cout << "Heap Dump Executed!" << endl;
	int i = 0;

	for (auto byte : heapMemory)
		cout << "Byte " << dec << i++ << " : " << hex << "0x" << (0xFF & (unsigned int)byte) << endl; // dec/hex change base for integer
}

void* Heap::operator new (size_t size)
{
	return reinterpret_cast<void*>(heapObject);
}

Heap* Heap::GetHeapInstance(void)
{
	static bool isInitiated = false;
	static Heap* heap = nullptr;

	if (isInitiated == false)
	{
		heap = new Heap();
		isInitiated = !isInitiated;
	}

	return heap;
}
