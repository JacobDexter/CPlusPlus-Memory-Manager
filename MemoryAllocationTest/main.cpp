#include <iostream>
#include <vector>
#include "GameObject.h"
#include "memoperator_override.h"
using namespace std;

int main()
{
    HeapManager::Initialize();

    //int value = 7;

    //int* array = new int[10];
    //delete[] array;

    //int* array2 = (int*)malloc(sizeof(int) * 10);
    //free(array2);

    //float* test = new float(999.0f);
    //delete test;

    GameObject* object = (GameObject*) ::operator new(sizeof(GameObject));
    delete object;


    //cout << "Number: " << value << endl;
}
