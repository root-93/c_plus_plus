#pragma once
#include "BaseMenu.hpp"
#include "Controler.hpp"
#include "CanMaster.hpp"
#include <vector>

#define vec std::vector

class CompositeMenu : public BaseMenu{
                        
    public:
        virtual             ~CompositeMenu() override {for (auto s : _vChilds) { delete s;}};
        
        virtual void        add(BaseMenu *child) override {_vChilds.push_back(child);}
        virtual BaseMenu*   operator+(BaseMenu *child) override{add(child); return static_cast<BaseMenu*>(this);};
        virtual void        remove([[maybe_unused]]BaseMenu *child) override {throw "function not defined";}
        virtual void        removeLast() override {_vChilds.pop_back();}

        virtual void        show()const noexcept override;
        BaseMenu*           getSelectedCellP() override {return *_ppSelectedCell;}      
        virtual void        createMenu([[maybe_unused]]MenuCells *pMenuList) override {}

    protected:
                            CompositeMenu(uint ID, std::string name, BaseMenu* pParent = nullptr)
                                : BaseMenu(ID, name, pParent){}
        
        BaseMenu**          _ppSelectedCell = nullptr;

        BaseMenu**          GetFirstPP() {return &_vChilds.front();}
        BaseMenu**          GetLastPP() {return &_vChilds.back();}
        bool                isSelected(BaseMenu* const cell)const {
                                if(_ppSelectedCell == nullptr)
                                    LOG(this->_name + ": pSelectedCell == nullptr");
                                return *_ppSelectedCell == cell;
                            }
    private:
        vec<BaseMenu*>      _vChilds; 
};