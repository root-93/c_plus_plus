#pragma once
#include "CompositeMenu.hpp"
#include "CommandKey.hpp"

#define vec std::vector

class SubMenu : public CompositeMenu{
    public:
            SubMenu(uint ID, std::string name, BaseMenu* pParent = nullptr, BaseMenu** ppActualMenu = nullptr)
                : CompositeMenu(ID, name, pParent), _ppActualMenu{ppActualMenu} {
                    pCommand = new CommandKey(this);
                }
            
            ~SubMenu() override {};

    void    createMenu(MenuCells* pMenuList);
    void    move(char key);

    enum Key{
        kbDown = 2,
        kbUp,
        kbLeft,
        kbRight,
        kbBackspace = 7,
        kbEnter = 10,
        kbEscape = 27
    };

    private:
        BaseMenu** _ppActualMenu = nullptr;
};