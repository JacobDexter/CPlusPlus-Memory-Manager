#pragma once
#include <iostream>
#include "HeapManager.h"

struct Header
{
	Heap* heap;
	int size;
};

struct Footer
{
	int reserved;
};

void* operator new (size_t size, Heap* heap);
void operator delete (void* pMem);