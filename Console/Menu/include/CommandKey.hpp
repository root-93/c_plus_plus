#pragma once
#include "Command.hpp"

class SubMenu;

class CommandKey : public Command {
    public:
                    CommandKey(SubMenu *pParent) : _pParent{pParent} {}
        void        execute()const override{}
        void        execute(char key)const override;

    private:
        SubMenu     *_pParent = nullptr;    
};

