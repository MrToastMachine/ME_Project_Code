// test.cpp

#include <iostream>
#include <vector>

#include "heap.h"

using namespace std;

void printVect(vector<int> v){
    for(int num: v){
        cout<<num<<" ";
    }
    cout<<endl;
}

void testTop(){
    Heap minH;
    minH.push(5);
    minH.push(8);
    minH.push(12);
    minH.push(20);
    minH.push(4);

    minH.pop();

    int top = minH.top();

    cout<<"Top: "<<top<<endl;
}

void testPush(){
    Heap minH;
    minH.push(5);
    minH.push(8);
    minH.push(12);
    minH.push(20);
    minH.push(4);

    minH.printHeap();
}

void testPop(){
    Heap minH;
    minH.push(5);
    minH.push(8);
    minH.push(12);
    minH.push(20);
    minH.push(4);

    cout<<"Before pop:"<<endl;
    minH.printHeap();

    minH.pop();

    cout<<"After pop:"<<endl;
    minH.printHeap();

}

void testEmpty(){
    Heap minH;
    minH.push(5);
    minH.push(8);
    minH.push(20);
    minH.push(4);

    cout<<"Full Heap;"<<endl;
    minH.printHeap();

    cout<<"\nPopping 3 times"<<endl;
    minH.pop();
    minH.pop();
    minH.pop();
    cout<<"IsEmpty: "<<minH.empty()<<endl;

    cout<<"\nPopping 1 time1"<<endl;
    minH.pop();
    cout<<"IsEmpty: "<<minH.empty()<<endl;
}

int main(int argc, const char** argv) {

    testEmpty();

    return 0;
}