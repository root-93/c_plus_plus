#pragma once
#include <string>
#include "CanMaster.hpp"

class Command;


class BaseMenu{
    public:
        virtual             ~BaseMenu(){}
        
        virtual void        add(BaseMenu*) = 0;
        virtual BaseMenu*   operator+(BaseMenu*) = 0;
        virtual void        remove(BaseMenu*) = 0;
        virtual void        removeLast() = 0;
        BaseMenu*const*     getParentPP()const noexcept{return &_pParent;}
        BaseMenu*           getParentP()const noexcept{return _pParent;}
        virtual void        show()const noexcept = 0;
        Command*            pCommand;
        unsigned int        getID()const noexcept{return _ID;}    
        const std::string   getName()const noexcept{return _name;}    
        virtual void        createMenu(MenuCells*) = 0;
        virtual BaseMenu*   getSelectedCellP() = 0;

    protected:
                            BaseMenu(unsigned int ID, std::string name, BaseMenu* pParent = nullptr)
                                : _ID{ID}, _name{name}, _pParent{pParent} {};


        unsigned int        _ID = 0;
        const std::string   _name;
        BaseMenu* const     _pParent = nullptr;     
        
        BaseMenu*           getMainMenuP()const noexcept{
                                return (_pParent == nullptr) ? const_cast<BaseMenu*>(this) : _pParent->getMainMenuP();
                            }
        

};
