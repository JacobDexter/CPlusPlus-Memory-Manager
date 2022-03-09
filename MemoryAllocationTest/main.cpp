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

    GameObject* object = :: new(&HeapManager::GetDefaultHeap()) GameObject;
    GameObject* object2 = :: new(heap) GameObject;
    GameObject* object3 = :: new(heap2) GameObject;
    GameObject* object4 = :: new(heap) GameObject;
    GameObject* object5 = :: new(&HeapManager::GetDefaultHeap()) GameObject;

    //heap walk
    HeapManager::GetDefaultHeap().HeapWalk();
    heap->HeapWalk();
    heap2->HeapWalk();

    delete object;
    delete object4;
    delete object2;
    delete object5;
    delete object3;
}
