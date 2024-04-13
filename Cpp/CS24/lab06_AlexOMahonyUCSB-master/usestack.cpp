// usestack.cpp - for CS 24 lab practice using stacks
// Alex O'Mahony - May 26th 2022

#include "intstack.h"
#include <iostream>
using namespace std;

void testPop(){
    Stack myStack;

    myStack.push(10);
    myStack.push(-90);
    myStack.push(70);
    myStack.push(11);
    myStack.push(9);

    while (!myStack.empty()){
        cout<<"Popping : "<<myStack.top()<<endl;
        myStack.pop();
        cout<<"Successfully popped value"<<endl;
    }
    cout<<"Pop Tests Complete"<<endl;
}

int main() {
    Stack s;

    testPop();

    cout<<"Is Empty: "<<s.empty()<<endl;

    s.push(10);
    s.push(20);

    cout<<"Is Empty: "<<s.empty()<<endl;

    while (!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }

    cout<<"Is Empty: "<<s.empty()<<endl;

    return 0;
}
