#include <iostream>

#include "Movie.hpp"
#include "XmlSerialize.hpp"

using namespace std;

int main() {
    cout << "Serailize example" << endl;
    cout << "Create some mvies" << endl;

    Movie forest {
        1221, 
        "Forest Gump", 
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
        "The Shawshank Redemption", 
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
        "Sherlock Holmes", 
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
    
    cout << "before serialization\n" << forest.toString(); 
    saveToXml(forest, "movies");
    //saveToXml(shawshank, "movies");
    //saveToXml(holmes, "movies");

    Movie restoredForest;
    //Movie restoredShawshank;
    //Movie restoredHolmes;

    restoreFromXml(restoredForest, "movies");
    cout << "after serialization\n" << restoredForest.toString(); 
}