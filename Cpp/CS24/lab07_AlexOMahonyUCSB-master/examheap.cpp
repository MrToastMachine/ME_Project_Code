// examheap.cpp
// More complete tests of Heap functions for CS 24 lab

#include "heap.h"
#include <queue>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cassert>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "usage: " << argv[0] << " test#\n";
        return 1;
    
    }
    int t = atoi(argv[1]);
    std::priority_queue<int, std::vector<int>, std::greater<int>> data;
    Heap h;
    int numvals = 3;
    if (t == 1) {
        cout << "testing with one and two values .... ";
        int sum = 0, count = 0;
        Heap h;
        srand(time(0));
        int arand = rand() % 1000;
        int brand = arand -10;
        h.push(arand);
        assert(h.top()==arand);
        h.pop();
        assert(h.empty());
        h.push(arand);
        h.push(brand);
        assert(h.top()==brand);
        h.pop();
        h.pop();
        assert(h.empty());
        h.push(brand);
        h.push(arand);
        assert(!h.empty());
        assert(h.top()==brand);

        cout << "PASSED\n";
        return 0;
        
	}
    if (t == 2) {
        cout << "testing with three values ... ";
        numvals = 3;       
    }
    if (t == 3) {
       cout << "testing with four values ... ";
       numvals = 4;
    }
    if (t == 4){
        cout << "testing with large data set ... ";
        numvals = 200;
    }
    if (t == 5){
        cout << "testing with very large data set ... ";
        numvals = 20000;
    } 
    for (int i=0; i < numvals; i++) {
            int arand = rand() % 2000;
            data.push(arand);
            h.push(arand);
    }
    int count = 0;
    while(!data.empty()){
        assert(!h.empty());
        if(data.top() != h.top()){
            cout<<endl;
            cout<<data.top()<<endl;
            cout<<h.top()<<endl;
            cout<<count<<endl<<endl;
            h.printHeap();
        }
        assert(data.top()==h.top());
        data.pop();
        h.pop();
        count += 1;
    }
    cout << "PASSED\n";

        
    return 0;

}
