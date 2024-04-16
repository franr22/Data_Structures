/*
 * file: arrayheap-student-proj5.h
 * author: Francisco Rios
 * course: CSI 2334
 * assignment Title: Project 5
 * due date: 4/12/24
 * version: 3.23, C++14
 * The purpose of this file is to implement the ArrayHeap class
 */
#ifndef ARRAY_HEAP_PROJ5_STUDENT_H
#define ARRAY_HEAP_PROJ5_STUDENT_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>

using namespace std;

/* ArrayHeap Constructor
 * The purpose of this function is to initialize the data members
 * and allocate memory for data and heapAndFreeStack arrays.
 *
 * Parameters: none
 * Return Value: none
 */
template <typename T>
ArrayHeap<T>::ArrayHeap(){
    numItems = 0;
    capacity = 10;

    data = new T[capacity];
    heapAndFreeStack = new int[capacity];
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
    for(int i = 0; i < capacity; i++){
        data[i] = h.data[i];
        heapAndFreeStack[i] = h.heapAndFreeStack[i];
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
        data = new T[capacity];
        heapAndFreeStack = new int[capacity];
        for(int i = 0; i < capacity; i++){
            data[i] = ah.data[i];
            heapAndFreeStack[i] = ah.heapAndFreeStack[i];
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
            swap(heapAndFreeStack[lesserChild], heapAndFreeStack[ndx]);
            bubbleDown(lesserChild);
        }
    }
}

/* ArrayHeap insert
 * The purpose of this function is to insert the values at the end,
 * then bubble's up to place the item in the correct stop. Furthermore,
 * doubles the capacity if it is necessary.
 *
 * Parameters: item - The item value that's going to be inserted
 * Return Value: none
 */
template <typename T>
void ArrayHeap<T>::insert(T const &item){
    if(capacity <= numItems){
        doubleCapacity();
    }

    int current = numItems;
    data[heapAndFreeStack[current]] = item;
    numItems++;
    bubbleUp(current);
}

/* ArrayHeap removeMinItem
 * The purpose of this function to remove the least item from the heap.
 *
 * Parameters: none
 * Return Value: none
 */
template <typename T>
void ArrayHeap<T>::removeMinItem(){
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

    for(int i = 0; i < capacity; i++){
        temp[i] = data[i];
        htemp[i] = heapAndFreeStack[i];
    }

    for(int i = capacity; i < capacity * 2; i++){
        htemp[i] = i;
    }

    capacity *= 2;
    delete[] data;
    delete[] heapAndFreeStack;

    data = temp;
    heapAndFreeStack = htemp;
}

#endif
