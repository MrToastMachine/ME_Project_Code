// main.cpp
// This is the main game builder file which reads in two hands from
// text files and plays the game
// Alex O'Mahony - 6872774

#include <iostream>
#include <fstream>
#include <string>

#include "cards.h"
#include "utility.h"

using namespace std;

void AliceTurn(PlayerHand& alice, PlayerHand& bob);
void BobTurn(PlayerHand& alice, PlayerHand& bob);

void AliceTurn(PlayerHand& alice, PlayerHand& bob){
    Card curCard = alice.getLowestCard();
    while(true){
        if (curCard.getValue() == 0) return;
        if(bob.contains(curCard)){
            //bob also has this card
            cout<<"Alice picked matching card ";
            curCard.printCardShort();
            bob.deleteCard(curCard);
            alice.deleteCard(curCard);
            BobTurn(alice, bob);
        }
        else {
            //bob doesn't have the card
            curCard = alice.getSuccessor(curCard);
        }
    }
}

void BobTurn(PlayerHand& alice, PlayerHand& bob){
    Card curCard = bob.getHighestCard();
    while(true){
        if(curCard.getValue() == 0) return;
        if(alice.contains(curCard)){
            //alice also has this card
            cout<<"Bob picked matching card ";
            curCard.printCardShort();
            alice.deleteCard(curCard);
            bob.deleteCard(curCard);
            AliceTurn(alice, bob);
        }
        else {
            //alice doesn't have the card
            curCard = bob.getPredecessor(curCard);
        }
    }
}

int main(int argv, char** argc){
    if(argv < 3){
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1 (argc[1]);
    ifstream cardFile2 (argc[2]);
    string line;


    if (cardFile1.fail() || cardFile2.fail() ){
        cout << "Could not open file " << argc[2];
        return 1;
    }

    char delim = ' ';

    PlayerHand alice;
    PlayerHand bob;

    //Read each file
    while (getline (cardFile1, line) && (line.length() > 0)){
        char suit = line.at(0);
        string face = line.substr(line.find(delim)+1,-1);

        alice.insert(Card(suit, face));
    }
    cardFile1.close();


    while (getline (cardFile2, line) && (line.length() > 0)){
        char suit = line.at(0);
        string face = line.substr(line.find(delim)+1,-1);

        bob.insert(Card(suit, face));
    }
    cardFile2.close();


    // Begin Alice's Turn
    AliceTurn(alice, bob);

    cout<<endl;
    cout<<"Alice's cards:"<<endl;
    alice.printInOrder();
    cout<<endl;

    cout<<"Bob's cards:"<<endl;
    bob.printInOrder();

    return 0;
}
