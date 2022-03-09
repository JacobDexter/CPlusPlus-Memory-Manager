#include "GameObject.h"

GameObject::GameObject()
{
	cout << "[Log] GameObject constructor called." << endl;
}

GameObject::~GameObject()
{
	cout << "[Log] GameObject destructor called." << endl;
}

void* GameObject::operator new(size_t size)
{
	cout << "[Log] GameObject new override called" << endl;

	return ::operator new (size);
}

void GameObject::operator delete(void* pMem)
{
	::operator delete (pMem);

	cout << "[Log] GameObject delete override called" << endl;
}
