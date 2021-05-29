#include "Item.h"
#include "Shelter.h"
#include "ButtonPush.h"
#include "PipePuzzle.h"
#include "menu.h"
#include "StageManager.h"

// 3D�ł̃A�C�e��

void ItemObj::init()
{
    arr->init();
    /* ID_ESC1 */
    /* ID_ESC2 */
    /* �ΔՂ̃q���g1 */
    /* �ΔՂ̃q���g2 */
    /* �����ǂ̃q���g */
    /* �V���̃q���g1 */
    /* �V���̃q���g2 */
    /* �V���̃q���g3 */
    /* ���ɂ̃q���g */
    /* �� */
    OBBscale = { 5.0f,5.0f,5.0f };
    Audio::load(6, L"./Data/BGM/get.wav");

    G_Item->count[0] = false;
    G_Item->count[1] = false;

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        item3D.itemSpec[i].exist = false;
        item3D.itemSpec[i].used = false; // �܂��g���Ă��Ȃ�
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


    // �I�u�W�F�N�g�������ĊY��������̂����������̏���
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

    // �A�C�e���o������
    // 
    // �����u������A�v���N���A������A�ΔՃq���g�A�ƓV���̃q���g�A���o��
    if (PipePuzzle::getInstance()->clearFlg0)
    {
        item3D.itemSpec[3].exist = true;
        item3D.itemSpec[6].exist = true;
    }

    // �����u�ΔՁv���N���A������A�ΔՃq���g���폜�E�E�o�̃q���g�A�Ɛ����ǃq���g���o��
    if (ButtonPush::getInstance()->final_judge)
    {
        item3D.itemSpec[1].exist = true;
        item3D.itemSpec[4].exist = true;
        arr->use_item(SPEC::ITEM_ID::ID_Stone1);
        arr->use_item(SPEC::ITEM_ID::ID_Stone2);
    }

    // �����u������B�v���N���A������A�����ǃq���g���폜�E���ɂ̃q���g���o��
    if (PipePuzzle::getInstance()->clearFlg1)
    {
        item3D.itemSpec[1].exist = true;
    }

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        if (ColLineOBB(rayStart, rayEnd, CreateOBB(item3D.itemSpec[i].pos, OBBscale, posture[i]), hitPos)&& input::TRG(VK_LBUTTON))
        {
            // ���݂��ĂĂ܂��g���ĂȂ��Ȃ�
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
                case 1: // �E�o�q���g�A
                case 2: // �ΔՃq���g�@
                case 3: // �ΔՃq���g�A
                case 4: // �����ǃq���g
                case 6: // �V���q���g�A
                case 7: // �V���q���g�B
                case 10: // ��
                    //SkinnedMeshRender(item3D.itemSpec[i].model, camera, item3D.itemSpec[i].pos, item3D.itemSpec[i].scale, posture[i], camera.LightFloamCamera(), color);
                    break;
                }
            }

          //  if (RoomNum == 2)
            {
                switch (i)
                {
                case 0:  // �E�o�q���g�@
                case 5:  // �V���q���g�@
                case 8:  // ���ɂ̃q���g
                case 9:  // ��
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

// 2D�ł̃A�C�e��(�Q�[����ʕ\���E�g�p)
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
            /* �� */
        case SPEC::ITEM_ID::ID_Weight:
            if (selectNum ==0 && count[0] && input::TRG('U'))
            {
                itemObj->item3D.itemSpec[9].exist = true;
                itemObj->item3D.itemSpec[9].used = true; // �g�p�ς�
                itemObj->item3D.itemSpec[9].pos = { 20,20,20 };
                itemObj->item3D.itemSpec[9].scale = { 0.02f,0.02f,0.02f };
                count[0] = false;
                selectNum = 1;
                arr->use_Disitem(i);
            }
            break;

            /* �� */
        case SPEC::ITEM_ID::ID_Esc1:
            if (selectNum == 1 && count[1] && input::TRG('U'))
            {
                itemObj->item3D.itemSpec[10].used = true; // �g�p�ς�
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
            /* �� */
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