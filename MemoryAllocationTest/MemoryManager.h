#pragma once
#include <iostream>
#include "HeapManager.h"

class Heap;

struct Header
{
	Heap* heap;
	int size;
	Header* previous = NULL;
	Header* next = NULL;
	int checkValue = 0xDEADC0DE;
};

struct Footer
{
	int reserved;

	int checkValue = 0xDEADC0DE;
};

void* operator new (size_t size, Heap* heap);
void operator delete (void* pMem);