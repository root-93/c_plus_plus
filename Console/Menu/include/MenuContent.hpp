#pragma once

#define COMPOSITE_MENU true
#define MENU_CELL false

struct MenuContent{

    std::vector<MenuCells*> pMenuList{
        &mainMenuList,
            &canUtils,
            &somethingElse, 
                &thirdLevel
    };
    
    MenuCells mainMenuList{
        Cell("Can Utils", COMPOSITE_MENU),
        Cell("Something else", COMPOSITE_MENU),
        Cell("Nothing", MENU_CELL),
        Cell("Exit", MENU_CELL)
    };
    
    MenuCells canUtils {
        Cell("Candump", MENU_CELL),
        Cell("Cangen", MENU_CELL),
        Cell("Canplayer", MENU_CELL),
        Cell("Cansend", MENU_CELL),
        Cell("Cansniffer", MENU_CELL),
        Cell("Back", MENU_CELL)
    };

    MenuCells somethingElse {
        Cell("cell 1", MENU_CELL),
        Cell("Third Level", COMPOSITE_MENU),
        Cell("cell 3", MENU_CELL),
        Cell("cell 4", MENU_CELL),
        Cell("cell 5", MENU_CELL),
        Cell("Back", MENU_CELL)
    };
    
    MenuCells thirdLevel {
        Cell("cell 1", MENU_CELL),
        Cell("cell 2", MENU_CELL),
        Cell("Back", MENU_CELL)
    };
};
