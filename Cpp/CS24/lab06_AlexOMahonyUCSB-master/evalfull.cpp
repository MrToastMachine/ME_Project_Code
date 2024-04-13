// evalfull.cpp - evaluates a fully-parenthesized expression
// Alex O'Mahony - May 26th 2022

#include <cstdlib>   // for atof function
#include <cstdio>    // for sscanf
#include <cstring>   // for strcmp and strtok
#include <iostream>
#include <stack>     // STL stack class
#include <string>    // for throwing string exceptions
using namespace std;

// constants used to identify a token - DO NOT CHANGE
enum TokenType {LEFT, RIGHT, ADD, SUBTRACT, MULTIPLY,
                DIVIDE, NUMBER, OTHER};
TokenType identify(char *t);

// balanced - returns true only if parentheses are balanced
// in the expression, where expression is an array of C
// string tokens like { "(", "4.2", ")" } and numTokens
// is the number of tokens in the array (3 in the sample)

bool balanced(char *expression[], int numTokens) {

    stack<char *> s;

    TokenType tokType; 
    for (int i = 0; i < numTokens; i++){
        tokType = identify(expression[i]);
        switch(tokType) {
            case LEFT:
                // push right bracket to stack
                s.push( (expression[i]) );
                break;
            case RIGHT:
                // If right bracket found when no left are in stack 
                // then eq must be unbalanced
                if(s.empty()){return false;}
                // otherwise we can pop the last added left bracket
                s.pop();
                break;
            default:
                break; // rest of characters accounted for below
        }
    }
    // if stack is empty after looping through entire expression then
    // num of left brackets == num of right brackets
    if (s.empty()) {
        return true;
    }

    return false; // REPLACE THIS return WITH ACTUAL IMPLEMENTATION
}

// DO NOT CHANGE ANYTHING BELOW - BUT DO READ IT

// utility function returns one of those constants
TokenType identify(char *t) {
    if (strcmp(t, "(") == 0)
        return LEFT;
    if (strcmp(t, ")") == 0)
        return RIGHT;
    if (strcmp(t, "+") == 0)
        return ADD;
    if (strcmp(t, "-") == 0)
        return SUBTRACT;
    if (strcmp(t, "*") == 0)
        return MULTIPLY;
    if (strcmp(t, "/") == 0)
        return DIVIDE;
    float value;
    if (sscanf(t, "%g", &value) == 1)
        return NUMBER;
    return OTHER;
}

// evalFull - evaluates a fully-parenthesized expression;
// relies on function balanced;
// returns result of the expression if it is formed properly
// throws string message if expression is not proper
double evalFull(char *expression[], int numTokens) {

    if ( !balanced(expression, numTokens) )
        throw string("parentheses are not balanced");

    stack<double> numbers;
    stack<TokenType> ops;
    double result = 0, leftValue, rightValue;
    TokenType type, op;

    for (int i=0; i<numTokens; i++) {
        type = identify(expression[i]);
        switch(type) {
            case NUMBER:
                numbers.push( atof(expression[i]) );
                break;
            case ADD: case SUBTRACT: case MULTIPLY: case DIVIDE:
                ops.push(type);
                break;
            case LEFT:
                break; // ignore left paren (know balanced already)
            case RIGHT:
                if (numbers.empty())
                    throw string("empty stack where two numbers expected");
                rightValue = numbers.top();
                numbers.pop();

                if (ops.empty())
                    throw string("empty stack where operator expected");
                op = ops.top();
                ops.pop();

                if (numbers.empty())
                    throw string("empty stack where one number expected");
                leftValue = numbers.top();
                numbers.pop();

                if (op == ADD)
                    numbers.push(leftValue + rightValue);
                else if (op == SUBTRACT)
                    numbers.push(leftValue - rightValue);
                else if (op == MULTIPLY)
                    numbers.push(leftValue * rightValue);
                else // op == DIVIDE
                    numbers.push(leftValue / rightValue);

                break; // end right paren case

            default:
                throw string("unknown token: ")
                      + string(expression[i]);
        }
    }

    if (!ops.empty())
        throw string("operator(s) left on stack at end");

    if (numbers.empty())
        throw string("empty stack where one result should be");

    result = numbers.top();
    numbers.pop();
    if (!numbers.empty())
        throw string("number(s) left on stack at end");

    return result;
}

#define MAXLEN 100

// main gets expression from user and evaluates it
int main() {
    char input[MAXLEN], *tokens[MAXLEN/2];

    // tokens is an array of pointers to chars

    cout << "enter expression: ";
    cin.getline(input, MAXLEN);
    // ( ( 4.2 * 6.4 ) + 5 )
    char *ptr = strtok(input, " ");

    int count = 0;
    while (ptr != 0) {
        tokens[count] = ptr;
        ++count;
        ptr = strtok(0, " ");
    }

    try {
        double result = evalFull(tokens, count);
        cout << "result: " << result << endl;
    }
    catch(string error) {
        cerr << "bad expression: " << error << endl;
        return 1;
    }

    return 0;
}
