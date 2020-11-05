#pragma once
#include <vector>
#include "SubMenu.hpp"
#include "MenuContent.hpp"
#include "Command.hpp"


class Menu{
    public:
                    Menu(MenuContent &&mC, std::string name = "Main Menu")
                        : subMenu{0, name, nullptr, &_actualMenu}  {
                            subMenu.createMenu(mC.pMenuList.front());
                        }

        void        show()const {_actualMenu->show();}  
        void        execute(char key) {_actualMenu->pCommand->execute(key);}
    private:
        SubMenu    subMenu;
        BaseMenu*   _actualMenu = &subMenu;

        void    createMenu(MenuCells* pMenuList);

};