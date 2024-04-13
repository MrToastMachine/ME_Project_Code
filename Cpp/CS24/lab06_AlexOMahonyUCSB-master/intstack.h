// intstack.h - stack class for CS 24 lab practice

// The class is implemented here too. All very bare bones,
// with no error-checking nor even pre-condition stating.
// But know two things: (1) don't push on full stack, which
// is a stack currently holding 10 ints; (2) don't pop or
// top from empty stack - use bool empty() to check.

#ifndef INTSTACK_H
#define INTSTACK_H

#define CAPACITY 10

class Stack {

public:
    Stack() : next(0) { }
    void push(int n) { data[next++] = n; }
    void pop() { --next; }
    int top() const { return data[next-1]; }
    bool empty() const { return next <= 0; }
private:
    int next, data[CAPACITY];
};

#endif
