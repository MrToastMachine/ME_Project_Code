// tests.cpp

#include <set>
#include <vector>
#include <iostream>
#include <iomanip>

#include "movies.h"

using namespace std;

void testMovieOrder(){
    Movie m1("Batman", 6.5);
    Movie m2("James Bond", 6.5);
    Movie m3("Zethora", 6.5);

    cout<<"All Movies..."<<endl;
    cout<<"m1: ";
    m1.printMovie();
    cout<<"m2: ";
    m2.printMovie();
    cout<<"m3: ";
    m3.printMovie();

    bool a = m2 > m1;
    bool b = m3 > m1;
    bool c = m2 > m3;

    cout<<"m2 > m1 : ";
    if(a){cout<<"True"<<endl;}
    else{cout<<"False"<<endl;}

    cout<<"m3 > m1 : ";
    if(b){cout<<"True"<<endl;}
    else{cout<<"False"<<endl;}

    cout<<"m2 > m3 : ";
    if(c){cout<<"True"<<endl;}
    else{cout<<"False"<<endl;}
}

void testSetStorage(){
    Movie m1("Batman", 6.5);
    Movie m2("James Bond", 3.8);
    Movie m3("Zethora", 9.8);
    Movie m4("LandMine", 9.1);
    Movie m5("Twilight", 1.1);
    Movie m6("Garg", 6.3);

    set<Movie> movies{m1,m2,m3,m4};

    cout<<"before add"<<endl;
    for (Movie item: movies){
        item.printMovie();
    } cout<<endl;

    movies.insert(m5);
    movies.insert(m6);

    cout<<"after add"<<endl;
    for (Movie item: movies){
        item.printMovie();
    } cout<<endl;

}

void argTesting(set<Movie> mSet){
    cout<<"Printing all movies Alphabetically"<<endl;

    cout<<"All Done"<<endl;
}

void prefixTesting(){
    string s1 = "the land before time";
    string s2 = "this is the place";
    string s3 = "there will be bloodmake";
    string s4 = "the bingo show";

    set<string> strs{s1,s2,s3,s4};

    string sub;
    string prefix = "the";

    cout<<"Checking for: "<<prefix<<endl;
    for (string s: strs){
        sub = s.substr(0,3);
        if (sub == prefix){
            cout<<s<<endl;
        }
    }


}

void doublePrecisionPrint(){
    Movie m1("Batman", 6.5);
    Movie m2("James Bond", 3.8);
    Movie m3("Zethora", 7);
    Movie m4("LandMine", 9.1);

    set<Movie> movies{m1,m2,m3,m4};

    cout<<"Rating: "<<setprecision(1)<<fixed<<m3.getRating()<<endl;
}

int main(int argc, char** argv)
{
    // testMovieOrder();
    // testSetStorage();

    // testing argument types : toggle true/false
    if (false){
        Movie m1("Batman", 6.5);
        Movie m2("James Bond", 3.8);
        Movie m3("Zethora", 9.8);
        Movie m4("LandMine", 9.1);
        set<Movie> movs{m1,m2,m3,m4};
        argTesting(movs);
    }

    // prefixTesting();
    doublePrecisionPrint();


    if (argc < 2){
        cout<<"Not enough args"<<endl;
        return 0;
    }

    vector<string> prefixes;

    cout<<"All arguments: "<<endl;
    // argc == number of arguments including file being run
    for (int i = 1; i < argc; i++){
        cout<<i<<" : "<<argv[i]<<endl;
        prefixes.push_back(argv[i]);
    }

    for (string s: prefixes){
        cout<<"Prefix: "<<s<<endl;
    }



    return 0;
}
