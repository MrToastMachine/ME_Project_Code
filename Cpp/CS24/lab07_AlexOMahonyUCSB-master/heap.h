// heap.h
// Binary heap tree header file for CS 24 lab
// Alex O'Mahony - 6872774

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>

class Heap{

 public:
    void push(int value);     // insert value; //duplicates are allowed
    void pop(); // delete the min element 
    int top();
    bool empty();
    void printHeap() const; //for testing
    
 private:
    std::vector<int> vdata; //store the binary heap tree as a dynamic array
    void bubbleUp(int index);
    void bubbleDown(int index);
};

#endif