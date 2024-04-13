// movies.cpp
#include <iomanip>

#include "movies.h"

Movie::Movie(){
    name = "N/A";
    rating = 0;
    cout<<"WARNING: Movie object created without initial values!!"<<endl;
}

Movie::Movie(string n, double r){
    name = n;
    rating = r;
}

Movie::~Movie(){

}

void Movie::printMovie() const{
    cout<<name<<", "<<fixed<<setprecision(1)<<rating<<endl;
}

// bool operator==(const Movie& mov1,const Movie& mov2){}

bool operator>(const Movie& mov1,const Movie& mov2){
    if (mov1.name > mov2.name){
        return true;
    }
    return false;
}

bool operator<(const Movie& mov1,const Movie& mov2){
    if (mov1.name < mov2.name){
        return true;
    }
    return false;
}