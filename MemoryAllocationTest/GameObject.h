#pragma once
#include <iostream>
#include "Heap.h"
using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();
public:
	void* operator new (size_t size);
	void operator delete (void* pMem, size_t size);
private:
	static Heap* heap;
};

Heap* GameObject::heap = NULL;
