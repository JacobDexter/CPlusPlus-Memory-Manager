#pragma once
#include "Heap.h"
#include <vector>

static class HeapManager
{
public:
	static void Initialize() { Heap* defHeap{}; defHeap->AddBytesAllocated(1000); heaps.push_back(defHeap); };
	static Heap* GetDefaultHeap() { return heaps.front(); };
	static void CreateHeap(size_t bytes) { Heap* heap{}; heap->AddBytesAllocated(bytes); heaps.push_back(heap); };
private:
	static std::vector<Heap*> heaps;
};