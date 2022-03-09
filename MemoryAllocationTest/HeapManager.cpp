#include "HeapManager.h"

Heap HeapManager::defaultHeap = Heap("Default");
Heap* HeapManager::rootHeap = new Heap("Root");
std::unordered_map<std::string, Heap*> HeapManager::heaps;

void HeapManager::InitManager()
{
	heaps.insert(std::make_pair("Default", &defaultHeap));
	heaps.insert(std::make_pair("Root", rootHeap));
	defaultHeap.SetParent(rootHeap);
}

Heap* HeapManager::CreateHeap(std::string name, std::string parent)
{
	Heap* pParent = heaps[parent];

	if (pParent == NULL)
	{
		pParent = new Heap(parent);
		pParent->SetParent(rootHeap);
	}

	//create heap
	Heap* heap = new Heap(name);
	//Inserts heap
	heaps.insert(std::make_pair(name, heap));

	//Attach the new heap to the parent
	heap->SetParent(pParent);

	return heap;
}

void HeapManager::ClearHeaps()
{
	heaps.clear();
}

Heap& HeapManager::GetDefaultHeap()
{
	return defaultHeap;
}

void HeapManager::Debug()
{
	for (auto i = heaps.begin(); i != heaps.end(); i++) {
		//(*i)->HeapWalk();
	}

	defaultHeap.HeapWalk();
}
