#pragma once
#include <vector>
#include <iostream>
using Cell = std::pair<const char*, bool>;
using MenuCells = std::vector<Cell>;

#define LOG(msg) errorLog(__FUNCTION__, msg)

inline void errorLog(const char* func, const std::string& msg){
    //printw("[%s] %s", func, msg.c_str());
    std::cerr << "[" << func << "] " << msg << std::endl;   
}