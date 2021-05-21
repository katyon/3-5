#include "Item.h"
#include "Shelter.h"
#include "ButtonPush.h"

// 3Dでのアイテム
void ItemObj::init()
{
    arr->init();
    
    /* ID_ESC1 */
    item3D.itemSpec[0].model.load("Data/Objects/esc1.fbx");
    item3D.itemSpec[0].pos = { 0.0f,10.0f,0.0f };
    item3D.itemSpec[0].scale = { 0.05f,0.05f,0.05f };
    item3D.itemSpec[0].exist = true;

    /* ID_ESC2 */
    item3D.itemSpec[1].model.load("Data/Objects/esc2.fbx");
    item3D.itemSpec[1].pos = { 0.0f,10.0f,0.0f };
    item3D.itemSpec[1].scale = { 0.05f,0.05f,0.05f };
    item3D.itemSpec[1].exist = false;

    /* 石盤のヒント1 */
    item3D.itemSpec[2].model.load("Data/Objects/kami.fbx");
    item3D.itemSpec[2].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[2].scale = { 0.5f,1.0f,0.7f };
    item3D.itemSpec[2].exist = false;

    /* 石盤のヒント2 */
    item3D.itemSpec[3].model.load("Data/Objects/kami.fbx");
    item3D.itemSpec[3].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[3].scale = { 0.5f,1.0f,0.7f };
    item3D.itemSpec[3].exist = false;

    /* 水道管のヒント */
    item3D.itemSpec[4].model.load("Data/Objects/omori.fbx");
    item3D.itemSpec[4].pos = { 0.0f,10.0f,0.0f };
    item3D.itemSpec[4].scale = { 0.05f,0.05f,0.05f };
    item3D.itemSpec[4].exist = false;

    /* 天秤のヒント1 */
    item3D.itemSpec[5].model.load("Data/Objects/balance1.fbx");
    item3D.itemSpec[5].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[5].scale = { 0.5f,1.0f,0.7f };
    item3D.itemSpec[5].exist = true;

    /* 天秤のヒント2 */
    item3D.itemSpec[6].model.load("Data/Objects/balance2.fbx");
    item3D.itemSpec[6].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[6].scale = { 0.5f,1.0f,0.7f };
    item3D.itemSpec[6].exist = false;

    /* 天秤のヒント3 */
    item3D.itemSpec[7].model.load("Data/Objects/balance3.fbx");
    item3D.itemSpec[7].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[7].scale = { 0.5f,1.0f,0.7f };
    item3D.itemSpec[7].exist = false;

    /* 金庫のヒント */
    item3D.itemSpec[8].model.load("Data/Objects/balance3.fbx");
    item3D.itemSpec[8].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[8].scale = { 0.5f,1.0f,0.7f };
    item3D.itemSpec[8].exist = false;

    /* 錘 */
    item3D.itemSpec[9].model.load("Data/Objects/omori.fbx");
    item3D.itemSpec[9].pos = { 0.0f,10.0f,0.0f };
    item3D.itemSpec[9].scale = { 0.05f,0.05f,0.05f };
    item3D.itemSpec[9].exist = true;

    /* 鍵 */
    item3D.itemSpec[10].model.load("Data/Objects/balance3.fbx");
    item3D.itemSpec[10].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[10].scale = { 0.5f,1.0f,0.7f };
    item3D.itemSpec[10].exist = false;

    OBBscale = { 10.0f,10.0f,10.0f };
    Audio::load(6, L"./Data/BGM/get.wav");
    Audio::SetVolume(6, 0.3f);

    G_Item->count[0] = false;
    G_Item->count[1] = false;
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
                if (item3D.itemSpec[i].exist)
                {
                    arr->get_item(static_cast<SPEC::ITEM_ID>(i));
                    item3D.itemSpec[i].exist = false;

                    switch (i)
                    {
                    case 0:
                    case 5:
                        item3D.itemSpec[2].exist = true;
                        break;

                    case 9:
                        G_Item->count[0] = true;
                        item3D.itemSpec[10].exist = true;
                        break;

                    case 10:
                        G_Item->count[1] = true;
                        break;

                    }
                }
            }
        }
    }
}

void ItemObj::render(const Camera& camera)
{
    COLOR color = { 1.0f,1.0f,1.0f,1.0f };

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        posture[i].reset();
        posture[0].RotationYaw(toRadian(-90.0f));
        if (item3D.itemSpec[i].exist)
        {
            /* Room1とRoom2の場合で分ける */
            SkinnedMeshRender(item3D.itemSpec[i].model, camera, item3D.itemSpec[i].pos, item3D.itemSpec[i].scale, posture[i], camera.LightFloamCamera(), color);
        }
    }
}

void ItemObj::uninit()
{
}

// 2Dでのアイテム(ゲーム画面表示・使用)
void GameItem::init()
{
    arr->init();
    M_Item->init();
    SpriteLoad(12, L"Data/Sprite/cursor.png");

    pos = { 0.0f,290.0f };
}

// 消費系アイテムの処理 
void GameItem::isChoice()
{
    if (input::GetWheel() > 0) { selectNum = 1; }
    if (input::GetWheel() < 0) { selectNum = 2; }

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        switch (arr->items[i])
        {
            /* 錘 */
        case SPEC::ITEM_ID::ID_Weight:
            if (selectNum ==1 && count[0] && input::TRG('U'))
            {
                itemObj->item3D.itemSpec[9].exist = true;
                count[0] = false;
                arr->use_Disitem(i);
            }
            break;

            /* 鍵２ */
        case SPEC::ITEM_ID::ID_Stone1:
            if (selectNum == 2 && count[1] && input::TRG('U'))
            {
                itemObj->item3D.itemSpec[2].exist = true;
                count[1] = false;
                arr->use_Disitem(i);
            }
            break;
        }
    }
}

void GameItem::update()
{
    isChoice();
}

void GameItem::draw()
{
    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        switch (arr->items[i])
        {
            /* 錘 */
        case SPEC::ITEM_ID::ID_Weight:
            SpriteRender(M_Item->menuItem.itemSpec[9].ptr,
                pos.x,pos.y,
                0.2f, 0.2f,
                0, 0,
                295, 354,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case ItemArr::ITEM_ID::ID_Key:
            break;

        }
    }
}