#include "GameObject.h"

GameObject::GameObject()
{
	cout << "Constructor Called." << endl;
}

GameObject::~GameObject()
{
	cout << "Destructor Called." << endl;
}

void* GameObject::operator new(size_t size)
{
	cout << "GameObject New Called" << endl;

	return ::operator new (size);
}

void GameObject::operator delete(void* pMem, size_t size)
{
	::operator delete (pMem);

	cout << "GameObject Delete Called" << endl;
}
