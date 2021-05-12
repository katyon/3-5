#include "Item.h"
#include "Shelter.h"


// 3Dでのアイテム
void ItemObj::init()
{
    arr->init();

    /* メモ */
    item3D.itemSpec[0].model.load("Data\\Objects\\kami.fbx");
    item3D.itemSpec[0].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[0].scale = { 0.5f,1.0f,0.7f };
    itemSpec[0].isConsumed = false;

    /* 錘 */
    item3D.itemSpec[1].model.load("Data\\Objects\\omori.fbx");
    item3D.itemSpec[1].pos = { 0.0f,10.0f,0.0f };
    item3D.itemSpec[1].scale = { 0.2f,0.2f,0.2f };
    itemSpec[1].isConsumed = true;

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        item3D.itemSpec[i].exist = true;
    }

    OBBscale = { 10.0f,10.0f,10.0f };
    Audio::load(6, L"./Data/BGM/get.wav");
    Audio::SetVolume(6, 0.3f);
}

void ItemObj::update(const Camera& camera)
{
    getMouseRay(camera, rayStart, rayEnd);

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        if (ColLineOBB(rayStart, rayEnd, CreateOBB(item3D.itemSpec[i].pos, OBBscale, posture[i]), hitPos))
        {
            if (input::TRG(VK_LBUTTON))
            {
                arr->get_item(static_cast<ITEM_ID>(i));
                item3D.itemSpec[i].exist = false;
                M_Item->item2D.itemSpec[i].exist = true;
                Audio::play(6);
            }
        }
    }
}

void ItemObj::render(const Camera& camera)
{
    COLOR color = { 1.0f,1.0f,1.0f,1.0f };
    Debug->Get()->SetString("存在[0]:%d", item3D.itemSpec[0].exist);
    Debug->Get()->SetString("存在[1]:%d", item3D.itemSpec[1].exist);

    for (int i=0;i<arr->ITEM_MAX;i++)
    {
        if (item3D.itemSpec[i].exist)
        {
            posture[i].reset();
            posture[0].RotationYaw(toRadian(-90.0f));
            SkinnedMeshRender(item3D.itemSpec[i].model, camera, item3D.itemSpec[i].pos, item3D.itemSpec[i].scale, posture[i], camera.LightFloamCamera(), color);
        }
    }
}


//
//// 2Dでのアイテム(ゲーム画面表示・使用)
//void GameItem::init()
//{
//
//    arr->init();
//}
//
//void GameItem::isChoice()
//{
//    if (!input::GetWheel())return;
//
//    select = true;
//
//    for (int i = 0; i < arr->ITEM_MAX; i++)
//    {
//        if (!arr->exist[i])
//        {
//            for (auto item : items)
//            {
//                //アイテムを使用
//                //アイテムの種類ごとの処理を書くこと
//                switch (use_item(item))
//                {
//                case ID_MEMO:
//                    break;
//                case ID_OMORI:
//                    break;
//                case ID_ITEM3:
//                    break;
//                case ID_ITEM4:
//                    break;
//                case ID_EMPTY:
//                    break;
//                }
//            }
//        }
//    }
//
//}
//
//void GameItem::update()
//{
//
//    if (input::GetWheel())
//    {
//        GameItem::isChoice();
//    }
//}
//
//void GameItem::draw()
//{
//    Debug->SetString("真ん中:%d", select);
//    for (int i = 0; i < ITEM_MAX; i++)
//    {
//        if (!arr->exist[i])
//        {
//            if (select)
//            {
//                SpriteRender(arr->ptr, pos.x, pos.y, 1, 1, 0, 0, 120, 120, 0, 0, 0, 1, 1, 1, 1);
//            }
//        }
//        break;
//    }
//}