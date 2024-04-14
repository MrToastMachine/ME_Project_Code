#include <iostream>
#include <vector>

using namespace std;


vector<int> vect;
vector<int> uS{425, 442, 450, 467, 475, 500, 524, 549, 574, 599, 624, 648, 673, 698, 723, 747, 772, 797, 821, 845, 870, 895, 919, 943, 968, 992, 1016, 1037, 1040, 9754, 9759, 9786, 9812, 9828, 9837, 9854, 9863, 9888, 9913, 9938, 9963, 9989, 10014, 10039, 10064, 10088, 10105, 10113, 10138, 10163, 10187, 10212, 10237, 10261, 10286, 10311, 10336, 10360, 10385, 10401, 10410, 10435, 10460, 10485, 10510, 10534, 10559, 10584, 10600, 10609, 10633, 10658, 10683, 10708, 10733, 10751, 10758, 10776, 10782, 10807, 10831, 10852, 10856, 19763, 19791, 19810, 19817, 19842, 19868, 19893, 19918, 19943, 19968, 19993, 20018, 20043, 20068, 20092, 20117, 20146, 20166, 20191, 20213, 20215};

vector<vector<int>> myVect{{2,4,6,7}, {1,3,6,8}};


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