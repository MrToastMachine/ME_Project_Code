#include "intlist.h"

#include <cstdlib> // provides atoi
#include <iostream>
using namespace std;

void testSum(IntList& l1){
    cout<<l1.sum()<<endl;
}

void testContains(IntList& l1){
    cout<<"15? --> ";
    cout<<l1.contains(15)<<endl;

    cout<<"8? --> ";
    cout<<l1.contains(8)<<endl;

    cout<<"4? --> ";
    cout<<l1.contains(4)<<endl;
}

void testMax(IntList& l1){
    cout<<"Max Val: "<<l1.max()<<endl;
}

void testAvg(IntList& l1){
    cout<<"Average Value: "<<l1.average()<<endl;
}

void testInsertBefore(IntList& l1){
    cout<<"Inserting 33 at beginning of list!"<<endl;
    l1.insertFirst(33);
    cout<<"List after insertion: ";
    l1.print(); cout << endl;
}

void testCC(IntList& l1){
    cout<<"Testing Copy Constructor"<<endl;

    IntList newList(l1);

    cout<<"New List Created: ";
    newList.print(); cout<<endl;
}

void testEquals(IntList& l1){
    IntList newList;

    newList = l1;

    cout<<"New List Created: ";
    newList.print(); cout<<endl;
}

int main(int argc, char* argv[]) {
    cout<<"Running myTests.cpp"<<endl;

    IntList list1;
    list1.append(2);
    list1.append(4);
    list1.append(67);
    list1.append(8);

    cout<<"List Being Tested... ";
    list1.print(); cout<<endl;

    // testSum(list1);
    // testContains(list1);
    // testMax(list1);
    // testAvg(list1);
    // testInsertBefore(list1);
    // testCC(list1);
    testEquals(list1);

    return 0;
}

/* Notes
argc is Number of Arguments, name of file counts as 1
eg:
    ./myTests 5 2   --> Here, argc == 3

*/