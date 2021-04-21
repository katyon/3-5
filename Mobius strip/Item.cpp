#include "Item.h"
#include "Shelter.h"

void ItemObj::init()
{
    kami.load("Data\\Objects\\kami.fbx");
    pos = { 0,4,0 };
    scale = { 1,1,1 };
    OBBscale = { 10.0f,10.0f,10.0f };
}

void ItemObj::update(const Camera& camera)
{
    getMouseRay(camera, rayStart, rayEnd);

    if (ColLineOBB(rayStart, rayEnd, CreateOBB(pos, OBBscale, posture), hitPos))
    {
        if (input::TRG(VK_LBUTTON))
        {
            get_item(ITEM_ID::ID_ITEM1);
        }
    }
}

void ItemObj::render(const Camera& camera)
{
    COLOR color = { 1.0f,1.0f,1.0f,1.0f };
    posture.reset();
    if (exist[0])
    {
        SkinnedMeshRender(kami, camera, pos, scale, posture, camera.LightFloamCamera(), color);
    }
}

//GameItem::GameItem()
//{
//    kami.load("Data\\Objects\\kami.fbx");
//}
//
//void GameItem::init()
//{
//    scale = ScalarToFloat3(0.165f);
//    OBBscale = ScalarToFloat3(2.5f);
//}
//
//void GameItem::isChoice()
//{
//    if (!input::GetWheel())return;
//
//    select = true;
//
//    for (auto i : items)
//    {
//        if (ColRects(pos[i].y, pos[i].y + 120.0f, pos[i].x, pos[i].x + 120.0f, input::GetMousePos()))
//        {
//            //アイテムを使用
//            //アイテムの種類ごとの処理を書くこと
//            switch (use_item(i))
//            {
//            case ID_ITEM1:
//                break;
//            case ID_ITEM2:
//                break;
//            case ID_ITEM3:
//                break;
//            case ID_ITEM4:
//                break;
//            case ID_EMPTY:
//                break;
//            }
//        }
//    }
//}
//
//
//
//
//// マウスホイールでアイテムを使用する版
//void GameItem::update()
//{
//    GameItem::isChoice();
//
//
//
//}
//
//
//void GameItem::draw()
//{
//    if (select)
//    {
//        SpriteRender(item_ptr, 100, 100, 1, 1, 0, 0, 120, 120, 0, 0, 0, 1, 1, 1, 1);
//    }
//}