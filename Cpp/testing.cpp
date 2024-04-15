#include <iostream>
#include <vector>

using namespace std;

int test1[5];
int test2[5];
int test3[5];

int current_test = 2;

int main(int argc, char const *argv[]) {

    int data[5] = {1,2,3,4,5};

    switch (current_test)
    {
    case 1:
        memcpy(&test1, data, sizeof(test1));
        break;

    case 2:
        memcpy(&test2, data, sizeof(test2));
        break;
    
    case 3:
        memcpy(&test2, data, sizeof(test2));
        break;
    
    default:
        break;
    }

    data[3] = 55;

    cout<<"TEST 1 ARRAY..."<<endl;
    for (int i = 0; i < 5; i++){
        cout<<i<<" : "<<test1[i]<<endl;
    }
    cout<<endl;

    cout<<"TEST 1 ARRAY..."<<endl;
    for (int i = 0; i < 5; i++){
        cout<<i<<" : "<<test2[i]<<endl;
    }
    cout<<endl;

    cout<<"TEST 1 ARRAY..."<<endl;
    for (int i = 0; i < 5; i++){
        cout<<i<<" : "<<test3[i]<<endl;
    }
    cout<<endl;
}