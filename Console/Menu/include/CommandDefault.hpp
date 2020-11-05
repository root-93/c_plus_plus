#pragma once
#include "Command.hpp"
#include "MenuItem.hpp"
#include "SubMenu.hpp"

class CommandDefault : public Command {
    public:
                        CommandDefault(SubMenu* pParent) : _pParent{pParent} {}
        void            execute()const override {
                            
                        }

        void            execute([[maybe_unused]]char key)const override {}

    private:
        SubMenu*        _pParent = nullptr;
};