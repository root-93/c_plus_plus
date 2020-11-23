#include <iostream>
#include <vector>
#include "Movie.hpp"
#include "XmlSerialize.hpp"

using namespace std;

int main() {
    cout << "Serailize example" << endl;
    cout << "Creating some mvies..." << endl;

    Movie forest {
        1221, 
        std::string("Forest Gump"), 
        1994,
        202,
        {   "Robert Zemeckis" },
        {   "Winston Groom",
            "Eric Roth"},
        {
            {"Tom Hamks", "Forrest Gump"},
            {"Sally Field", "Mrs Gump"},
            {"Robin Wright", "Jenny Curran"},
            {"Mykelti Williamson", "Bubba Blue"}
        }
    };

    Movie shawshank {
        964, 
        std::string("The Shawshank Redemption"), 
        1994,
        142,
        {   "Frank Darabont" },
        {   "Stephen King",
            "Frank Darabont"},
        {
            {"Tim Robbins", "Andy Dufresne"},
            {"Morgan Freeman", "Ellis 'Red' Redding"},
            {"Bob Gunton", "Warden Norton"}
        }
    };

    Movie holmes {
        1003, 
        std::string("Sherlock Holmes"), 
        2009,
        128,
        {   "Guy Ritchie" },
        {   "Michael Robert Johnson",
            "Anthony Peckham"},
        {
            {"Robert Downey Jr.", "Sherlock Holmes"},
            {"Jude Law", "Dr. John Watson"},
            {"Rachel McAdams", "Irene Adler"},
            {"Mark Strong", "Lord Henry Blackwood"}
        }
    };
    
    vector<Movie> Movies {
        forest,
        shawshank,
        holmes
    };

    cout << "before serialization\n" 
        << forest.toString()
        << shawshank.toString()
        << holmes.toString();
    // xml::save(forest, "movies.xml");
    // xml::save(shawshank, "movies");
    // xml::save(holmes, "movies");
    xml::save(Movies, "movies.xml");


    vector<Movie> restoredMovies;
    xml::restore(restoredMovies, "movies.xml");
    cout << "\n\nAfter serialization\n";
    for (auto &&s : restoredMovies){
        cout << s.toString();
    }
    
    //Movie restoredForest;
    //Movie restoredShawshank;
    //Movie restoredHolmes;

    // xml::restore(restoredForest, "movies.xml");
    // cout << "after serialization\n" << restoredForest.toString(); 
}   