#include "menu.h"

void Item::init()
{
    SpriteLoad(4, L"Data/Sprite/item.png");
    for (int i = 0; i < 5; i++)
    {
        // item class ‚É‚Ð‚Â‚æ‚¤‚Èî•ñŽ‚½‚¹‚ÄAlist‚Éptr“n‚·
    }
}

void Menu::init()
{
    pos = { 0,0 };
    scale = { 1,1 };
    SpriteLoad(1, L"Data/Sprite/menu_item.png");
    SpriteLoad(2, L"Data/Sprite/menu_memo.png");
    SpriteLoad(3, L"Data/Sprite/menu_exit.png");
}

void Menu::update()
{
    if (input::GetMousePos().x > 600 && input::GetMousePos().x < 900 && input::GetMousePos().y <100 && input::TRG(VK_LBUTTON))
    {
        tab = MenuTab::Item;
   }
    else if (input::GetMousePos().x > 900 && input::GetMousePos().x < 1200 && input::GetMousePos().y < 100 && input::TRG(VK_LBUTTON))
    {
        tab = MenuTab::Memo;
    }

}

void Menu::draw()
{
    switch (tab)
    {
    case MenuTab::Item:
    SpriteRender(1,
        pos.x, pos.y,
        scale.x, scale.y,
        0, 0,
        1920, 1080,
        0, 0,
        0,
        1, 1, 1, 1);
        break;

    case MenuTab::Memo:
    SpriteRender(2,
        pos.x, pos.y,
        scale.x, scale.y,
        0, 0,
        1920, 1080,
        0, 0,
        0,
        1, 1, 1, 1);
    break;


    default:
    SpriteRender(3,
        pos.x, pos.y,
        scale.x, scale.y,
        0, 0,
        1920, 1080,
        0, 0,
        0,
        1, 1, 1, 1);
    break;
    }
}

void Menu::uninit()
{

}