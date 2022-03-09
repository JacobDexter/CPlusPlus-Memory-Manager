#include "Heap.h"
#include <iostream>
#include <cassert>

using namespace std;

Heap::Heap(std::string name) : _bytesAllocated(0), _name(name)
{

}

Heap::~Heap()
{
	
}

void Heap::SetParent(Heap* parent)
{
	//ensure parent isn't null
	assert(parent != NULL);

	if (parent == _parent)
		return;

	this->_child = parent->_child;
	_parent = parent;
	parent->_child = this;
}

void Heap::AddBytesAllocated(size_t bytes, Header* header)
{
	_bytesAllocated += bytes;
	header->checkValue = 0xDEADC0DE;
	header->size = bytes;
	header->previous = NULL;
	header->next = _head;

	if (_head != NULL)
		_head->previous = header;

	_head = header;
}

void Heap::RemoveBytesAllocated(size_t bytes, Header* header)
{
	_bytesAllocated -= bytes;

	if (_head == header)
		_head = header->next;

	if (header->next != NULL)
		header->next->previous = header->previous;

	if (header->previous != NULL)
		header->previous->next = header->next;
}

void Heap::HeapWalk()
{
	if (_head != NULL)
	{
		//header size
		size_t size = sizeof(Header);
		Header* currentHeader = _head;

		cout << "Heap walk for: " << _name << endl;

		while (currentHeader != NULL)
		{
			if (currentHeader == NULL) //double check header
				break;

			auto& startMem = *(currentHeader + size);

			cout << &startMem << "\t" << typeid(startMem).name() << "\t" << currentHeader->size << endl;

			if (currentHeader->next == NULL) {
				break;
			}

			//next list element
			currentHeader = currentHeader->next;
		}

		cout << endl;
	}
	else
	{
		cout << "Current memory: " << _bytesAllocated << endl;
	}
}

void* Heap::operator new (size_t size)
{
	void* pMem = (void*)malloc(size);
	return pMem;
}
