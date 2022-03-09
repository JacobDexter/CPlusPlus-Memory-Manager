#pragma once
#include <iostream>
class Heap;
using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();
public:
	void* operator new (size_t size);
	void operator delete (void* pMem);
private:
	Heap* heap;
};

//Heap* GameObject::heap = NULL;
