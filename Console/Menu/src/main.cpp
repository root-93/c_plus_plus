#include <ncurses.h>
#include <stdlib.h>
#include "../include/Menu.hpp"
#include "../include/MenuContent.hpp"

using namespace std;


int main([[maybe_unused]]int argc,[[maybe_unused]] char *argv[]) { 
    initscr();
    keypad(stdscr, true);

    MenuContent mC;
    Menu menu(std::move(mC));

    char kbCode;
    while (true){
        menu.show();
        kbCode = getch();
        menu.execute(kbCode);

        if(kbCode == 'e')
            break;
    }

    printw("\nbye");
    getch();
    endwin();
}