#pragma once
#include <string>
#include <vector>
#include <iostream>

using actor =  std::pair<std::string, std::string>;


struct Movie{
    int ID;
    std::string title;
    int publishmentYear;
    int lenght; //[min]
    std::vector<std::string>directors;    
    std::vector<std::string>writers;
    std::vector<actor>cast;

    std::string toString(){
        std::string result;
        result = "ID: " + std::to_string(ID) +
                "Title: " + title + "\n"+
                "Year: " + std::to_string(publishmentYear) + "\n" + 
                "Lenght [min]: " + std::to_string(lenght) + "\n";
        
        result += "Directors:\n"; 
        for (auto &&s : directors){
            result += "\t" + s + "\n";
        }

        result += "Writers:\n";
        for (auto &&s : writers){
            result += "\t" + s + "\n";
        }

        result += "Cast:\n";
        for (auto &&s : cast){
            result += "\tstar: " + s.first + "\tname: " + s.second + "\n";
        }
        return result;
    }
};