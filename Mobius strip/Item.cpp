#include "Item.h"
#include "Shelter.h"
#include "ButtonPush.h"
#include "PipePuzzle.h"
#include "menu.h"
#include "StageManager.h"

// 3Dでのアイテム

void ItemObj::init()
{
    arr->init();
    /* ID_ESC1 */
    /* ID_ESC2 */
    /* 石盤のヒント1 */
    /* 石盤のヒント2 */
    /* 水道管のヒント */
    /* 天秤のヒント1 */
    /* 天秤のヒント2 */
    /* 天秤のヒント3 */
    /* 金庫のヒント */
    /* 錘 */
    OBBscale = { 5.0f,5.0f,5.0f };
    Audio::load(6, L"./Data/BGM/get.wav");

    G_Item->count[0] = false;
    G_Item->count[1] = false;

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        item3D.itemSpec[i].exist = false;
        item3D.itemSpec[i].used = false; // まだ使っていない
    }
}

void ItemObj::update(const Camera& camera)
{
    StageObject* objects = StageManager::getIns()->getStageObjects();
    StageObject* esc1 = nullptr;
    StageObject* esc2 = nullptr;
    StageObject* stone1 = nullptr;
    StageObject* stone2 = nullptr;
    StageObject* pipe = nullptr;
    StageObject* balance1 = nullptr;
    StageObject* balance2 = nullptr;
    StageObject* balance3 = nullptr;

    StageObject* omori = nullptr;


    // オブジェクト検索して該当するものを見つけた時の処理
    if (objects)
    {
        for (int i = 0; i < StageData::MaxObjects; i++)
        {
            if (objects[i].ID == "esc1.fbx")
            {
                esc1 = &objects[i];
            }
        }
    }

    getMouseRay(camera, rayStart, rayEnd);

    // アイテム出現条件
    // 
    // もし「水道管A」をクリアしたら、石盤ヒント②と天秤のヒント②が出現
    if (PipePuzzle::getInstance()->clearFlg0)
    {
        item3D.itemSpec[3].exist = true;
        item3D.itemSpec[6].exist = true;
    }

    // もし「石盤」をクリアしたら、石盤ヒントを削除・脱出のヒント②と水道管ヒントが出現
    if (ButtonPush::getInstance()->final_judge)
    {
        item3D.itemSpec[1].exist = true;
        item3D.itemSpec[4].exist = true;
        arr->use_item(SPEC::ITEM_ID::ID_Stone1);
        arr->use_item(SPEC::ITEM_ID::ID_Stone2);
    }

    // もし「水道管B」をクリアしたら、水道管ヒントを削除・金庫のヒントが出現
    if (PipePuzzle::getInstance()->clearFlg1)
    {
        item3D.itemSpec[1].exist = true;
    }

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        if (ColLineOBB(rayStart, rayEnd, CreateOBB(item3D.itemSpec[i].pos, OBBscale, posture[i]), hitPos)&& input::TRG(VK_LBUTTON))
        {
            // 存在しててまだ使ってないなら
            if (item3D.itemSpec[i].exist && !item3D.itemSpec[i].used)
            {
                arr->get_item(static_cast<SPEC::ITEM_ID>(i));
                item3D.itemSpec[i].exist = false;

                switch (i)
                {
                case 0:
                    item3D.itemSpec[2].exist = true;
                    /*if (esc1 != nullptr)
                    {
                        esc1->isShow=
                    }*/
                    break;

                case 2:
                    item3D.itemSpec[9].exist = true;
                    break;

                case 9:
                    item3D.itemSpec[10].exist = true;
                    G_Item->selectNum = 0;
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

void ItemObj::render(const Camera& camera)
{
    COLOR color = { 1.0f,1.0f,1.0f,1.0f };

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        posture[i].reset();
        posture[0].RotationYaw(toRadian(-90.0f));
        if (item3D.itemSpec[i].exist)
        {
            //if (RoomNum == 1)
            {
                switch (i)
                {
                case 1: // 脱出ヒント②
                case 2: // 石盤ヒント①
                case 3: // 石盤ヒント②
                case 4: // 水道管ヒント
                case 6: // 天秤ヒント②
                case 7: // 天秤ヒント③
                case 10: // 鍵
                    //SkinnedMeshRender(item3D.itemSpec[i].model, camera, item3D.itemSpec[i].pos, item3D.itemSpec[i].scale, posture[i], camera.LightFloamCamera(), color);
                    break;
                }
            }

          //  if (RoomNum == 2)
            {
                switch (i)
                {
                case 0:  // 脱出ヒント①
                case 5:  // 天秤ヒント①
                case 8:  // 金庫のヒント
                case 9:  // 錘
                    //SkinnedMeshRender(item3D.itemSpec[i].model, camera, item3D.itemSpec[i].pos, item3D.itemSpec[i].scale, posture[i], camera.LightFloamCamera(), color);
                    break;
                }
            }
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
    gameItem.itemSpec[9].pos = { 0.0f,290.0f,0.0f };
    gameItem.itemSpec[0].pos = { 0.0f,290.0f + 120,0.0f };
}

void GameItem::isChoice()
{
    if (count[0] && !count[1]) { selectNum = 0; }
    if (count[0] && count[1])
    {
        if (input::GetWheel() > 0) { selectNum = 0; }
        if (input::GetWheel() < 0) { selectNum = 1; }
    }
    if (!count[0] && count[1]) { selectNum = 1; }

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        switch (arr->items[i])
        {
            /* 錘 */
        case SPEC::ITEM_ID::ID_Weight:
            if (selectNum ==0 && count[0] && input::TRG('U'))
            {
                itemObj->item3D.itemSpec[9].exist = true;
                itemObj->item3D.itemSpec[9].used = true; // 使用済み
                itemObj->item3D.itemSpec[9].pos = { 20,20,20 };
                itemObj->item3D.itemSpec[9].scale = { 0.02f,0.02f,0.02f };
                count[0] = false;
                selectNum = 1;
                arr->use_Disitem(i);
            }
            break;

            /* 鍵 */
        case SPEC::ITEM_ID::ID_Esc1:
            if (selectNum == 1 && count[1] && input::TRG('U'))
            {
                itemObj->item3D.itemSpec[10].used = true; // 使用済み
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
                gameItem.itemSpec[9].pos.x, gameItem.itemSpec[9].pos.y,
                0.05f, 0.05f,
                0, 0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);

            if(selectNum==0)
            SpriteRender(12,
                gameItem.itemSpec[9].pos.x, gameItem.itemSpec[9].pos.y,
                0.9f, 0.9f,
                0, 0,
                120, 120,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case SPEC::ITEM_ID::ID_Esc1:
            if (count[0])
            {
                SpriteRender(M_Item->menuItem.itemSpec[0].ptr,
                    gameItem.itemSpec[0].pos.x, gameItem.itemSpec[0].pos.y,
                    0.05f, 0.05f,
                    0, 0,
                    2048, 2048,
                    0, 0,
                    0,
                    1, 1, 1, 1);
                if (selectNum == 1) {
                    SpriteRender(12,
                        gameItem.itemSpec[0].pos.x, gameItem.itemSpec[0].pos.y,
                        0.9f, 0.9f,
                        0, 0,
                        120, 120,
                        0, 0,
                        0,
                        1, 1, 1, 1);
                }
            }
            if(!count[0])
            {
                SpriteRender(M_Item->menuItem.itemSpec[0].ptr,
                    gameItem.itemSpec[9].pos.x, gameItem.itemSpec[9].pos.y,
                    0.05f, 0.05f,
                    0, 0,
                    2048, 2048,
                    0, 0,
                    0,
                    1, 1, 1, 1);

                SpriteRender(12,
                    gameItem.itemSpec[9].pos.x, gameItem.itemSpec[9].pos.y,
                    0.9f, 0.9f,
                    0, 0,
                    120, 120,
                    0, 0,
                    0,
                    1, 1, 1, 1);
            }
            break;
        }
    }
}