// intlist.cpp
// Implements class IntList
// Alex O'Mahony - 25th April 2022

#include "intlist.h"

#include <iostream>
using std::cout;

// copy constructor
IntList::IntList(const IntList& source) {
    if (source.first == 0){
        first = 0;
    }
    else{
        first = new Node;
        Node* srcNode = source.first;
        first->info = srcNode->info;
        while(srcNode->next){
            srcNode = srcNode->next;
            append(srcNode->info);
        }
    }

}

// destructor deletes all nodes
IntList::~IntList() {
    Node *n = first;
    while(n){
        Node* delNode = n;
        n = n->next;
        delete delNode;
    }
}


// return sum of values in list
int IntList::sum() const {
    Node *n = first;
    int sum = 0;
    while (n) {
        sum += n->info;
        n = n->next;
    }
    return sum;
}

// returns true if value is in the list; false if not
bool IntList::contains(int value) const {
    Node *n = first;
    while (n) {
        if(n->info == value){
            return true;
        }
        n = n->next;
    }
    return false;
}

// returns maximum value in list, or 0 if empty list
int IntList::max() const {
    if(first == 0){
        return 0;
    }
    else{
        Node *n = first;
        int max = n->info;
        while (n) {
            if(n->info > max){
                max = n->info;
            }
            n = n->next;
        }
        return max;
    }
}

// returns average (arithmetic mean) of all values, or
// 0 if list is empty
double IntList::average() const {
    if (first == 0){
        return 0;
    }
    else{
        Node *n = first;
        double sum = 0;
        while (n) {
            sum += n->info;
            n = n->next;
        }
        return sum / count();
    }
}

// inserts value as new node at beginning of list
void IntList::insertFirst(int value) {
    Node* newNode = new Node;
    newNode->info = value;
    if (first == 0){
        first = newNode;
    }
    else{
        newNode->next = first;
        first = newNode;
    }
}

//Assignment operator should copy the list from the source
//to this list, deleting/replacing any existing nodes
IntList& IntList::operator=(const IntList& source){
    
    if (source.first == 0){
        first = 0;
    }
    else{
        first = new Node;
        Node* srcNode = source.first;
        first->info = srcNode->info;
        while(srcNode->next){
            srcNode = srcNode->next;
            append(srcNode->info);
        }
    }

    return *this;
}



// DO NOT CHANGE ANYTHING BELOW (READ IT THOUGH)

// constructor sets up empty list
IntList::IntList() : first(0) { }


// append value at end of list
void IntList::append(int value) {
    if (first == 0) { // empty list
        first = new Node;
        first->info = value;
        first->next = 0;
    }
    else {
        Node *n = first;
        while (n->next) // not last node yet
            n = n->next;
        n->next = new Node;
        n->next->info = value;
        n->next->next = 0;
    }
}

// print values enclose in [], separated by spaces
void IntList::print() const {
    Node *n = first;
    cout << '[';
    while (n) {
        cout << n->info;
        if (n->next)
            cout << " ";
        n = n->next;
    }
    cout << ']';
}

// return count of values
int IntList::count() const {
    int result = 0;
    Node *n = first;
    while (n) {
        ++result;
        n = n->next;
    }
    return result;
}
