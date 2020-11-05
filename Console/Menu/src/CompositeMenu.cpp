#include "../include/CompositeMenu.hpp"
#include <ncurses.h>

using CM = CompositeMenu;
using namespace std;

void CompositeMenu::show()const noexcept{
    clear();
    
    if(has_colors()){
        start_color();
        init_pair(1,COLOR_BLACK, COLOR_GREEN);
        attron(COLOR_PAIR(1));
        
        printw("%s", _name.c_str());
        attroff(COLOR_PAIR(1));
    }
    else{
        printw("Twoja konsola nie obsługuje kolorów :(");
    }

    printw("\n\n");
    
    for (auto &i : _vChilds){
        if(isSelected(i))
            attron(A_REVERSE);
        printw("%d: %s\n", i->getID(), i->getName().c_str());

        attroff(A_REVERSE);
    }
}