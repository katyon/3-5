#include "menu.h"


/*****************************************/
/*                初期化                 */
/*****************************************/
void Menu::init()
{
    SpriteLoad(menu_ptr, L"Data/Sprite/menu.png");
}

//void ItemList::init()
//{
//    SpriteLoad(item_ptr, L"Data/Sprite/item.png");
//    for (int i = 0; i < ITEM_MAX; i++)
//    {
//        item[i] = ITEM_ID::ID_EMPTY;
//    }
//    reset();
//}


/*****************************************/
/*                 更新                  */
/*****************************************/

void Menu::update()
{
    if (input::TRG(VK_LBUTTON))
    {
        if (Collision::ColRects(20, 80, 600, 900, input::GetMousePos()))
        {
            tab = MenuTab::ItemTab;
        }
        else if (Collision::ColRects(20, 80, 901, 1200, input::GetMousePos()))
        {
            tab = MenuTab::MemoTab;
        }
        else if (Collision::ColRects(20, 80, 1201, 1500, input::GetMousePos()))
        {
            tab = MenuTab::OptionTab;
        }
    }

}


//void SetDraw(ItemList* list, int num,FLOAT2 frame_pos)
//{
//     選択範囲設定
//    if (Collision::ColRects(frame_pos.y, frame_pos.y + 120, frame_pos.x, frame_pos.x + 120, input::GetMousePos()))
//    {
//        list->cursor = num;
//        num = list->item[num];
//        list->SetUp();
//
//        if (input::TRG(VK_LBUTTON))
//        {
//            list->observation = true;
//        }
//    }
//
//    switch (num)
//    {
//    case 0:
//        list->src[num] = { 0,0 };
//        list->pos[num] = { 0,0 };
//        break;
//
//    case 1:
//        list->src[num] = { 0,120 };
//        list->pos[num] = { 120,0 };
//        break;
//    }
//
//}
//
//void ItemList::update()
//{
//    if (Collision::ColRects(320, 640, 320, 640, input::GetMousePos()))
//    {
//        if (canGetItem(ITEM_ID::ID_ITEM0)&&input::TRG(VK_LBUTTON))
//        {
//            item[1] = ITEM_ID::ID_ITEM0;
//            SetDraw(&itemlist, 0, { 120,120 });
//
//        }
//    }
//
//
//
//    
//}

/*****************************************/
/*                  描画                 */
/*****************************************/
void Menu::draw()
{
    switch (tab)
    {
    case MenuTab::ItemTab:
        SpriteRender(menu_ptr, 0, 0, 1, 1, 0, 0, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
        break;

    case MenuTab::MemoTab:
        SpriteRender(menu_ptr, 0, 0, 1, 1, 0, 1080, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
        break;
        
    case MenuTab::OptionTab:
        SpriteRender(menu_ptr, 0, 0, 1, 1, 0, 2160, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
        break;
    }
}

//void ItemList::draw(Menu* menu)
//{
//    switch (menu->tab)
//    {
//    case MenuTab::ItemTab:
//        SpriteRender(item_ptr,
//            320,320,
//            1, 1,
//            120,120,
//            120, 120,
//            0, 0,
//            0,
//            1, 1, 1, 1
//        );
//
//
//        for (int i = 0; i < ITEM_MAX; ++i)
//        {
//            if (item[i] == ITEM_ID::ID_EMPTY) continue;
//
//                SpriteRender(item_ptr,
//                    pos[i].x, pos[i].y,
//                    1, 1,
//                    src[i].x, src[i].y,
//                    120,120,
//                    0, 0,
//                    0,
//                    1, 1, 1, 1
//                );
//        }
//        break;
//
//    case MenuTab::MemoTab:
//        break;
//
//    case MenuTab::OptionTab:
//        break;
//    }
//        
//}

/*****************************************/
/*                  終了                 */
/*****************************************/
void Menu::uninit()
{

}
