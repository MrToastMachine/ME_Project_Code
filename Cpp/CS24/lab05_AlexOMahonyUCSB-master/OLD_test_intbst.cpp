// test_intbst.cpp
// My Tests for intbst.cpp for CS 24 lab04

#include "intbst.h"

#include <iostream>
using namespace std;

//Taken from other test file for my own use
int getTest();

void testInsert(){
    cout<<"Testing Insert Function"<<endl;
    IntBST a;
    bool inserted = a.insert(15);
    cout<<"Insert Successful: "<<inserted<<endl;
    a.insert(20);
    a.insert(10);
    a.insert(14);

    a.printInOrder();
}

void testAllPrints(IntBST& tree){
    cout<<"In Order: ";
    tree.printInOrder();
    cout<<endl;

    cout<<"Pre Order: ";
    tree.printPreOrder();
    cout<<endl;

    cout<<"Post Order: ";
    tree.printPostOrder();
    cout<<endl;
}

void testSum(){
    cout<<"Testing getSum"<<endl;
    IntBST tree1;
    tree1.insert(45);
    tree1.insert(67);
    tree1.insert(50);
    tree1.insert(13);
    tree1.insert(10);

    int ans = 45+67+50+13+10;
    int sum = tree1.sum();
    cout<<"RUNNING TEST 1...  ";
    if(sum == ans){
        cout<<"PASSED"<<endl;
    }
    else {
        cout<<"FAILED!"<<endl;
        cout<<"Expected: "<<ans<<endl;
        cout<<"Got: "<<sum<<endl;
    }

    IntBST tree2;
    tree2.insert(6);
    tree2.insert(-15);
    tree2.insert(5);
    tree2.insert(100);
    tree2.insert(-1);

    ans = 6-15+5+100-1;
    sum = tree2.sum();
    cout<<"RUNNING TEST 2...  ";
    if(sum == ans){
        cout<<"PASSED"<<endl;
    }
    else {
        cout<<"FAILED!"<<endl;
        cout<<"Expected: "<<ans<<endl;
        cout<<"Got: "<<sum<<endl;
    }
}

void testCount(){
    cout<<"Testing count"<<endl;
    IntBST tree1;
    tree1.insert(45);
    tree1.insert(67);
    tree1.insert(50);
    tree1.insert(13);
    tree1.insert(10);

    int ans = 5;
    int count = tree1.count();
    cout<<"RUNNING TEST 1...  ";
    if(count == ans){
        cout<<"PASSED"<<endl;
    }
    else {
        cout<<"FAILED!"<<endl;
        cout<<"Expected: "<<ans<<endl;
        cout<<"Got: "<<count<<endl;
    }

    IntBST tree2;
    tree2.insert(6);
    tree2.insert(-15);
    tree2.insert(5);
    tree2.insert(100);
    tree2.insert(-1);

    ans = 5;
    count = tree2.count();
    cout<<"RUNNING TEST 2...  ";
    if(count == ans){
        cout<<"PASSED"<<endl;
    }
    else {
        cout<<"FAILED!"<<endl;
        cout<<"Expected: "<<ans<<endl;
        cout<<"Got: "<<count<<endl;
    }
}

void testPred(){
    cout<<"Testing pred"<<endl;
    IntBST tree1;
    tree1.insert(64);
    tree1.insert(128);
    tree1.insert(8);
    tree1.insert(512);
    tree1.insert(256);
    tree1.insert(32);
    tree1.insert(16);
    tree1.insert(4);

    int ans = 8;
    if(1){
        int pred = tree1.getPredecessor(16);
        cout<<"RUNNING TEST 1...  ";
        if(pred == ans){
            cout<<"PASSED"<<endl;
        }
        else {
            cout<<"FAILED!"<<endl;
            cout<<"Expected: "<<ans<<endl;
            cout<<"Got: "<<pred<<endl;
        }
    }
    IntBST tree2;
    tree2.insert(6);
    tree2.insert(-15);
    tree2.insert(5);
    tree2.insert(100);
    tree2.insert(-1);

    ans = 50;
    if(0){
        int pred = tree2.getPredecessor(6);
        cout<<"RUNNING TEST 2...  ";
        if(pred == ans){
            cout<<"PASSED"<<endl;
        }
        else {
            cout<<"FAILED!"<<endl;
            cout<<"Expected: "<<ans<<endl;
            cout<<"Got: "<<pred<<endl;
        }
    }
}

void testRemove(){
    IntBST tree1;
    tree1.insert(64);
    tree1.insert(128);
    tree1.insert(8);
    tree1.insert(512);
    tree1.insert(256);
    tree1.insert(32);
    tree1.insert(16);
    tree1.insert(4);
    // tree1.insert(72);
    tree1.insert(5);

    cout<<"Before Removals"<<endl;
    testAllPrints(tree1);

    bool all = true;
    int testnum = getTest();
    if (testnum)
        all = false;

    if(all || testnum == 1){
        cout<<"CASE 1: Leaf Node"<<endl;
        cout<<"Removing 5 and 256"<<endl;
        tree1.remove(5);
        tree1.remove(256);
        testAllPrints(tree1);
    }
    if(all || testnum == 2){
        cout<<"CASE 2: Left Child only"<<endl;
        cout<<"Removing 32 and 128"<<endl;
        tree1.remove(32);
        tree1.remove(128);
        testAllPrints(tree1);
    }
    if(all || testnum == 3){
        cout<<"CASE 3: Right Child only"<<endl;
        cout<<"Removing 128"<<endl;
        tree1.remove(128);
        testAllPrints(tree1);
    }
    if(all || testnum == 4){
        cout<<"CASE 2: Two Children"<<endl;
        cout<<"Removing 64"<<endl;
        tree1.remove(64);
        testAllPrints(tree1);
    }
}

void removeEdgeCases(){
    IntBST tree;
    tree.insert(8);
    tree.insert(4);
    tree.insert(12);
    tree.insert(2);
    tree.insert(6);
    tree.insert(10);
    tree.insert(14);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    tree.insert(9);
    tree.insert(11);
    tree.insert(13);
    tree.insert(15);

    int treeSize = tree.count();

    cout<<"Before: "<<endl;
    cout<<"Number of nodes: "<<treeSize<<endl;
    testAllPrints(tree);
    cout<<"Removed 8:"<<endl;
    tree.remove(8);
    testAllPrints(tree);
    cout<<"Removed 9"<<endl;
    tree.remove(9);
    testAllPrints(tree);

    treeSize = tree.count();
    cout<<"Number of nodes: "<<treeSize<<endl;

    tree.insert(8);
    tree.remove(12);
    tree.insert(12);
    cout<<"Reinsert 8, remove 12, reinsert 12, remove 6"<<endl;


    tree.remove(6);
    testAllPrints(tree);
    for (int i = 1; i < 18; i++){
        cout<<"Tree Contains "<<i<<": "<<tree.contains(i)<<endl;
    }

    

}

int main(int argc, char const *argv[])
{
    cout<<"Running my test Script"<<endl;
    // testClear();
    // testInsert();
    // testAllPrints();
    // testSum();
    // testCount();
    // testPred();
    // testRemove();
    removeEdgeCases();
    
    cout<<"Test Completed!"<<endl;
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
