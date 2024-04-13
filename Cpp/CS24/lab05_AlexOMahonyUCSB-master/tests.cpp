// tests.cpp
// My Tests for CS 24 lab05

#include "intbst.h"

#include <iostream>
using namespace std;

//Taken from other test file for my own use
int getTest();

void strInsert(){
    IntBST<string> strBST;

    if (!strBST.insert("James")){
        cout<<"Insert Failed: James"<<endl;
        return;
    }
    cout<<"Insert Complete"<<endl;
    if (!strBST.insert("Bob")){
        cout<<"Insert Failed: Bob"<<endl;
        return;
    }
    cout<<"Insert Complete"<<endl;
    if (!strBST.insert("Alice")){
        cout<<"Insert Failed: Alice"<<endl;
        return;
    }
    cout<<"Insert Complete"<<endl;
}

void strPrints() {
    IntBST<string> strBST;

    strBST.insert("Harry");
    strBST.insert("Mark");
    strBST.insert("Bob");
    strBST.insert("Charlie");
    strBST.insert("Robert");

    cout<<"In Order:"<<endl;
    strBST.printInOrder();
    cout<<"\nPre Order:"<<endl;
    strBST.printPreOrder();
    cout<<"\nPost Order:"<<endl;
    strBST.printPostOrder();
}

int main(int argc, const char** argv) {

    cout<<"Running Test File"<<endl;

    // strInsert();
    strPrints();

    string x = "helo";

    return 0;
}

int getTest() {
    cout << "Choice of tests:\n"
	 << "  0. all Cases\n"
	 << "  1. Case 1: Leaf Node\n"
	 << "  2. Case 2: Left Child only\n"
	 << "  3. Case 3: Right Child only\n"
	 << "  4. Case 4: Node with two children\n";
	 
    do {
        int choice;
        cout << "Enter choice:\n";
        cin >> choice;
        if (choice >=0 && choice <= 4)
            return choice;
        cout << "0, 1, 2, 3, or 4 only!\n";
    } while (true);
}
