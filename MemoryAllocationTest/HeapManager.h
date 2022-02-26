#pragma once
#include "Heap.h"
#include <vector>
#include <unordered_map>

class Heap;

class HeapManager
{
public:
	void InitManager();
	static Heap* CreateHeap(std::string name, std::string parent);
	static void ClearHeaps();
	static void Debug();
public:
	//getters
	static Heap& GetDefaultHeap();
	static Heap* GetHeap(std::string name) { return heaps[name]; };

private:
	static std::unordered_map<std::string, Heap*> heaps;
	static Heap defaultHeap;
	static Heap* rootHeap;
};