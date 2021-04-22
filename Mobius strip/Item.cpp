#include "Item.h"
#include "Shelter.h"

// ３Dでのアイテム
void ItemObj::init()
{
    kami.load("Data\\Objects\\kami.fbx");
    pos = { 0,4,0 };
    scale = { 1,1,1 };
    OBBscale = { 10.0f,10.0f,10.0f };
    Audio::load(6, L"./Data/BGM/get.wav");
    Audio::SetVolume(6, 0.3f);
}

void ItemObj::update(const Camera& camera)
{
    getMouseRay(camera, rayStart, rayEnd);

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        if (ColLineOBB(rayStart, rayEnd, CreateOBB(pos, OBBscale, posture), hitPos))
        {
            if (input::TRG(VK_LBUTTON))
            {
                arr->get_item(static_cast<ITEM_ID>(i));
                Audio::play(6);
            }
        }
        break;
    }
}

void ItemObj::render(const Camera& camera)
{
    Debug->SetString("存在[0]:%d", arr->exist[0]);
    Debug->SetString("存在[1]:%d", arr->exist[1]);
    COLOR color = { 1.0f,1.0f,1.0f,1.0f };
    posture.reset();
    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        if (arr->exist[i])
        {
            SkinnedMeshRender(kami, camera, pos, scale, posture, camera.LightFloamCamera(), color);
        }
        break;
    }
}



// マウスホイールでアイテムを使用する版
void GameItem::init()
{
    arr->init();
}

void GameItem::isChoice()
{
    if (!input::GetWheel())return;

    select = true;

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        if (!arr->exist[i])
        {
            for (auto item : items)
            {
                //アイテムを使用
                //アイテムの種類ごとの処理を書くこと
                switch (use_item(item))
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

}

void GameItem::update()
{
    if (input::GetWheel())
    {
        GameItem::isChoice();
    }
}

void GameItem::draw()
{
    Debug->SetString("真ん中:%d", select);
    for (int i = 0; i < ITEM_MAX; i++)
    {
        if (!arr->exist[i])
        {
            if (select)
            {
                SpriteRender(arr->item_ptr, pos[i].x, pos[i].y, 1, 1, 0, 0, 120, 120, 0, 0, 0, 1, 1, 1, 1);
            }
        }
        break;
    }
}