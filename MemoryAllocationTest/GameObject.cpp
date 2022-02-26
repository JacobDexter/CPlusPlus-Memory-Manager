#include "GameObject.h"

GameObject::GameObject(std::string name) : _name(name)
{
	std::cout << "[Log] " << _name << " constructor called." << std::endl;
}

GameObject::~GameObject()
{
	std::cout << "[Log] " << _name << " destructor called." << std::endl;
}

void* GameObject::operator new(size_t size)
{
	std::cout << "[Log] GameObject new override called" << std::endl << std::endl;

	return ::operator new (size);
}

void GameObject::operator delete(void* pMem)
{
	::operator delete (pMem);

	std::cout << "[Log] GameObject delete override called" << std::endl << std::endl;
}
