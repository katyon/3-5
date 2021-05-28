#include "Item.h"
#include "Shelter.h"
#include "ButtonPush.h"
#include "PipePuzzle.h"
#include "menu.h"
#include "StageManager.h"
#include "reticle.h"
#include "safety_box.h"
#include "Balance.h"
#include "Sound.h"

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
    Audio::load(sound_num::GET, L"./Data/BGM/get.wav");

    G_Item->count[0] = false;
    G_Item->count[1] = false;

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        item3D.itemSpec[i].used = false; // まだ使っていない
    }
    item3D.itemSpec[0].exist = true;
    item3D.itemSpec[1].exist = true;
}

void ItemObj::Diffupdate(FPSCamera& camera)
{
    StageObject* objects = StageManager::getIns()->getStageObjects();
    StageObject* esc1 = nullptr;
    StageObject* balance1 = nullptr;
    StageObject* balance3 = nullptr;
    StageObject* safety = nullptr;
    if (objects)
    {
        for (int i = 0; i < StageData::MaxObjects; i++)
        {
            if (objects[i].ID == "esc1.fbx") { esc1 = &objects[i]; }
            if (objects[i].ID == "balance1.fbx") { balance1 = &objects[i]; }
            if (objects[i].ID == "balance3.fbx") { balance3 = &objects[i]; }
            if (objects[i].ID == "safety_hint.fbx") { safety = &objects[i]; }
        }
    }

    StageObject* objects2 = StageManager::getIns()->getStageObjects();
    StageObject* esc2 = nullptr;
    StageObject* stone1 = nullptr;
    StageObject* stone2 = nullptr;
    StageObject* pipe = nullptr;
    StageObject* balance2 = nullptr;
    StageObject* omori = nullptr;
    StageObject* key = nullptr;
    // オブジェクト検索して該当するものを見つけた時の処理(別ステージ)
    // 今いるステージ番号が0なら1を見て、1だったら0を見る
    StageData* stage = StageManager::getIns()->getStageData(StageManager::getIns()->getStageNum() == 0 ? 1 : 0);
    if (stage) // 念のため
    {
        objects2 = stage->getObdects();
        if (objects2)
        {
            for (int i = 0; i < StageData::MaxObjects; i++)
            {
                if (objects2[i].ID == "esc2.fbx") { esc2 = &objects2[i]; }
                if (objects2[i].ID == "stone1.fbx") { stone1 = &objects2[i]; }
                if (objects2[i].ID == "stone2.fbx") { stone2 = &objects2[i]; }
                if (objects2[i].ID == "pipe_hint3.fbx") { pipe = &objects2[i]; }
                if (objects2[i].ID == "balance2.fbx") { balance2 = &objects2[i]; }
                if (objects2[i].ID == "key.fbx") { key = &objects2[i]; }
                if (objects2[i].ID == "omori.fbx") { omori = &objects2[i]; }
            }
        }
    }

    // 対象アイテムまでの距離
    FLOAT3 hit_pos[2];
    static FLOAT3 rayStart, rayEnd;
    getMouseRay(camera, rayStart, rayEnd);

    // アイテム出現条件
    // 
    // もし「水道管A」をクリアしたら、石盤ヒント②と天秤のヒント②が出現
    if (PipePuzzle::getInstance()->GetClearFlg() == 0)
    {
        item3D.itemSpec[3].exist = true;
        item3D.itemSpec[6].exist = true;
    }

    // もし「石盤」をクリアしたら、石盤ヒントを削除・脱出のヒント②と水道管ヒントが出現
    if (ButtonPush::getInstance()->judge_answer())
    {
        item3D.itemSpec[1].exist = true;
        item3D.itemSpec[4].exist = true;
        arr->use_item(SPEC::ITEM_ID::ID_Stone1);
        arr->use_item(SPEC::ITEM_ID::ID_Stone2);
    }

    // もし「水道管B」をクリアしたら、水道管ヒントを削除・金庫のヒントが出現
    if (PipePuzzle::getInstance()->GetClearFlg() == 1)
    {
        item3D.itemSpec[1].exist = true;
    }

    // 当たり判定検索ループ
    for (const auto& col : StageManager::getIns()->getColBoxs())
    {
        // アイテムは3以降に設定しているのでそれより前は見なくていい
        if (col.option < 3) continue;

        if (ColLineOBB(rayStart, rayEnd, col.obb, hit_pos[SAVE]))
        {
            float dist_temp = rayStart.distanceFrom(hit_pos[SAVE]);
            if (dist_temp < distance)
            {
                hit_pos[MINIMUM] = hit_pos[SAVE];
                distance = rayStart.distanceFrom(hit_pos[MINIMUM]);
            }
            // 距離が近いときにクリックしたら
            if (distance < 30.0f && input::TRG(VK_LBUTTON))
            {
                switch (col.option)
                {
                case 3: // esc1,balance1(R2)
                    break;

                case 9: // safety(R2)
                    break;

                case 10: // omori(R2)
                    break;



                case 4: // esc2(R1)
                    break;

                case 5: // stone1,pipe(R1)
                    break;

                case 6: // stone2(R1)
                    break;

                case 7: // balance2(R1)
                    break;

                case 8: // balance8(R1)
                    break;

                case 11: // key(R1)
                    break;



                }
            }
        }
    }
}



//void ItemObj::Diffupdate(FPSCamera& camera)
//{
// 
//
//    // もし「石盤」をクリアしたら、石盤ヒントを削除・脱出のヒント②と水道管ヒントが出現
//    if (ButtonPush::getInstance()->final_judge)
//    {
//        if ((esc2 != nullptr) && (pipe != nullptr))
//        {
//            esc2->isShow = true;
//            item3D.itemSpec[1].exist = true;
//            pipe->isShow = true;
//            item3D.itemSpec[4].exist = true;
//        }
//        arr->use_item(SPEC::ITEM_ID::ID_Stone1);
//        arr->use_item(SPEC::ITEM_ID::ID_Stone2);
//    }
//
//    // 金庫が開いたら
//    if (!SafetyBox::getInstance()->locked)
//    {
//        if (omori != nullptr && !item3D.itemSpec[9].exist)
//        {
//            omori->isShow = true;
//            item3D.itemSpec[9].exist = true;
//        }
//    }
//
//    // 錘を使ったら
//    if (item3D.itemSpec[9].used)
//    {
//        if (omori != nullptr/* && !omori->isShow*/)
//        {
//            Libra::getInstance()->Equilibrium = true;
//        }
//    }
//
//    FLOAT3 hit_pos[2];
//    float distance = 100.0f;
//    static FLOAT3 rayStart, rayEnd;
//    getMouseRay(camera, rayStart, rayEnd);
//
//                // 距離が近いときにクリックしたら
//                if (distance < 30.0f && input::TRG(VK_LBUTTON))
//                {
//                    switch (col.option)
//                    {
//                        // 脱出②を入手
//                    case 4:
//                        if (esc2 != nullptr && item3D.itemSpec[1].exist)
//                        {
//                            esc2->isShow = false;
//                            item3D.itemSpec[1].exist = false;
//                            arr->get_item(static_cast<SPEC::ITEM_ID>(SPEC::ITEM_ID::ID_Esc2));
//                        }
//                        break;
//
//                    case 5:
//                        if (stone1 != nullptr && item3D.itemSpec[2].exist && !item3D.itemSpec[4].exist)
//                        {
//                            stone1->isShow = false;
//                            item3D.itemSpec[2].exist = false;
//                            arr->get_item(static_cast<SPEC::ITEM_ID>(SPEC::ITEM_ID::ID_Stone1));
//                        }
//                        if (pipe != nullptr && item3D.itemSpec[4].exist)
//                        {
//                            pipe->isShow = false;
//                            item3D.itemSpec[4].exist = false;
//                            arr->get_item(static_cast<SPEC::ITEM_ID>(SPEC::ITEM_ID::ID_Pipe3));
//                        }
//                        break;
//
//                    case 6:
//                        if (stone2 != nullptr && item3D.itemSpec[3].exist)
//                        {
//                            stone2->isShow = false;
//                            item3D.itemSpec[3].exist = false;
//                            arr->get_item(static_cast<SPEC::ITEM_ID>(SPEC::ITEM_ID::ID_Stone2));
//                        }
//                        break;
//
//                    case 7:
//                        if (balance2 != nullptr && item3D.itemSpec[6].exist)
//                        {
//                            balance2->isShow = false;
//                            item3D.itemSpec[6].exist = false;
//                            arr->get_item(static_cast<SPEC::ITEM_ID>(SPEC::ITEM_ID::ID_Balance2));
//                        }
//                        break;
//
//                    case 10:
//                        if (omori != nullptr && item3D.itemSpec[9].exist)
//                        {
//                            omori->isShow = false;
//                            item3D.itemSpec[9].exist = false;
//                            arr->get_item(static_cast<SPEC::ITEM_ID>(SPEC::ITEM_ID::ID_Weight));
//                            G_Item->selectNum = 0;
//                            G_Item->count[0] = true;
//
//                            if (!item3D.itemSpec[7].exist)item3D.itemSpec[7].exist = true;
//                            if (!item3D.itemSpec[10].exist)item3D.itemSpec[10].exist = true;
//                        }
//                        break;
//
//                    case 11:
//                        if (key != nullptr && item3D.itemSpec[10].exist)
//                        {
//                            key->isShow = false;
//                            item3D.itemSpec[10].exist = false;
//                            arr->get_item(static_cast<SPEC::ITEM_ID>(SPEC::ITEM_ID::ID_Key));
//                            G_Item->count[1] = true;
//                        }
//                        break;
//                    }
//                }
//            }
//        }
//    }
//}
//
//void ItemObj::Sameupdate(FPSCamera& camera)
//{
//    // 同ステージ内
//    StageObject* objects = StageManager::getIns()->getStageObjects();
//    StageObject* esc1 = nullptr;
//    StageObject* balance1 = nullptr;
//    StageObject* balance3 = nullptr;
//    StageObject* safety = nullptr;
//
//    // オブジェクト検索して該当するものを見つけた時の処理(同一ステージ)
//    if (objects)
//    {
//        for (int i = 0; i < StageData::MaxObjects; i++)
//        {
//            if (objects[i].ID == "esc1.fbx") { esc1 = &objects[i]; }
//            if (objects[i].ID == "balance1.fbx") { balance1 = &objects[i]; }
//            if (objects[i].ID == "balance3.fbx") { balance3 = &objects[i]; }
//            if (objects[i].ID == "safety_hint.fbx") { safety = &objects[i]; }
//        }
//    }
//
//    FLOAT3 hit_pos[2];
//    float distance = 100.0f;
//    static FLOAT3 rayStart, rayEnd;
//    getMouseRay(camera, rayStart, rayEnd);
//
//
//    // アイテム出現条件
//    // もし「水道管B」をクリアしたら、水道管ヒントを削除・金庫のヒントが出現
//    if (PipePuzzle::getInstance()->clearFlg1)
//    {
//        if (safety != nullptr)
//        {
//            safety->isShow = true;
//            item3D.itemSpec[8].exist = true;
//        }
//        arr->use_item(SPEC::ITEM_ID::ID_Pipe3);
//    }
//
//    for (const auto& col : StageManager::getIns()->getColBoxs())
//    {
//        if (col.option < 3) continue;
//
//        if (ColLineOBB(rayStart, rayEnd, col.obb, hit_pos[SAVE]))
//        {
//            float dist_temp = rayStart.distanceFrom(hit_pos[SAVE]);
//            if (dist_temp < distance)
//            {
//                hit_pos[MINIMUM] = hit_pos[SAVE];
//                distance = rayStart.distanceFrom(hit_pos[MINIMUM]);
//            }
//                // 距離が近いときにクリックしたら
//                if (distance < 30.0f && input::TRG(VK_LBUTTON))
//                {
//                    // 当たり判定エディターで設定したoption番号で判断
//                    switch (col.option)
//                    {
//                        // 脱出①と天秤①を手に入れたら、石盤①が出現
//                    case 3:
//                        if ((esc1 != nullptr && item3D.itemSpec[0].exist) && (balance1 != nullptr && item3D.itemSpec[5].exist))
//                        {
//                            esc1->isShow = false;
//                            balance1->isShow = false;
//                            item3D.itemSpec[0].exist = false;
//                            item3D.itemSpec[5].exist = false;
//                            arr->get_item(static_cast<SPEC::ITEM_ID>(SPEC::ITEM_ID::ID_Esc1));
//                            arr->get_item(static_cast<SPEC::ITEM_ID>(SPEC::ITEM_ID::ID_Balance1));
//
//                            if (!item3D.itemSpec[2].exist) { item3D.itemSpec[2].exist = true; }
//                        }
//                        break;
//
//                    case 8:
//                        if (balance3 != nullptr && item3D.itemSpec[7].exist)
//                        {
//                            balance3->isShow = false;
//                            item3D.itemSpec[7].exist = false;
//                            arr->get_item(static_cast<SPEC::ITEM_ID>(SPEC::ITEM_ID::ID_Balance3));
//                        }
//                        break;
//
//                    case 9:
//                        if (safety != nullptr && item3D.itemSpec[8].exist)
//                        {
//                            safety->isShow = false;
//                            item3D.itemSpec[8].exist = false;
//                            arr->get_item(static_cast<SPEC::ITEM_ID>(SPEC::ITEM_ID::ID_SafetyBox));
//                        }
//                        break;
//                    }
//                
//            }
//        }
//    }
//
//
//    // ルーペ表示の条件
//    for (int i = 0; i < arr->ITEM_MAX; i++)
//    {
//        if (distance < 30.0f && item3D.itemSpec[i].exist)
//        {
//            Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);
//        }
//    }
//}

void ItemObj::render(const Camera& camera)
{
 //   Debug->SetString("距離：%f", distance);
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
}

void GameItem::isChoice()
{
    //if (count[0] && !count[1]) { selectNum = 0; }
    //if (count[0] && count[1])
    //{
    //    if (input::GetWheel() > 0) { selectNum = 0; }
    //    if (input::GetWheel() < 0) { selectNum = 1; }
    //}
    //if (!count[0] && count[1]) { selectNum = 1; }

    //for (int i = 0; i < arr->ITEM_MAX; i++)
    //{
    //    switch (arr->items[i])
    //    {
    //        /* 錘 */
    //    case SPEC::ITEM_ID::ID_Weight:
    //        if (selectNum ==0 && count[0] && input::TRG('U'))
    //        {
    //            itemObj->item3D.itemSpec[9].used = true; // 使用済み
    //            count[0] = false;
    //            selectNum = 1;
    //            arr->use_Disitem(i);
    //        }
    //        break;

    //        /* 鍵 */
    //    case SPEC::ITEM_ID::ID_Esc1:
    //        if (selectNum == 1 && count[1] && input::TRG('U'))
    //        {
    //            itemObj->item3D.itemSpec[10].used = true; // 使用済み
    //            count[1] = false;
    //            arr->use_Disitem(i);
    //        }
    //        break;
    //    }
    //}
}

void GameItem::update()
{
    isChoice();
}

void GameItem::draw()
{
    Debug->SetString("中身0:%d", arr->items[0]);
    Debug->SetString("中身1:%d", arr->items[1]);
    Debug->SetString("中身2:%d", arr->items[2]);
    Debug->SetString("中身3:%d", arr->items[3]);
    Debug->SetString("中身4:%d", arr->items[4]);
    Debug->SetString("中身5:%d", arr->items[5]);
    Debug->SetString("中身6:%d", arr->items[6]);
    Debug->SetString("存在0:%d", itemObj->item3D.itemSpec[0].exist);
    Debug->SetString("存在1:%d", itemObj->item3D.itemSpec[1].exist);
    Debug->SetString("存在2:%d", itemObj->item3D.itemSpec[2].exist);
    Debug->SetString("存在3:%d", itemObj->item3D.itemSpec[3].exist);
    Debug->SetString("存在4:%d", itemObj->item3D.itemSpec[4].exist);
    Debug->SetString("存在5:%d", itemObj->item3D.itemSpec[5].exist);


    // 錘を所持中かつ使っていない
    if (count[0] && !itemObj->item3D.itemSpec[9].used)
    {
        SpriteRender(M_Item->menuItem.itemSpec[9].ptr, gameItem.itemSpec[9].pos.x, gameItem.itemSpec[9].pos.y, 0.05f, 0.05f, 0, 0, 2048, 2048, 0, 0, 0, 1, 1, 1, 1);
    }

    // 鍵を所持中かつ使っていない
    if (count[1] && !itemObj->item3D.itemSpec[10].used)
    {
        SpriteRender(M_Item->menuItem.itemSpec[10].ptr, gameItem.itemSpec[9].pos.x, gameItem.itemSpec[9].pos.y, 0.05f, 0.05f, 0, 0, 2048, 2048, 0, 0, 0, 1, 1, 1, 1);
    }
}
