// movies.h

#ifndef  MOVIE_H
#define MOVIE_H

#include <iostream>

using namespace std;

class Movie {
    public:
        Movie();
        Movie(string n, double r);
        ~Movie();
        void printMovie() const;
        string getName() const {return name;};
        double getRating() const {return rating;};

        friend bool operator==(const Movie& mov1,const Movie& mov2);
        friend bool operator>(const Movie& mov1,const Movie& mov2);
        friend bool operator<(const Movie& mov1,const Movie& mov2);

    private:
        string name;
        double rating;
};

#endif