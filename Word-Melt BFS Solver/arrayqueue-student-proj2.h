/*
 * file: arrayqueue-student-proj2.h
 * author: Francisco Rios
 * course: CSI 3334
 * assignment: Project 2
 * due date: February, 16 2023
 * version: 3.23, c++14
 * This purpose of this driver is to use code the implementations
 * for the queue functions.
 *
 */

#ifndef PROJECT2_ARRAYQUEUE_STUDENT_PROJ2_H
#define PROJECT2_ARRAYQUEUE_STUDENT_PROJ2_H

#include "arrayqueue-prof-proj2.h"

template <class Base>
ArrayQueue<Base>::ArrayQueue(){
    front = 0;
    length = 0;
    capacity = 10;
    data = new Base[capacity];
}

template <class Base>
ArrayQueue<Base>::ArrayQueue(const ArrayQueue<Base> &q){
    length = q.length;
    capacity = q.capacity;
    data = new Base[capacity];
    for (int i = 0; i < length; i++) {
        data[(front + i) % capacity] = q.data[(q.front + i) % q.capacity];
    }
}

template <class Base>
ArrayQueue<Base>::~ArrayQueue(){
    delete [] data;
}

template <class Base>
void ArrayQueue<Base>::add(const Base &item){
    if(length >= capacity){
        doubleCapacity();
    }
    int r = (front + length) % capacity;
    data[r] = item;
    length++;
}

template <class Base>
void ArrayQueue<Base>::remove(){
    if(length > 0){
        front = (front + 1) % capacity;
        length -= 1;
    }
}

template <class Base>
const Base& ArrayQueue<Base>::getFront() const{
    return data[front];
}

template <class Base>
int ArrayQueue<Base>::getLength() const{
    return length;
}

template <class Base>
const ArrayQueue<Base>& ArrayQueue<Base>::operator=(const ArrayQueue<Base> &q){

    if(this != &q){
        Base* newData = new Base[q.capacity];
        for (int i = 0; i < q.length; i++) {
            newData[i] = q.data[(q.front + i) % q.capacity];
        }
        delete [] data;
        data = newData;
        capacity = q.capacity;
        length = q.length;

        front = 0;
    }
    return *this;
}

template <class Base>
void ArrayQueue<Base>::doubleCapacity(){
    Base* temp = new Base[capacity * 2];
    for (int i = 0; i < length; i++) {
        temp[i] = data[(front + i) % capacity];
    }
    delete[] data;
    data = temp;
    capacity *= 2;
    front = 0;
}

#endif //PROJECT2_ARRAYQUEUE_STUDENT_PROJ2_H
