//Lecture 6b - Second part of Lecture

//linkedlist.cpp
#include<iostream>
#include <vector>
#include "LinkedList.h"
using namespace std;


//:: Think of this as 's --> Ownership kinda     
void LinkedList::prepend(string value){
    head = new Node {value, head}
}
void LinkedList::append(string value){

}
string LinkedList::getMax() const{ //Getter Function <---------------------- LOOK INTO THIS 'const' PART

}
string LinkedList::getMin() const;{ //Getter Function

}
void LinkedList::clear(){

}
bool LinkedList::search(string value) const{

}

void LinkedList::print(){
    Node* t = head; // t  is a traversal 
    while(t){ // same as while (t!=nullptr)
        cout<<t->data<<" ";
        t = t->next;
    }
    cout<<endl;
}

void LinkedList::clear(Node* h){
    if(!h) return;
    clearList(h->next);
    delete h; // delete nullptr; OKAY!
}


// Precondition: @param1 : LinkeList, @param2: string value
// Postcondition: Insert value to the front of the list and return 
// the resulting linked list
/*
Node* insertToFrontOfList(Node* h , string value){
    //Create a new node
    // Node* p = new Node {value, h};
    // Update the head pointer
    // h = p;
    // p->next = h;
    // Return the modified linked list
    // return p;
    return new Node {value, h};

}
void printList(Node* h){
    Node* t = h; // t  is a traversal 
    while(t){ // same as while (t!=nullptr)
        cout<<t->data<<" ";
        t = t->next;
    }
    cout<<endl;
}

void clearList(Node* h){
    if(!h) return;
    clearList(h->next);
    delete h; // delete nullptr; OKAY!
}
*/

int main(int argc, char const *argv[])
{
    vector<string> TAs {"Tina", "Zack", "Ganesh", "Roman"};
    //Node n1 {"Apoorva", nullptr}; //n1 is on the stack
    //Node* p = new Node {"Apoorva", nullptr}; // *p on the heap

    //Create an empty linked list
    LinkedList list;
    list.prepend(TAs[0]);
    list.printList();
    list.prepend(TAs[1]);
    list.printList();
    list.prepend(TAs[2]);
    list.printList();
    list.prepend(TAs[3]);
    list.printList();

    list.clear();
    list.printList();


    return 0;
}