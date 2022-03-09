#pragma once
struct Chunk 
{
	Chunk* next = nullptr;
};

class MemoryPool
{
public:
	MemoryPool(size_t chunkLimit) : mChunkLimit(chunkLimit), pRootChunk(nullptr) { };
	~MemoryPool() { };
public:
	void* AllocateMemory(size_t size);
	void Free(void* mem);
private:
	Chunk* pRootChunk;
	size_t mChunkLimit;
};