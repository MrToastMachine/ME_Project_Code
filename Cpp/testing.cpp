#include <iostream>
#include <vector>

using namespace std;

int test[5] = [];


void gg_copyToNewVector(vector<int>& new_vect){
    for (int i = 0; i < vect.size(); i++){
        new_vect.push_back(vect[i]);
    }
}

double getDistFromMicros(int uS_val){
    double c = 343.0; // Speed of sound m/s
    return c * uS_val / 2000000.0;
}

int main(int argc, char const *argv[]) {


    for (int i = 0; i < uS.size(); i++){
        cout<<uS[i] << " : " << getDistFromMicros(uS[i]) <<endl;
    }

}