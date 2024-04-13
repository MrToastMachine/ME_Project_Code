// heap.cpp
// Alex O'Mahony - 6872774

#include "heap.h"
#include <iostream>
using std::cout;

using namespace std;

// Pushes a value into the heap, then ensures
// the heap is correctly arranged
void Heap::push(int value){
    vdata.push_back(value);

    bubbleUp(vdata.size()-1);
}

void Heap::bubbleUp(int index){
    if(index == 0){return;}
    int parent = (index - 1) / 2;
    int tempVal;

    if (vdata[parent] >= vdata[index]){
        tempVal = vdata[parent];
        vdata[parent] = vdata[index];
        vdata[index] = tempVal;
        bubbleUp(parent);
    }
}

// Pops the minimum value off the heap
// (but does not return it), then ensures
// the heap is correctly arranged
void Heap::pop(){
    // cout<<"Before Pop:"<<endl;
    // printHeap();
    if (empty()) return;
    int tempVal = vdata[0];
    vdata[0] = vdata[vdata.size()-1];
    vdata[vdata.size()-1] = tempVal;
    vdata.pop_back();

    bubbleDown(0);
    // cout<<"After Pop:"<<endl;
    // printHeap();
}

void Heap::bubbleDown(int index){
    if(empty()) return;
    int leftChild = index*2 + 1;
    int leftVal = vdata[leftChild];
    int rightVal = vdata[leftChild+1];
    int value = vdata[index];
    int temp;

    if (leftChild >= vdata.size()){ return;}
    if(leftChild + 1 < vdata.size()){
        // Both Children exist
        if(leftVal < value){
            // left is lower
            if(rightVal < value){
                //both children lower
                if(leftVal > rightVal){
                    //replace with right
                    temp = vdata[leftChild+1];
                    vdata[leftChild+1] = value;
                    vdata[index] = temp;
                    bubbleDown(leftChild+1);
                    return;
                }
            }
            //replace with left because either
            // > ONLY left is lower
            // > Both are lower but left is <= right
            temp = vdata[leftChild];
            vdata[leftChild] = value;
            vdata[index] = temp;
            bubbleDown(leftChild);
        }
    } else {
        // only left tree exists
        if (leftVal < value){
            temp = vdata[leftChild];
            vdata[leftChild] = value;
            vdata[index] = temp;
            bubbleDown(leftChild);
        }
    }
    
}

// Returns the minimum element in the heap
int Heap::top(){
    if(empty()) return 0;
    return vdata.front();
}

// Returns true if the heap is empty, false otherwise
bool Heap::empty(){
  return vdata.empty();
}

void Heap::printHeap() const{
    for(int num: vdata){
        cout<<num<<" ";
    }
    cout<<endl;
}
    