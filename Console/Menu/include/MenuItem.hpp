#pragma once
#include "LeafMenu.hpp"

class MenuItem : public LeafMenu{
    public:
                                    MenuItem(unsigned int ID, std::string name, BaseMenu* pParent = nullptr)
                                        : LeafMenu(ID, name, pParent){}
                                    ~MenuItem() override {}

        virtual BaseMenu*           getSelectedCellP() override { return nullptr;}
};