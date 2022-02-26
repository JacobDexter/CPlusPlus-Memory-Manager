#include "MemoryManager.h"

void* operator new(size_t size, Heap* heap)
{
	//assign bytes
	size_t nRequestedBytes = size + sizeof(Header) + sizeof(Footer); //calculate total number of bits required
	char* pMem = (char*)malloc(nRequestedBytes); //allocate specific amount of bits for use by object

	//Header Setup
	Header* pHeader = (Header*)pMem; //Set pointer to start of pMem address
	pHeader->heap = heap;
	pHeader->size = size;
	//std::cout << "Debug (Size): " << pHeader->size << std::endl; //check value

	//mem to heap
	heap->AddBytesAllocated(size, pHeader);

	//Footer Setup
	void* pFooterAddr = pMem + sizeof(Header) + size; //start address of footer
	Footer* pFooter = (Footer*)pFooterAddr;

	void* pStartOfMemBlock = pMem + sizeof(Header); //gets first element after header assigned memory
	return pStartOfMemBlock;
}

void* operator new(size_t size)
{
	return ::operator new(size, &HeapManager::GetDefaultHeap());
}


void operator delete(void* pMem)
{
	Header* pHeader = (Header*)( (char*)pMem - sizeof(Header) ); //Get header start address
	//Footer* pFooter = (Footer*)( (char*)pMem + pHeader->size); //Get footer start address

	//remove memory allocation from heap
	pHeader->heap->RemoveBytesAllocated(pHeader->size, pHeader);
	
	free(pHeader);
}
