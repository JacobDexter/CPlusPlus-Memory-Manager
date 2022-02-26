#pragma once
#include "MemoryManager.h"

struct Header;

class Heap
{
public:
	Heap(std::string name);
	~Heap();

public:
	//getters
	//get header
	Header* GetHeader() { return _head; }
	//set parent
	void SetParent(Heap* parent);
	//get parent
	Heap* GetParent() { return _parent; }
public:
	//mem allocation
	void AddBytesAllocated(size_t bytes, Header* header);
	//mem remove allocation
	void RemoveBytesAllocated(size_t bytes, Header* header);
	//new overload
	static void* operator new (size_t size);
	//debug heap
	void Debug();
public:
	//child heap
	Heap* _child = NULL;
private:
	//Header
	Header* _head = NULL;
	//bytes allocated to heap
	unsigned _bytesAllocated;
	//heap name
	std::string _name;
	//parent heap
	Heap* _parent = NULL;
};

