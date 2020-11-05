#include "../include/SubMenu.hpp"
#include "../include/MenuItem.hpp"
#include "../include/CommandKey.hpp"
#include "../include/CommandDefault.hpp"
#include "../include/CommandBack.hpp"

class BaseMenu;
using CM = CompositeMenu;

using namespace std;


void SubMenu::createMenu(MenuCells* pMenuList){
    unsigned int ID = 1;
    for (auto &&s : *pMenuList){
        if(s.second){
            add(new SubMenu(ID++, s.first, this, _ppActualMenu));
            
            if(dynamic_cast<MenuCells*>(pMenuList + 1))
                (*this->GetLastPP())->createMenu(++pMenuList); //recurrence
            else
                throw "Submenu is not defined";
        }
        else{
            auto cell = new MenuItem(ID++, s.first, this);
            cell->pCommand = new CommandDefault(this);
            add(cell);
        }
    }
    
    // it sucks, it need to be improved
    delete (*GetLastPP())->pCommand;
    (*GetLastPP())->pCommand = new CommandBack(this);
    
    _ppSelectedCell = this->GetFirstPP();
}



void SubMenu::move(char key) {
    switch (key){
        case kbDown:
            if(_ppSelectedCell != GetLastPP())
                _ppSelectedCell++;
            break;
        case kbUp:
            if(_ppSelectedCell != GetFirstPP())
                _ppSelectedCell--;
            break;
        case kbEscape:
        case kbBackspace:
        case kbLeft:
            if(*getParentPP() != nullptr){
                *_ppActualMenu = *getParentPP();         
            }
            break;
        case kbEnter:
        case kbRight:
            if(dynamic_cast<CM*>(*_ppSelectedCell))
                *_ppActualMenu = *_ppSelectedCell;
            else
                (*_ppSelectedCell)->pCommand->execute();
            break;
        default:
            break;
    }
}

