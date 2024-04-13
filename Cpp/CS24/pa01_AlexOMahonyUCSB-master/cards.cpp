// cards.cpp
// Author: Your name
// Implementation of the classes defined in cards.h

#include <iostream>

#include "cards.h"

using namespace std;

PlayerHand::PlayerHand(){
    root = NULL;
}

PlayerHand::~PlayerHand(){
    clear(root);
}

// private helper function
void PlayerHand::clear(Node *n){
    if (n == NULL) return;

    /* first delete both subtrees */
    clear(n->left);
    clear(n->right);
    delete n; // Delete the node
}

// public insert function
bool PlayerHand::insert(Card card){
    if (root == NULL){
        root = new Node(card);
        return true;
    }
    else {
        return insert(card, root);
    }
    return false;
}

// private helper function
bool PlayerHand::insert(Card c, Node *n){
    if(c < n->card){
        if(n->left == NULL){
            n->left = new Node(c);
            n->left->parent = n;
            return true;
        } else {
            return insert(c, n->left);
        }
    } else if (c > n->card) {
        if (n->right == NULL){
            n->right = new Node(c);
            n->right->parent = n;
            return true;
        } else {
            return insert(c, n->right);
        }
    } else {
        return false;
    }
}

// private helper
PlayerHand::Node* PlayerHand::find(Card c, Node *n) const {
    while (n != NULL) {
        if (c == n->card) {
            return n; // Found
        }
        else if (c < n->card) {
            return find(c, n->left);
        }
        else {
            return find(c, n->right);
        }
    }
    return NULL; // Node doesn't exist in tree
}

bool PlayerHand::contains(Card c) const{
    if(find(c, root) != NULL){
        return true;
    } else {
        return false;
    }
}

void PlayerHand::printInOrder() const{
    if (root == NULL){
        return;
    } else {
        printInOrder(root);
    }
}

void PlayerHand::printInOrder(Node *n) const {
    if (n == NULL){
        return;                     
    }
    printInOrder(n->left); 
    n->card.printCardShort();                  
    printInOrder(n->right);
}

// private helper function
PlayerHand::Node* PlayerHand::getPredecessorNode(Card c) const{
    Node* currentNode = find(c, root);
    if (!contains(c)){
        return NULL;
    }
    //If no left subtree then pred is an ancestor
    if(currentNode->left == NULL){ 
        Node* parentNode = currentNode->parent;
        while(parentNode != NULL){
            if (parentNode->card < c){
                return parentNode;
            } else {
                parentNode = parentNode->parent;
            }
        }
        return NULL;
    } 
    else {
        Node* predNode = currentNode->left; 
        while (predNode->right != NULL){
            predNode = predNode->right;
        }
        return predNode;
    }
}

// public member function
Card PlayerHand::getPredecessor(Card c) const{
    Node* predNode = getPredecessorNode(c);
    if (predNode != NULL){
        return predNode->card;
    }
    else {return Card();}
}

// private helper function
PlayerHand::Node* PlayerHand::getSuccessorNode(Card c) const{
    if (!contains(c)){
        return NULL;
    }
    Node* currentNode = find(c, root);
    //If no left subtree then pred is an ancestor
    if(currentNode->right == NULL){ 
        Node* parentNode = currentNode->parent;
        while(parentNode != NULL){
            if (parentNode->card > c){
                return parentNode;
            } else {
                parentNode = parentNode->parent;
            }
        }
        return NULL;
    } 
    else {
        Node* sucNode = currentNode->right; 
        while (sucNode->left != NULL){
            sucNode = sucNode->left;
        }
        return sucNode;
    }
}

// public member function
Card PlayerHand::getSuccessor(Card c) const{
    Node* sucNode = getSuccessorNode(c);
    if (sucNode != NULL){
        return sucNode->card;
    }
    else {return Card();}
}

// public member function
Card PlayerHand::getLowestCard() const{
    if (root == NULL) return Card();
    return getLowestCard(root);
}

// private helper function
Card PlayerHand::getLowestCard(Node *n) const{
    if (n->left == NULL){
        return n->card;
    } else {
        return getLowestCard(n->left);
    }
}

// public member function
Card PlayerHand::getHighestCard() const{
    if (root == NULL) return Card();
    return getHighestCard(root);
}

// private helper function
Card PlayerHand::getHighestCard(Node *n) const{
    if (n->right == NULL){
        return n->card;
    } else {
        return getHighestCard(n->right);
    }
}

// public member function
bool PlayerHand::deleteCard(Card c){
    Node* curNode = find(c, root);
    if (!curNode){return false;}
    else{
        //CASE 1: Leaf node
        if (curNode->left == NULL && curNode->right == NULL){
            if(curNode->parent == NULL){
                //Node selected is root node - only node in tree
                delete curNode;
                root = NULL;
                return true;
            }
            if(curNode->parent->card > c){
                //curNode is left child of parent
                curNode->parent->left = NULL;
            } else {
                //curNode is right child of parent
                curNode->parent->right = NULL;
            }
            delete curNode;
            return true;
        }
        else if (curNode->right == NULL){ //CASE 2: Only left subtree
            if (curNode->parent == NULL){
                //curNode is the root
                curNode->left->parent = NULL;
                root = curNode->left;
            }
            else{
                Node* parentNode = curNode->parent;
                curNode->left->parent = parentNode;
                if (parentNode->card < c){ //curNode is right child
                    parentNode->right = curNode->left;
                } else {
                    parentNode->left = curNode->left;
                }
            }
            delete curNode;
            return true;
        }
        else if (curNode->left == NULL){ // CASE 3: Only right subtree
            if (curNode->parent == NULL){
                //curNode is the root
                curNode->right->parent = NULL;
                root = curNode->right;
            }
            else{
                Node* parentNode = curNode->parent;
                curNode->right->parent = parentNode;
                if (parentNode->card < c){ //curNode is right child
                    parentNode->right = curNode->right;
                } else {
                    parentNode->left = curNode->right;
                }
            }
            delete curNode;
            return true;
        }
        else { // CASE 4: node has two children
            Card replacement = getSuccessor(c);
            deleteCard(replacement);
            curNode->card = replacement;
            return true;
        }
    }
}

