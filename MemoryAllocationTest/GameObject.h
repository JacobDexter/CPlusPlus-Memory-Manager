#pragma once
#include <iostream>

class Heap;

class GameObject
{
public:
	GameObject(std::string name);
	~GameObject();

public:
	void* operator new (size_t size);
	void operator delete (void* pMem);
private:
	std::string _name;
};