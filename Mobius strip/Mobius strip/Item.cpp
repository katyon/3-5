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
    item3D.itemSpec[0].scale = { 0.5f,1.0f,0.7f };
    item3D.itemSpec[0].exist = true;

    /* ID_ESC2 */
    item3D.itemSpec[1].model.load("Data/Objects/esc2.fbx");
    item3D.itemSpec[1].pos = { 0.0f,10.0f,0.0f };
    item3D.itemSpec[1].scale = { 0.05f,0.05f,0.05f };
    //item3D.itemSpec[1].exist = false;

    /* 石盤のヒント1 */
    item3D.itemSpec[2].model.load("Data/Objects/kami.fbx");
    item3D.itemSpec[2].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[2].scale = { 0.5f,1.0f,0.7f };
    item3D.itemSpec[2].exist = false;

    /* 石盤のヒント2 */
    item3D.itemSpec[3].model.load("Data/Objects/kami.fbx");
    item3D.itemSpec[3].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[3].scale = { 0.5f,1.0f,0.7f };
    //item3D.itemSpec[3].exist = false;

    /* 水道管のヒント */
    item3D.itemSpec[4].model.load("Data/Objects/omori.fbx");
    item3D.itemSpec[4].pos = { 0.0f,10.0f,0.0f };
    item3D.itemSpec[4].scale = { 0.05f,0.05f,0.05f };
    //item3D.itemSpec[4].exist = false;

    /* 天秤のヒント1 */
    item3D.itemSpec[5].model.load("Data/Objects/balance1.fbx");
    item3D.itemSpec[5].pos = { -46.0f,10.0f,-37.0f };

    item3D.itemSpec[5].scale = { 0.5f,1.0f,0.7f };
    //item3D.itemSpec[5].exist = true;

    /* 天秤のヒント2 */
    item3D.itemSpec[6].model.load("Data/Objects/balance2.fbx");
    item3D.itemSpec[6].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[6].scale = { 0.5f,1.0f,0.7f };
    //item3D.itemSpec[6].exist = false;

    /* 天秤のヒント3 */
    item3D.itemSpec[7].model.load("Data/Objects/balance3.fbx");
    item3D.itemSpec[7].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[7].scale = { 0.5f,1.0f,0.7f };
    //item3D.itemSpec[7].exist = false;

    /* 金庫のヒント */
    item3D.itemSpec[8].model.load("Data/Objects/balance3.fbx");
    item3D.itemSpec[8].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[8].scale = { 0.5f,1.0f,0.7f };
    //item3D.itemSpec[8].exist = false;

    /* 錘 */
    item3D.itemSpec[9].model.load("Data/Objects/omori.fbx");
    item3D.itemSpec[9].pos = { 0.0f,10.0f,0.0f };
    item3D.itemSpec[9].scale = { 0.05f,0.05f,0.05f };
    item3D.itemSpec[9].exist = false;

    /* 鍵 */
    item3D.itemSpec[10].model.load("Data/Objects/balance3.fbx");
    item3D.itemSpec[10].pos = { -46.0f,10.0f,-37.0f };
    item3D.itemSpec[10].scale = { 0.5f,1.0f,0.7f };
    //item3D.itemSpec[10].exist = false;

    OBBscale = { 5.0f,5.0f,5.0f };
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
                        item3D.itemSpec[2].exist = true;
                        break;

                    case 2:
                        item3D.itemSpec[9].exist = true;
                        break;

                    case 9:
                        item3D.itemSpec[10].exist = true;
                        G_Item->count[0] = true;
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

    //Debug->SetString("中身[0]:%d", arr->items[0]);
    //Debug->SetString("中身[1]:%d", arr->items[1]);
    //Debug->SetString("中身[2]:%d", arr->items[2]);
    //Debug->SetString("中身[3]:%d", arr->items[3]);
    //Debug->SetString("中身[4]:%d", arr->items[4]);
    //Debug->SetString("中身[5]:%d", arr->items[5]);
    //Debug->SetString("中身[6]:%d", arr->items[6]);
    //Debug->SetString("中身[7]:%d", arr->items[7]);
    //Debug->SetString("中身[8]:%d", arr->items[8]);
    //Debug->SetString("中身[9]:%d", arr->items[9]);
    //Debug->SetString("中身[10]:%d", arr->items[10]);

    //Debug->SetString("存在[0]:%d", itemObj->item3D.itemSpec[0].exist);
    //Debug->SetString("存在[1]:%d", itemObj->item3D.itemSpec[1].exist);
    //Debug->SetString("存在[2]:%d", itemObj->item3D.itemSpec[2].exist);
    //Debug->SetString("存在[3]:%d", itemObj->item3D.itemSpec[3].exist);
    //Debug->SetString("存在[4]:%d", itemObj->item3D.itemSpec[4].exist);
    //Debug->SetString("存在[5]:%d", itemObj->item3D.itemSpec[5].exist);
    //Debug->SetString("存在[6]:%d", itemObj->item3D.itemSpec[6].exist);
    //Debug->SetString("存在[7]:%d", itemObj->item3D.itemSpec[7].exist);
    //Debug->SetString("存在[8]:%d", itemObj->item3D.itemSpec[8].exist);
    //Debug->SetString("存在[9]:%d", itemObj->item3D.itemSpec[9].exist);
    //Debug->SetString("存在[10]:%d", itemObj->item3D.itemSpec[10].exist);
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
                itemObj->item3D.itemSpec[9].pos = { 20,20,20 };
                itemObj->item3D.itemSpec[9].scale = { 0.02f,0.02f,0.02f };
                count[0] = false;
                arr->use_Disitem(i);
            }
            break;

            /* 鍵 */
        case SPEC::ITEM_ID::ID_Key:
            if (selectNum == 2 && count[1] && input::TRG('U'))
            {
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