// utility.h
// This file is for any other classes that need to be implemented for this game
// Alex O'Mahony - 6872774

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

using namespace std;

class Card {
    
    public:
        Card();
        Card(char s, string f);
        ~Card();
        int getValue() const;
        void printCardShort() const;
        void printCardFull() const;
        friend bool operator==(const Card& card1, const Card& card2);
        friend bool operator>(const Card& card1, const Card& card2);
        friend bool operator<(const Card& card1, const Card& card2);

    private:
        char suit;
        string face;
        int value;

        int calculateValue() const;
};

#endif
