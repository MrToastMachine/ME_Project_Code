// Spring'22
// Instructor: Diba Mirza
// Student name: Alex O'Mahony

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
using namespace std;

#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

void printAlphabetical(set<Movie> movSet){
    for (Movie mov: movSet){
        mov.printMovie();
    } 
}

set<Movie> getPrefixMovies(set<Movie> movSet, string prefix){

    set<Movie> prefixSet;
    int prefixLen = prefix.length();

    for (Movie m: movSet){
        if (m.getName().substr(0,prefixLen) == prefix){
            prefixSet.insert(m);
        }
    }
    return prefixSet;
}

Movie rankMovies(set<Movie> movies){
    vector<Movie> movieVect;
    movieVect.assign(movies.begin(), movies.end());

    sort(movieVect.begin(), movieVect.end(), [](const Movie& m1, const Movie& m2) {
        if (m1.getRating() == m2.getRating()){
            return m1.getName() < m2.getName();
        }
        return m1.getRating() > m2.getRating();
    });

    for(Movie m : movieVect){
        m.printMovie();
    } cout<<endl;

    return movieVect[0];

}

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " filename prefix1 prefix2 ... prefix n " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    set<Movie> allMovies;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            
            Movie mov(movieName, movieRating);
            allMovies.insert(mov);
    }

    movieFile.close();

    if (argc == 2){
        //print all the movies in ascending alphabetical order of movie names
        printAlphabetical(allMovies);
        return 0;
    }

    // ----------- PART TWO STARTS HERE ---------
    
    vector<string> prefixes;
    vector<Movie> topRated;

    for (int i = 2; i < argc; i++){
        prefixes.push_back(argv[i]);
    }

    for (string p: prefixes){
        set<Movie> prefixSet = getPrefixMovies(allMovies, p);

        if (!prefixSet.empty()){
            topRated.push_back(rankMovies(prefixSet));
        } else {   
            cout<<"No movies found with prefix "<<p<<endl<<endl;
        }
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    // cout << "No movies found with prefix "<<"<replace with prefix>" << endl << endl;

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    
    for (int i = 0; i < topRated.size(); i++){
        cout<<"Best movie with prefix ";
        cout<<prefixes[i]<<" is: "<<topRated[i].getName();
        cout<<" with rating "<<setprecision(1)<<fixed<<topRated[i].getRating()<<endl;
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/
/*
    3a : Time Complexity
    My code for section 2 begins at line 103 which is a for loop that iterates over
    all 'm' prefixes given in the command line.
    Inside this for loop we first call the custom function 'getPrefixMovies()'
     -> This function overall has a time complexity of around '5n+5'
        This comes from the 5 constant time operations on lines 30, 31 and 38
        Line 31 contains a variable creation, and assignment and a vector operation so counts as 3

        The for loop in this function loops through all 'n' given movies
         -> for each n it checks if the name contains the prefix. When looking into the substr()
            method the documentation says it has a linear time complexity[1]. But we do not know
            what length the prefix will have so I estimated around 3. This does not really affect the
            end product so this assumption should be fine. This along with the comparison and insert
            adds up to 5 which is multiplied by n
        
        This in total results in a complexity of 5n + 5

    The next part of the code checks if the prefix set of movies is empty, which we assume is always false
    with 'k' movies with each prefix.
    Then Line 107 calls the vector append 'push_back' which get the value from our custom function rankMovies()
    This Function has an overall runtime complexity of '1 + k + klog(k)'
     -> The 'assign' function has a time complexity of O(N)[2] where in our case N = k.
        Next we call the built-in std::sort() function which has a time complexity of O(Nlog(N))[3] where N = k
        here again.
        Adding these together along with the other constant time operations results in
        Time Complexity = 1 + k + klog(k)
    
    Combining all of the above results in time complexity equal to 
        m * ((5n + 5) + (1 + k + klog(k)))
      = O(m) * ( O(n) + O(klog(k)) )
      = O( mn + klog(k) ) 

    
    3b : Space Complexity
    > set space complexity : O(n)
    > vector space complexity : O(n)

    Again, looping over all 'm' prefixes, we call the functions getPrefixMovies and rankMovies
    For getPrefixMovies, we have a space complexity of S(n,k) = n + k + 4
     -> As input memory we have set 'movies' of size n, and string 'prefix' of undetermined size.
        I took prefix to have a size of ~3 for the sake of this analysis.
        The Non-input memory used is the set 'prefixMovies' which is initialized as empty but will
        come to have size 'k'.
        We also have a fixed size int 'prefixLen'
        Combining all of these we are left with S(n,k) = n + k + 4

    For rankMovies, I came to a space complexity of 2k
     -> As for input memory, we input the set 'movies' of size 'k'
        For Non-input memory we create a vector 'movieVect' which is also size 'k'
        As far as I know, the rest of the lines in the function all have a constant 
        space complexity as no new variables are created or space allocated
        Therefore, space complexity for rankMovies = S(k) = 2k

    This results in a Space complexity of
        m * ((n + k + 4) + (2k))
        S(n,m,k) = m*(n + 2k +4)

    3c: Analysis
    When designing my algorithms I aimed for a low time complexity, however there are likely 
    much more efficient algorithms than the one I designed.

    I believe I saved space also by utilizing built in functions such as std::assign and std::sort
    and altering their functionality to suit my own needs.

    For example, running my program through valgrind with file input_100_random.csv and prefix the
    results in values n = 100, m = 1, k = 11.

    The total heap summary for this run was 516 allocations and 516 frees, using ~106,000 bytes
*/
// REFERENCES
// [1] https://www.cplusplus.com/reference/string/string/substr/
// [2] https://www.cplusplus.com/reference/vector/vector/assign/
// [3] https://en.cppreference.com/w/cpp/algorithm/sort

bool parseLine(string &line, string &movieName, double &movieRating) {
    if (line.length() <= 0) return false;
    string tempRating = "";

    bool flag = false;
    movieName = tempRating = "", movieRating = 0.0, flag = false;

    for (int i = 0; i < line.length(); i++){
        if(flag) tempRating += line[i];
        else if(line[i]==','&& line[0]!='"') flag = true;
        else {
            if(i==0 && line[0]=='"') continue;
            if(line[i]=='"'){ i++; flag=true; continue;}
            movieName += line[i];
        }
    }
    
    movieRating = stod(tempRating);
    return true;
}
