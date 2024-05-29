#ifndef ARRAY_HEAP_STUDENT_PROJ6_H
#define ARRAY_HEAP_STUDENT_PROJ6_H

#include "arrayheap-prof-proj6.h"
#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
ArrayHeap<T>::ArrayHeap(){
    numItems = 0;
    capacity = 10;

    data = new T[capacity];
    heapAndFreeStack = new int[capacity];
    dataToHeap = new int[capacity];
    for(int i = 0; i < capacity; i++){
        heapAndFreeStack[i] = i;
    }
}

/* ArrayHeap Copy Constructor
 * The purpose of this function is to initialize the data members
 * with the parameter's values and allocate memory for data
 * and heapAndFreeStack
 *
 * Parameters: h - The ArrayHeap object that's going to be copied
 * Return Value: none
 */
template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h){
    numItems = h.numItems;
    capacity = h.capacity;

    data = new T[capacity];
    heapAndFreeStack = new int[capacity];
    dataToHeap = new int[capacity];
    for(int i = 0; i < capacity; i++){
        data[i] = h.data[i];
        heapAndFreeStack[i] = h.heapAndFreeStack[i];
        dataToHeap[i] = h.dataToHeap[i];
    }
}

/* ArrayHeap Destructor
 * The purpose of this function is to reset the to default value members and
 * delete all the allocated memory.
 *
 * Parameters: none
 * Return Value: none
 */
template <typename T>
ArrayHeap<T>::~ArrayHeap(){
    numItems = 0;
    capacity = 10;

    delete []data;
    delete []heapAndFreeStack;
    delete []dataToHeap;

}

/* ArrayHeap operator=
 * The purpose of this function is to set the data members to the
 * parameter's value and copy the data and heapAndFreeStack.
 *
 * Parameters: ah - the ArrayHeap that's going to be copied
 * Return Value: *this
 */
template <typename T>
ArrayHeap<T> const& ArrayHeap<T>::operator=(ArrayHeap<T> const &ah){
    if(&ah != this){
        numItems = ah.numItems;
        capacity = ah.capacity;
        delete[] data;
        delete[] heapAndFreeStack;
        delete[] dataToHeap;

        data = new T[capacity];
        heapAndFreeStack = new int[capacity];
        dataToHeap = new int[capacity];
        for(int i = 0; i < capacity; i++){
            data[i] = ah.data[i];
            heapAndFreeStack[i] = ah.heapAndFreeStack[i];
            dataToHeap[i] = ah.dataToHeap[i];
        }
    }
    return *this;
}

/* ArrayHeap getMinItem
 * The purpose of this function is to get the highest priority item
 *
 * Parameters: none
 * Return Value: The highest priority item
 */
template <typename T>
T const& ArrayHeap<T>::getMinItem() const{
    return data[heapAndFreeStack[0]];
}

/* ArrayHeap getNumItems
 * The purpose of this function is to get the total number of items
 *
 * Parameters: none
 * Return Value: The total number of items
 */
template <typename T>
int ArrayHeap<T>::getNumItems() const{
    return numItems;
}

/* ArrayHeap bubbleUp
 * The purpose of this function is to bubble up an item to the correct place
 * in its heap
 *
 * Parameters: ndx - The index of the object that's to bubble up
 * Return Value: none
 */
template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx){
    int parent = (ndx -1)/2;
    if(ndx <= 0){
        return;
    }
    if(data[heapAndFreeStack[ndx]] < data[heapAndFreeStack[parent]]){
        swap(dataToHeap[heapAndFreeStack[ndx]],
             dataToHeap[heapAndFreeStack[parent]]);
        swap(heapAndFreeStack[ndx],heapAndFreeStack[parent]);
        bubbleUp(parent);
    }
}

/* ArrayHeap bubbleDown
 * The purpose of this function is to bubble down an item to the correct place
 * in its heap
 *
 * Parameters: ndx - The index of the object that's to bubble up
 * Return Value: none
 */
template <typename T>
void ArrayHeap<T>::bubbleDown(int ndx){
    int child1 = (2 * ndx) + 1;
    int child2 = (2 * ndx) + 2;

    if(child1 < numItems){
        int lesserChild = child1;
        if((data[heapAndFreeStack[child2]] <
            data[heapAndFreeStack[child1]]) && (child2 < numItems)){
            lesserChild = child2;
        }
        if(data[heapAndFreeStack[lesserChild]] < data[heapAndFreeStack[ndx]]){
            swap(dataToHeap[heapAndFreeStack[ndx]],
                 dataToHeap[heapAndFreeStack[lesserChild]]);
            swap(heapAndFreeStack[lesserChild], heapAndFreeStack[ndx]);
            bubbleDown(lesserChild);
        }
    }
}

/* ArrayHeap insert
 *
 *
 *
 */
template <typename T>
int ArrayHeap<T>::insert(T const &item){
    if(capacity == numItems){
        doubleCapacity();
    }

    int current = heapAndFreeStack[numItems];
    data[heapAndFreeStack[numItems]] = item;
    dataToHeap[heapAndFreeStack[numItems]] = numItems;
    bubbleUp(numItems);
    numItems++;

    return current;
}

/* ArrayHeap removeMinItem
 * The purpose of this function to remove the least item from the heap.
 *
 * Parameters: none
 * Return Value: none
 */
template <typename T>
void ArrayHeap<T>::removeMinItem(){
    swap(dataToHeap[heapAndFreeStack[0]],
         dataToHeap[heapAndFreeStack[numItems-1]]);
    swap(heapAndFreeStack[0], heapAndFreeStack[numItems - 1]);
    numItems--;
    bubbleDown(0);
}

/* ArrayHeap doubleCapacity
 * The purpose of this function to double the capacity of the heap whenever
 * there isn't a sufficient capacity for the objects/items.
 *
 * Parameters: none
 * Return Value: none
 */
template <typename T>
void ArrayHeap<T>::doubleCapacity(){
    T* temp = new T[capacity * 2];
    int* htemp = new int[capacity * 2];
    int* dataToHeapTemp = new int[capacity * 2];

    for(int i = 0; i < capacity; i++){
        temp[i] = data[i];
        htemp[i] = heapAndFreeStack[i];
        dataToHeapTemp[i] = dataToHeap[i];
    }

    for(int i = capacity; i < capacity * 2; i++){
        htemp[i] = i;
    }

    capacity *= 2;
    delete[] data;
    delete[] heapAndFreeStack;
    delete[] dataToHeap;

    data = temp;
    heapAndFreeStack = htemp;
    dataToHeap = dataToHeapTemp;

}

template <typename T>
bool ArrayHeap<T>::isOnHeap(int key) const{
    if(key >= 0 && key < capacity){
        if(dataToHeap[key] >= 0 && dataToHeap[key] < numItems){
            if(heapAndFreeStack[dataToHeap[key]] == key){
                return true;
            }
        }
    }
    return false;
}

template <typename T>
void ArrayHeap<T>::changeItemAtKey(int key, T const &newItem){
    if(isOnHeap(key)){
        data[key] = newItem;
        bubbleUp(dataToHeap[key]);
        bubbleDown(dataToHeap[key]);
    }
}


#endif
