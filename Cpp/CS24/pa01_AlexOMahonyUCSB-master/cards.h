// cards.h
// Author: Your name
// All class declarations go here
// Alex O'Mahony - 6872774

#ifndef CARDS_H
#define CARDS_H

#include <iostream>

#include "utility.h"

using namespace std;

class PlayerHand {

    public:
        PlayerHand(); // Constructor
        ~PlayerHand(); // Destructor
        bool insert(Card c);
        bool deleteCard(Card c);
        bool contains(Card c) const;
        void printInOrder() const;

        Card getPredecessor(Card c) const;
        Card getSuccessor(Card c) const;

        Card getLowestCard() const;
        Card getHighestCard() const;
        
    private:
        struct Node {
            Card card;
            Node *left, *right, *parent;
            Node(Card c) : left(0), right(0), parent(0) {card=c;}
        };

        Node* root;

        void clear(Node *n);
        bool insert(Card c, Node *n);
        void printInOrder(Node *n) const;

        Node* find(Card c, Node *n) const;
        Node* getPredecessorNode(Card c) const;
        Node* getSuccessorNode(Card c) const;
        Card getLowestCard(Node *n) const;
        Card getHighestCard(Node *n) const;

};

#endif
