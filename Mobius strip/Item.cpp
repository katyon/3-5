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

    Audio::load(sound_num::GET, L"./Data/BGM/get.wav");

    G_Item->count[0] = false;
    G_Item->count[1] = false;

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        item3D.itemSpec[i].got = false;
        item3D.itemSpec[i].used = false; // まだ使っていない
        item3D.itemSpec[i].exist = false;
    }

    item3D.itemSpec[0].exist = true;
    item3D.itemSpec[5].exist = true;
}

void ItemObj::update(FPSCamera& camera)
{
    StageObject* objects = StageManager::getIns()->getStageObjects();
    StageObject* esc1 = nullptr;
    StageObject* balance1 = nullptr;
    StageObject* balance3 = nullptr;
    StageObject* safety = nullptr;
    StageObject* objects2 = StageManager::getIns()->getStageObjects();
    StageObject* esc2 = nullptr;
    StageObject* stone1 = nullptr;
    StageObject* stone2 = nullptr;
    StageObject* pipe = nullptr;
    StageObject* balance2 = nullptr;
    StageObject* omori = nullptr;
    StageObject* key = nullptr;
    if (objects)
    {
        for (int i = 0; i < StageData::MaxObjects; i++)
        {
            if (objects[i].ID == "esc1.fbx") { esc1 = &objects[i]; }
            if (objects[i].ID == "balance1.fbx") { balance1 = &objects[i]; }
            if (objects[i].ID == "balance3.fbx") { balance3 = &objects[i]; }
            if (objects[i].ID == "safety_hint.fbx") { safety = &objects[i]; }
            if (objects[i].ID == "esc2.fbx") { esc2 = &objects[i]; }
            if (objects[i].ID == "stone1.fbx") { stone1 = &objects[i]; }
            if (objects[i].ID == "stone2.fbx") { stone2 = &objects[i]; }
            if (objects[i].ID == "pipe_hint3.fbx") { pipe = &objects[i]; }
            if (objects[i].ID == "balance2.fbx") { balance2 = &objects[i]; }
            if (objects[i].ID == "key.fbx") { key = &objects[i]; }
            if (objects[i].ID == "omori.fbx") { omori = &objects[i]; }
        }
    }

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
                if (objects2[i].ID == "esc1.fbx") { esc1 = &objects2[i]; }
                if (objects2[i].ID == "balance1.fbx") { balance1 = &objects2[i]; }
                if (objects2[i].ID == "balance3.fbx") { balance3 = &objects2[i]; }
                if (objects2[i].ID == "safety_hint.fbx") { safety = &objects2[i]; }
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

    if (esc1 != nullptr) { esc1->isShow = item3D.itemSpec[0].exist ? true : false; }
    if (esc2 != nullptr) { esc2->isShow = item3D.itemSpec[1].exist ? true : false; }
    if (stone1 != nullptr) { stone1->isShow = item3D.itemSpec[2].exist ? true : false; }
    if (stone2 != nullptr) { stone2->isShow = item3D.itemSpec[3].exist ? true : false; }
    if (pipe != nullptr) { pipe->isShow = item3D.itemSpec[4].exist ? true : false; }
    if (balance1 != nullptr) { balance1->isShow = item3D.itemSpec[5].exist ? true : false; }
    if (balance2 != nullptr) { balance2->isShow = item3D.itemSpec[6].exist ? true : false; }
    if (balance3 != nullptr) { balance3->isShow = item3D.itemSpec[7].exist ? true : false; }
    if (safety != nullptr) { safety->isShow = item3D.itemSpec[8].exist ? true : false; }
    if (omori != nullptr) { omori->isShow = item3D.itemSpec[9].exist ? true : false; }
    if (key != nullptr) { key->isShow = item3D.itemSpec[10].exist ? true : false; }

    // もし「水道管A」をクリアしたら、石盤ヒント②と天秤のヒント②が出現
    if (PipePuzzle::getInstance()->GetClearFlg() == 0)
    {
        if (!item3D.itemSpec[3].got)item3D.itemSpec[3].exist = true;
        if (!item3D.itemSpec[6].got)item3D.itemSpec[6].exist = true;
    }

    // もし「石盤」をクリアしたら、石盤ヒントを削除・脱出のヒント②と水道管ヒントが出現
    if (ButtonPush::getInstance()->final_judge)
    {
        if (!item3D.itemSpec[1].got)item3D.itemSpec[1].exist = true;
        if (!item3D.itemSpec[4].got)item3D.itemSpec[4].exist = true;

        arr->use_item(SPEC::ITEM_ID::ID_Stone1);
        arr->use_item(SPEC::ITEM_ID::ID_Stone2);
    }

    // もし「水道管B」をクリアしたら、水道管ヒントを削除・金庫のヒントが出現
    if (PipePuzzle::getInstance()->GetClearFlg() == 1)
    {
        if (!item3D.itemSpec[8].got)item3D.itemSpec[8].exist = true;
        if (!item3D.itemSpec[10].got)item3D.itemSpec[10].exist = true;
        arr->use_item(SPEC::ITEM_ID::ID_Pipe3);
    }

    // 金庫が開いたら
    if (!SafetyBox::getInstance()->locked)
    {
        if (omori != nullptr && !item3D.itemSpec[9].got)
        {
            item3D.itemSpec[9].exist = true;
        }
    }

    // 錘を使ったら
    if (item3D.itemSpec[9].used)
    {
        if (omori != nullptr)
        {
            Libra::getInstance()->Equilibrium = true;
        }
    }

    // 対象アイテムまでの距離
    FLOAT3 hit_pos[2];
    distance = 100.0f;
    static FLOAT3 rayStart, rayEnd;
    getMouseRay(camera, rayStart, rayEnd);
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

                // 距離が近いとき
                if (distance < 30.0f)
                {
                    switch (col.option)
                    {
                    case 3: // esc1,balance1(R2)
                        if (item3D.itemSpec[0].exist)
                        {
                            Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);

                            if (input::TRG(VK_LBUTTON))
                            {
                                item3D.itemSpec[0].exist = false;
                                item3D.itemSpec[5].exist = false;
                                item3D.itemSpec[2].exist = true;

                                arr->get_item(SPEC::ITEM_ID::ID_Esc1);
                                arr->get_item(SPEC::ITEM_ID::ID_Balance1);
                                item3D.itemSpec[0].got = true;
                                item3D.itemSpec[5].got = true;
                            }
                        }
                        break;

                    case 9: // safety(R2)
                        if (item3D.itemSpec[8].exist)
                        {
                            Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);

                            if (input::TRG(VK_LBUTTON))
                            {
                                item3D.itemSpec[8].exist = false;
                                arr->get_item(SPEC::ITEM_ID::ID_SafetyBox);
                                item3D.itemSpec[8].got = true;
                            }
                        }
                        break;

                    case 10: // omori(R2)
                        if (item3D.itemSpec[9].exist)
                        {
                            Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);

                            if (input::TRG(VK_LBUTTON))
                            {
                                G_Item->count[0] = true;
                                item3D.itemSpec[9].exist = false;
                                item3D.itemSpec[7].exist = true;

                                arr->get_item(SPEC::ITEM_ID::ID_Weight);
                                item3D.itemSpec[9].got = true;
                            }
                        }
                        break;



                    case 4: // esc2(R1)
                        if (item3D.itemSpec[1].exist)
                        {
                            Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);

                            if (input::TRG(VK_LBUTTON))
                            {
                                item3D.itemSpec[1].exist = false;
                                arr->get_item(SPEC::ITEM_ID::ID_Esc2);
                                item3D.itemSpec[1].got = true;
                            }
                        }
                        break;

                    case 5: // stone1,pipe(R1)
                        if (item3D.itemSpec[2].exist && !item3D.itemSpec[4].exist)
                        {
                            Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);

                            if (input::TRG(VK_LBUTTON))
                            {
                                item3D.itemSpec[2].exist = false;
                                arr->get_item(SPEC::ITEM_ID::ID_Stone1);
                                item3D.itemSpec[2].got = true;
                            }
                        }
                        if (!item3D.itemSpec[0].exist && item3D.itemSpec[4].exist)
                        {
                            Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);

                            if (input::TRG(VK_LBUTTON))
                            {
                                item3D.itemSpec[4].exist = false;
                                arr->get_item(SPEC::ITEM_ID::ID_Pipe3);
                                item3D.itemSpec[4].got = true;
                            }
                        }
                        break;

                    case 6: // stone2(R1)
                        if (item3D.itemSpec[3].exist)
                        {
                            Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);

                            if (input::TRG(VK_LBUTTON))
                            {
                                item3D.itemSpec[3].exist = false;
                                arr->get_item(SPEC::ITEM_ID::ID_Stone2);
                                item3D.itemSpec[3].got = true;
                            }
                        }
                        break;

                    case 7: // balance2(R1)
                        if (item3D.itemSpec[6].exist)
                        {
                            Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);
                            if (input::TRG(VK_LBUTTON))
                            {
                                item3D.itemSpec[6].exist = false;
                                arr->get_item(SPEC::ITEM_ID::ID_Balance2);
                                item3D.itemSpec[6].got = true;
                            }
                        }
                        break;

                    case 8: // balance3(R1)
                        if (item3D.itemSpec[7].exist)
                        {
                            Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);
                            if (input::TRG(VK_LBUTTON))
                            {
                                item3D.itemSpec[7].exist = false;
                                arr->get_item(SPEC::ITEM_ID::ID_Balance3);
                                item3D.itemSpec[7].got = true;
                            }
                        }
                        break;

                    case 11: // key(R1)
                        if (item3D.itemSpec[10].exist)
                        {
                            Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);
                            if (input::TRG(VK_LBUTTON))
                            {
                                G_Item->count[1] = true;
                                item3D.itemSpec[10].exist = false;
                                arr->get_item(SPEC::ITEM_ID::ID_Key);
                                item3D.itemSpec[10].got = true;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}


void ItemObj::render(const Camera& camera)
{
    SpriteLoad(5, L"Data/Sprite/cursor.png");
}

void ItemObj::uninit()
{
}

// 2Dでのアイテム(ゲーム画面表示・使用)
void GameItem::init()
{
    arr->init();
    M_Item->init();
    pos = { 0.0f,290.0f };
    for (int i = 0; i < 2; i++)
    {
        isdraw[i] = false;
        count[i] = false;
    }
}

void GameItem::useWeight(FPSCamera& camera)
{
    // 対象アイテムまでの距離
    FLOAT3 hit_pos[2];
    float distance = 100.0f;
    static FLOAT3 rayStart, rayEnd;
    getMouseRay(camera, rayStart, rayEnd);

    for (const auto& col : StageManager::getIns()->getColBoxs())
    {
        if (count[0])
        {
            if (col.option != -2) continue;

            if (ColLineOBB(rayStart, rayEnd, col.obb, hit_pos[SAVE]))
            {
                float dist_temp = rayStart.distanceFrom(hit_pos[SAVE]);
                if (dist_temp < distance)
                {
                    hit_pos[MINIMUM] = hit_pos[SAVE];
                    distance = rayStart.distanceFrom(hit_pos[MINIMUM]);
                    if (distance < 15.0f && !itemObj->item3D.itemSpec[9].used)
                    {
                        Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);
                        isdraw[0] = true;

                        if (input::TRG(VK_LBUTTON))
                        {
                            itemObj->item3D.itemSpec[9].used = true;
                            arr->use_item(SPEC::ITEM_ID::ID_Weight);
                        }
                    }
                    else isdraw[0] = false;
                }
            }
            else  isdraw[0] = false;
        }
    }
}

void GameItem::useKey(FPSCamera& camera)
{
    // 対象アイテムまでの距離
    FLOAT3 hit_pos[2];
    float distance = 100.0f;
    static FLOAT3 rayStart, rayEnd;
    getMouseRay(camera, rayStart, rayEnd);


    for (const auto& col : StageManager::getIns()->getColBoxs())
    {
        if (count[1])
        {
            if (col.option != -21) continue;

            if (ColLineOBB(rayStart, rayEnd, col.obb, hit_pos[SAVE]))
            {
                float dist_temp = rayStart.distanceFrom(hit_pos[SAVE]);
                if (dist_temp < distance)
                {
                    hit_pos[MINIMUM] = hit_pos[SAVE];
                    distance = rayStart.distanceFrom(hit_pos[MINIMUM]);
                    if (distance < 15.0f && !itemObj->item3D.itemSpec[10].used)
                    {
                        Reticle::getInstance()->setReticleType(Reticle::RETICLE_TYPE::LOUPE);
                        isdraw[1] = true;

                        if (input::TRG(VK_LBUTTON))
                        {
                            itemObj->item3D.itemSpec[10].used = true;
                            arr->use_item(SPEC::ITEM_ID::ID_Key);
                        }
                    }
                    else isdraw[1] = false;
                }
            }
            else  isdraw[1] = false;
        }
    }
}


void GameItem::draw()
{
    if (isdraw[0])
    {
        SpriteRender(M_Item->menuItem.itemSpec[9].ptr, pos.x, pos.y, 0.0454f, 0.0561f, 0, 0, 2048, 2048, 0, 0, 0, 1, 1, 1, 1);
        SpriteRender(5, pos.x, pos.y, 0.0454f, 0.0561f, 0, 0, 2048, 2048, 0, 0, 0, 1, 1, 1, 1);
    }

    if (isdraw[1])
    {
        SpriteRender(M_Item->menuItem.itemSpec[10].ptr, pos.x, pos.y, 0.0454f, 0.0561f, 0, 0, 2048, 2048, 0, 0, 0, 1, 1, 1, 1);
        SpriteRender(5, pos.x, pos.y, 0.0454f, 0.0561f, 0, 0, 2048, 2048, 0, 0, 0, 1, 1, 1, 1);
    }
}
