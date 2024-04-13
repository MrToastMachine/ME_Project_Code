// intbst.cpp
// Implements class IntBST
// Alex O'Mahony, 1st May 2022

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = NULL;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n == NULL) return;

    /* first delete both subtrees */
    clear(n->left);
    clear(n->right);
    delete n; // Delete the node
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (root == NULL){
        root = new Node(value);
        return true;
    }
    else{
        return insert(value, root);
    }
    return false; // REPLACE THIS NON-SOLUTION
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if(value < n->info){
        if(n->left == NULL){
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        } else {
            return insert(value, n->left);
        }
    } else if (value > n->info) {
        if (n->right == NULL){
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        } else {
            return insert(value, n->right);
        }
    } else {
        return false;
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    if (root == NULL){
        return;
    } else {
        printPreOrder(root);
    }
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n == NULL){
        return;
    }
    else {
        cout<<n->info<<" ";
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    if (root == NULL){
        return;
    } else {
        printInOrder(root);
    }
}
void IntBST::printInOrder(Node *n) const {
    if (n == NULL){
        return;                     
    }
    printInOrder(n->left); 
    cout<<n->info<<" ";                     
    printInOrder(n->right); 
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    if (root == NULL){
        return;
    } else {
        printPostOrder(root);
    }
}

void IntBST::printPostOrder(Node *n) const {
    if (n == NULL){
        return;                     
    }
    printPostOrder(n->left); 
    printPostOrder(n->right); 
    cout<<n->info<<" ";               
}

// return sum of values in tree
int IntBST::sum() const {
    if (root == NULL){
        return 0;
    }
    else {
        return sum(root);
    }
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (n == NULL){
        return 0;                     
    }
    return(n->info + sum(n->left) + sum(n->right));
}

// return count of values
int IntBST::count() const {
    if (root == NULL){
        return 0;
    }
    else {
        return count(root);
    }
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (n == NULL){
        return 0;
    }
    else {
        // count(n->left);
        // count(n->right);
        // return 1;
        return (1 + count(n->left) + count(n->right));
    }
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    while (n != NULL) {
        if (value == n->info) {
            return n; // Found
        }
        else if (value < n->info) {
            return getNodeFor(value, n->left);
        }
        else {
            return getNodeFor(value, n->right);
        }
    }
    return NULL; // Node doesn't exist in tree
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if(getNodeFor(value, root) != NULL){
        return true;
    } else {
        return false;
    }
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* currentNode = getNodeFor(value, root);
    if (!contains(value)){
        return NULL;
    }
    //If no left subtree then pred is an ancestor
    if(currentNode->left == NULL){ 
        Node* parentNode = currentNode->parent;
        while(parentNode != NULL){
            if (parentNode->info < value){
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

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* predNode = getPredecessorNode(value);
    if (predNode != NULL){
        return predNode->info;
    }
    else {return 0;}
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    if (!contains(value)){
        return NULL;
    }
    Node* currentNode = getNodeFor(value, root);
    //If no left subtree then pred is an ancestor
    if(currentNode->right == NULL){ 
        Node* parentNode = currentNode->parent;
        while(parentNode != NULL){
            if (parentNode->info > value){
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

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* sucNode = getSuccessorNode(value);
    if (sucNode != NULL){
        return sucNode->info;
    }
    else {return 0;}
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* curNode = getNodeFor(value, root);
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
            if(curNode->parent->info > value){
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
                if (parentNode->info < value){ //curNode is right child
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
                if (parentNode->info < value){ //curNode is right child
                    parentNode->right = curNode->right;
                } else {
                    parentNode->left = curNode->right;
                }
            }
            delete curNode;
            return true;
        }
        else { // CASE 4: node has two children
            int replacement = getSuccessor(value);
            remove(replacement);
            curNode->info = replacement;
            return true;
        }
    }
}
