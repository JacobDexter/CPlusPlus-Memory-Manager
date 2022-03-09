#include "MemoryPool.h"
#include <iostream>

void* MemoryPool::AllocateMemory(size_t size)
{
	if (pRootChunk == nullptr)
	{
		std::cout << "Allocating new block with " << mChunkLimit << " chunks." << std::endl;

		size_t bSize = mChunkLimit * size;
		Chunk* root = reinterpret_cast<Chunk*>(malloc(bSize));
		Chunk* chunk = root;

		for (int i = 0; i < mChunkLimit - 1; i++) {
			chunk->next = reinterpret_cast<Chunk*>(reinterpret_cast<char*>(chunk) + size);
			chunk = chunk->next;
		}

		chunk->next = nullptr;

		return root;
	}

	Chunk* freeChunk = pRootChunk;
	pRootChunk = pRootChunk->next;

	return freeChunk;
}

void MemoryPool::Free(void* mem)
{
	std::cout << "Deallocating block with " << mChunkLimit << " chunks." << std::endl;

	reinterpret_cast<Chunk*>(mem)->next = pRootChunk;
	pRootChunk = reinterpret_cast<Chunk*>(mem);
}
