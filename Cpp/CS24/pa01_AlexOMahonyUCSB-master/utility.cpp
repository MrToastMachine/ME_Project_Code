// utility.cpp
// Actual descriptions and functionality of class in utility.h go here
// Alex O'Mahony - 6872774

#include "utility.h"

#include <iostream>
using namespace std;

//Ordering: Clubs, Diamonds, Spades, Hearts

Card::Card(){
    // This version of constructor only ever called to represent
    // a null card;
    value = 0;
}

Card::Card(char s, string f){
    suit = s;
    face = f;
    value = calculateValue();
}

Card::~Card(){}

int Card::getValue() const{
    return value;
}

int Card::calculateValue() const {
    // Calculates value of card within deck
    // Will return a value between 1 and 52
    int val = 0;
    switch(suit){
        case 'c':
            break;
        case 'd':
            val += 13;
            break;
        case 's':
            val += 26;
            break;
        case 'h':
            val += 39;
            break;
        default:
            cout<<"Suit Not Valid"<<endl;
            return 0;
    }
    if (face == "a"){
        val += 1;
    } else if (face == "j"){
        val += 11;
    } else if (face == "q"){
        val += 12;
    } else if (face == "k"){
        val += 13;
    } else {
        val += stoi(face);
    }
    return val;
}

void Card::printCardShort() const{
    cout<<suit<<" "<<face<<endl;
}

void Card::printCardFull() const{
    if (value == 0) return;
    cout<<"Card: ";
    if (face == "a"){
        cout<<"Ace of ";
    } else if (face == "j"){
        cout<<"Jack of ";
    } else if (face == "q"){
        cout<<"Queen of ";
    } else if (face == "k"){
        cout<<"King of ";
    } else {
        cout<<face<<" of ";
    }
    switch(suit){
        case 'c':
            cout<<"Clubs";
            break;
        case 'd':
            cout<<"Diamonds";
            break;
        case 's':
            cout<<"Spades";
            break;
        case 'h':
            cout<<"Hearts";
            break;
        default:
            cout<<"Suit Not Valid"<<endl;
            break;
    }
    cout<<"(Val: "<<value<<")"<<endl;
}

bool operator==(const Card& card1, const Card& card2){
    if (card1.getValue() == card2.getValue()){
        return true;
    } else {
        return false;
    }
}

bool operator>(const Card& card1, const Card& card2){
    if (card1.getValue() > card2.getValue()){
        return true;
    } else {
        return false;
    }
}

bool operator<(const Card& card1, const Card& card2){
    if (card1.getValue() < card2.getValue()){
        return true;
    } else {
        return false;
    }
}
