#pragma once
#include "Command.hpp"
#include "MenuItem.hpp"
#include "SubMenu.hpp"

class CommandBack : public Command {
    public:
                        CommandBack(SubMenu* pParent) : _pParentMenu{pParent} {}
        void            execute()const override {
                            if(_pParentMenu->getParentP() == nullptr)
                                std::exit(EXIT_SUCCESS);
                            else
                                _pParentMenu->pCommand->execute(SubMenu::Key::kbEscape);
                        }

        void            execute([[maybe_unused]] char key)const override {}

    private:
        SubMenu*        _pParentMenu = nullptr;
};