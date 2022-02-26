#include <iostream>
#include <vector>
#include "GameObject.h"
#include "MemoryManager.h"
using namespace std;

int main()
{
    HeapManager hManager = HeapManager();

    Heap* heap = hManager.CreateHeap("gameobjects", "");
    Heap* heap2 = hManager.CreateHeap("gameobjects2", "");

    GameObject* object = :: new(&HeapManager::GetDefaultHeap()) GameObject("GameObject1");
    GameObject* object2 = :: new(heap) GameObject("GameObject2");
    GameObject* object3 = :: new(heap2) GameObject("GameObject3");
    GameObject* object4 = :: new(heap) GameObject("GameObject4");
    GameObject* object5 = :: new(&HeapManager::GetDefaultHeap()) GameObject("GameObject5");

    delete object;
    delete object4;
    delete object2;
    delete object5;
    delete object3;
}
