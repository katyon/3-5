#include "Item.h"

void GameItem::init()
{


}

void GameItem::isChoice()
{
    if (!input::GetWheel())return;

    select = true;

    for (auto i : items)
    {
        if (ColRects(pos[i].y, pos[i].y + 120.0f, pos[i].x, pos[i].x + 120.0f, input::GetMousePos()))
        {
            //アイテムを使用
            //アイテムの種類ごとの処理を書くこと
            switch (use_item(i))
            {
            case ID_ITEM1:
                break;
            case ID_ITEM2:
                break;
            case ID_ITEM3:
                break;
            case ID_ITEM4:
                break;
            case ID_EMPTY:
                break;
            }
        }
    }
}




// マウスホイールでアイテムを使用する版
void GameItem::update()
{
    GameItem::isChoice();



}


void GameItem::draw()
{

}