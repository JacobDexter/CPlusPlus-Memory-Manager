#include "memoperator_override.h"

void* operator new(size_t size, Heap* heap)
{
	std::cout << "New Called. (Global)" << std::endl;

	//assign bytes
	size_t nRequestedBytes = size + sizeof(Header) + sizeof(Footer); //calculate total number of bits required
	char* pMem = (char*)malloc(nRequestedBytes); //allocate specific amount of bits for use by object

	//Header Setup
	Header* pHeader = (Header*)pMem; //Set pointer to start of pMem address
	pHeader->heap = heap;
	pHeader->size = size;
	//std::cout << "Debug (Size): " << pHeader->size << std::endl; //check value

	//Footer Setup
	void* pFooterAddr = pMem + sizeof(Header) + size; //start address of footer
	Footer* pFooter = (Footer*)pFooterAddr;

	heap->AddBytesAllocated(size);

	void* pStartOfMemBlock = pMem + sizeof(Header); //gets first element after header assigned memory
	return pStartOfMemBlock;
}

void operator delete(void* pMem)
{
	std::cout << "Delete Called. (Global)" << std::endl;

	Header* pHeader = (Header*)( (char*)pMem - sizeof(Header) ); //Get header start address
	//Footer* pFooter = (Footer*)( (char*)pMem + pHeader->size); //Get footer start address

	//remove memory allocation from heap
	pHeader->heap->RemoveBytesAllocated(pHeader);
	
	free(pHeader);
}
