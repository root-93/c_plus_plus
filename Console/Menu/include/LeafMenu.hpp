#pragma once
#include <string>
#include "BaseMenu.hpp"
#include <exception>
#include <stdexcept>

class LeafMenu : public BaseMenu{
    public:
        virtual             ~LeafMenu() override {}
        
        virtual void        add(BaseMenu*) override { throw std::bad_alloc();}
        virtual BaseMenu*   operator+(BaseMenu*) override {throw std::bad_alloc();}
        virtual void        remove(BaseMenu*) override {throw std::logic_error("LeafMenu class doesn't contain child elements");}
        virtual void        removeLast() override {throw std::logic_error("LeafMenu class doesn't contain child elements");}
        virtual void        show()const noexcept override {}
        virtual void        createMenu([[maybe_unused]]MenuCells *pMenuList) override {};
    
    protected:
                            LeafMenu(unsigned int ID, std::string name, BaseMenu* pParent = nullptr)
                                :BaseMenu(ID, name, pParent) {}

};