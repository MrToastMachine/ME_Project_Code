// tests.cpp
// Contains test code for all classes and methods created
// Note: Should have at least 5 test cases for EACH PUBLIC MEMBER FUNCTION
// Alex O'Mahony - 6872774

#include <iostream>

#include "utility.h"
#include "cards.h"

using namespace std;

int getTest_operators();

void testCardConstructor(){
    cout<<"Testing Card Constructor"<<endl;

    char suit1 = 'c';
    string face1 = "9";
    char suit2 = 's';
    string face2 = "10";
    char suit3 = 'h';
    string face3 = "2";

    Card myCard1(suit1,face1);
    Card myCard2(suit2,face2);
    Card myCard3(suit3,face3);
    
    myCard1.printCardFull();
    myCard2.printCardFull();
    myCard3.printCardFull();

    cout<<endl;
}

void testPlayerHandConstructor(){
    
    cout<<"\nTesting PlayerHand Constructor"<<endl;
    PlayerHand alice;
    PlayerHand bob;

    cout<<"Hands Successfully Created"<<endl;

}

void testCardOpOverloads(){
    
    cout<<"\nTesting Card Operator Overloads"<<endl;

    Card myCard1('c',"10"); // value: 10
    Card myCard2('s',"j"); // value: 37
    Card myCard3('h',"a"); // value: 40
    Card myCard4('d',"q"); // value: 25
    Card myCard5('c',"a"); // value: 1
    Card myCard6('s',"j"); // value: 37

    bool all = true;
    int testnum = getTest_operators();
    if (testnum) all = false;

    if(all||testnum == 1){
        cout<<"Test '==' operator"<<endl;
        cout<<"Test 1: ";
        if (myCard1 == myCard4){
            cout<<"FAILED"<<endl;
        } else {
            cout<<"PASSED"<<endl;
        }
        cout<<"Test 2: ";
        if (myCard2 == myCard6){
            cout<<"PASSED"<<endl;
        } else {
            cout<<"FAILED"<<endl;
        }
        cout<<endl;
    }
    if(all||testnum == 2){
        cout<<"Test '>' operator"<<endl;
        cout<<"Test 1: ";
        if (myCard1 > myCard4){
            cout<<"FAILED"<<endl;
        } else {
            cout<<"PASSED"<<endl;
        }
        cout<<"Test 2: ";
        if (myCard2 > myCard6){
            cout<<"FAILED"<<endl;
        } else {
            cout<<"PASSED"<<endl;
        }
        cout<<endl;
    }
    if(all||testnum == 3){
        cout<<"Test '<' operator"<<endl;
        cout<<"Test 1: ";
        if (myCard1 < myCard4){
            cout<<"PASSED"<<endl;
        } else {
            cout<<"FAILED"<<endl;
        }
        cout<<"Test 2: ";
        if (myCard2 < myCard6){
            cout<<"FAILED : ";
            cout<<"returned "<<(myCard2 < myCard6)<<endl;
        } else {
            cout<<"PASSED"<<endl;
        }
        cout<<endl;
    }
    if(all || testnum == 4){
        cout<<"Want : Got"<<endl;
        if (0){ // test ==
            cout<<"0 : "<<(myCard4 == myCard1)<<endl;
            cout<<"0 : "<<(myCard4 == myCard2)<<endl;
            cout<<"0 : "<<(myCard4 == myCard3)<<endl;
            cout<<"0 : "<<(myCard4 == myCard5)<<endl;
            cout<<"0 : "<<(myCard2 == myCard6)<<endl;
            cout<<endl;
        }
        if (1){ // test <
            cout<<"0 : "<<(myCard4 < myCard1)<<endl;
            cout<<"1 : "<<(myCard4 < myCard2)<<endl;
            cout<<"1 : "<<(myCard4 < myCard3)<<endl;
            cout<<"0 : "<<(myCard4 < myCard5)<<endl;
            cout<<"0 : "<<(myCard2 < myCard6)<<endl;
            cout<<endl;
        }
        if (1){ // test >
            cout<<"1 : "<<(myCard4 > myCard1)<<endl;
            cout<<"0 : "<<(myCard4 > myCard2)<<endl;
            cout<<"0 : "<<(myCard4 > myCard3)<<endl;
            cout<<"1 : "<<(myCard4 > myCard5)<<endl;
            cout<<"0 : "<<(myCard2 > myCard6)<<endl;
            cout<<endl;
        }
    }
}

void testHandInsert(){
    
    cout<<"\nTesting PlayerHand Insert"<<endl;
    PlayerHand alice;

    Card myCard1('c',"10"); // value: 10
    Card myCard2('s',"j"); // value: 37
    Card myCard3('h',"a"); // value: 40
    Card myCard4('d',"q"); // value: 25
    Card myCard5('c',"a"); // value: 1
    Card myCard6('s',"j"); // value: 37

    alice.insert(myCard1);
    alice.insert(myCard2);
    alice.insert(myCard3);
    alice.insert(myCard4);
    alice.insert(myCard5);
    alice.insert(myCard6);

    cout<<"Code Runs Fine!"<<endl;
    
}

void testContains(){
    
    cout<<"\nTesting PlayerHand Contains"<<endl;
    PlayerHand alice;

    Card myCard1('c',"10"); // value: 10
    Card myCard2('s',"j"); // value: 37
    Card myCard3('h',"a"); // value: 40
    Card myCard4('d',"q"); // value: 25
    
    Card myCard5('c',"a"); // value: 1
    Card myCard6('s',"j"); // value: 37

    alice.insert(myCard1);
    alice.insert(myCard2);
    alice.insert(myCard3);
    alice.insert(myCard4);

    cout<<"Testing for..."<<endl;
    myCard1.printCardFull();
    cout<<alice.contains(myCard1)<<endl;
    
    myCard2.printCardFull();
    cout<<alice.contains(myCard2)<<endl;
    
    myCard3.printCardFull();
    cout<<alice.contains(myCard3)<<endl;

    myCard4.printCardFull();
    cout<<alice.contains(myCard4)<<endl;
    
    myCard5.printCardFull();
    cout<<alice.contains(myCard5)<<endl;
    
    myCard6.printCardFull();
    cout<<alice.contains(myCard6)<<endl;
}

void testForMemLeak(PlayerHand& hand){
    
    cout<<"\nTesting for possible memory leaks"<<endl;
    Card myCard1('c',"10"); // value: 10
    Card myCard2('s',"j"); // value: 37
    Card myCard3('h',"a"); // value: 40
    Card myCard4('d',"q"); // value: 25
    Card myCard5('c',"a"); // value: 1
    Card myCard6('s',"j"); // value: 37

    hand.insert(myCard1);
    hand.insert(myCard2);
    hand.insert(myCard3);
    hand.insert(myCard4);
    hand.insert(myCard5);
    hand.insert(myCard6);

    cout<<"All Cards added"<<endl;
}

void testInsertMethods(){
    
    cout<<"\nTesting Different Insert Methods"<<endl;
    PlayerHand alice;

    alice.insert(Card('c',"j"));
    alice.insert(Card('h',"a"));
    alice.insert(Card('d',"6"));
    alice.insert(Card('s',"10"));

    cout<<alice.contains(Card('c',"j"))<<endl;
    cout<<alice.contains(Card('h',"a"))<<endl;
    cout<<alice.contains(Card('h',"6"))<<endl;
    cout<<alice.contains(Card('s',"10"))<<endl;
    
    cout<<"Code runs"<<endl;
}

void testPredecessor(){
    
    cout<<"\nTesting getPredecessor"<<endl;

    PlayerHand alice;
    alice.insert(Card('c',"10")); // value: 10
    alice.insert(Card('s',"j")); // value: 37
    alice.insert(Card('h',"a")); // value: 40
    alice.insert(Card('d',"q")); // value: 25
    alice.insert(Card('c',"a")); // value: 1
    alice.insert(Card('c',"5")); // value: 5

    // Structure
    /*       [c 10]
           /       \
        [c a]      [s j]
          \       /     \
         [c 5] [d q]  [h a]
    */

   Card c1 = alice.getPredecessor(Card('d',"q"));
   Card c2 = alice.getPredecessor(Card('h',"a"));
   Card c3 = alice.getPredecessor(Card('d',"q"));
   Card c4 = alice.getPredecessor(Card('c',"a"));

   c1.printCardFull();
   cout<<endl;
   c2.printCardFull();
   cout<<endl;
   c3.printCardFull();
   cout<<endl;
   c4.printCardFull();
   cout<<endl;

   cout<<"Complete"<<endl;
}

void testSuccessor(){
    cout<<"\nTesting getSuccessor"<<endl;

    PlayerHand alice;
    alice.insert(Card('c',"10")); // value: 10
    alice.insert(Card('s',"j")); // value: 37
    alice.insert(Card('h',"a")); // value: 40
    alice.insert(Card('d',"q")); // value: 25
    alice.insert(Card('c',"a")); // value: 1
    alice.insert(Card('c',"5")); // value: 5

    // Structure
    /*       [c 10]
           /       \
        [c a]      [s j]
          \       /     \
         [c 5] [d q]  [h a]
    */

   Card c1 = alice.getSuccessor(Card('c',"5"));
   Card c2 = alice.getSuccessor(Card('c',"10"));
   Card c3 = alice.getSuccessor(Card('d',"q"));
   Card c4 = alice.getSuccessor(Card('h',"a"));

   c1.printCardFull();
   cout<<endl;
   c2.printCardFull();
   cout<<endl;
   c3.printCardFull();
   cout<<endl;
   c4.printCardFull();
   cout<<endl;
}

void testLowestHighest(){
    cout<<"\nTesting get Lowest/Highest Card in Hand"<<endl;

    PlayerHand alice;
    alice.insert(Card('c',"10")); // value: 10
    alice.insert(Card('s',"j")); // value: 37
    alice.insert(Card('h',"a")); // value: 40
    alice.insert(Card('d',"q")); // value: 25
    alice.insert(Card('c',"a")); // value: 1
    alice.insert(Card('c',"5")); // value: 5

    // Structure
    /*       [c 10]
           /       \
        [c a]      [s j]
          \       /     \
         [c 5] [d q]  [h a]
    */

    Card low = alice.getLowestCard();
    Card high = alice.getHighestCard();

    cout<<"Lowest ";
    low.printCardFull();
    cout<<endl;
    cout<<"Highest";
    high.printCardFull();
    cout<<endl;

    cout<<"Empty tree test"<<endl;
    PlayerHand bob;

    Card low2 = bob.getLowestCard();
    Card high2 = bob.getHighestCard();

    cout<<"Lowest ";
    low2.printCardFull();
    cout<<endl;
    cout<<"Highest ";
    high2.printCardFull();
    cout<<endl;

    cout<<"Only Root Node Tree"<<endl;
    PlayerHand carl;
    carl.insert(Card('d',"10"));

    Card low3 = carl.getLowestCard();
    Card high3 = carl.getHighestCard();

    cout<<"Lowest ";
    low3.printCardFull();
    cout<<endl;
    cout<<"Highest ";
    high3.printCardFull();
    cout<<endl;
}


int main(int argc, const char** argv) {
    cout<<"This is the testing file"<<endl;

    testCardConstructor();
    testCardOpOverloads();
    testHandInsert();
    testContains();
    testInsertMethods();

    testPredecessor();
    testSuccessor();

    testLowestHighest();


    // test if cards are being allocated properly
    if (true){
        PlayerHand bob;
        testForMemLeak(bob);

        Card temp1('d', "q");
        Card temp2('c', "5");
        cout<<bob.contains(temp1)<<endl;
        cout<<bob.contains(temp2)<<endl;
    }
    return 0;
}

int getTest_operators() {
    cout << "Choice of tests:\n"
	 << "  0. all Cases\n"
	 << "  1. == Operator\n"
	 << "  2.  > Operator\n"
	 << "  3.  < Operator\n"
     << "  4. Custom\n";
	 
    do {
        int choice;
        cout << "Enter choice:\n";
        cin >> choice;
        if (choice >=0 && choice <= 4)
            return choice;
        cout << "0, 1, 2, or 3 only!\n";
    } while (true);
}