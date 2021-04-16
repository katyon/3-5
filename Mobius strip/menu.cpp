#include "menu.h"

void ItemArr::init()
{
    SpriteLoad(item_ptr, L"Data/Sprite/item.png");
}

void Menu::init()
{
    SpriteLoad(menu_ptr, L"Data/Sprite/menu.png");

}






void ItemMenu::update()
{
    
}

void Menu::update()
{
 
}

void ItemMenu::draw()
{
    SpriteRender(item_ptr,
        0, 0,
        1, 1,
        0, 0,
        120, 120,
        0,0,
        0,
        1, 1, 1, 1
    );
}

void Menu::draw()
{
    switch (tab)
    {
    case MenuTab::Item:
    SpriteRender(menu_ptr,
        0,0,
        1, 1,
        0, 0,
        1920, 1080,
        0, 0,
        0,
        1, 1, 1, 1);

    item_menu.draw();
    break;

    //case MenuTab::Memo:
    //SpriteRender(menu_ptr,
    //    0, 0,
    //    1, 1,
    //    0, 0,
    //    1920, 1080,
    //    0, 0,
    //    0,
    //    1, 1, 1, 1);
    //break;


    //default:
    //SpriteRender(menu_ptr,
    //    0, 0,
    //    1, 1,
    //    0, 0,
    //    1920, 1080,
    //    0, 0,
    //    0,
    //    1, 1, 1, 1);
    //break;
    }
}

void Menu::uninit()
{

}