#pragma once
#include <algorithm>
#include "AliceLib/AliceLib.h"
#include "common.h"
class SPEC
{
public:
    enum ITEM_ID
    {
        ID_ITEM1 = 0, // �ŏ��Ɏ�����q
        ID_ITEM2 = 1, // �Q�ԖڂɎ�����q
        ID_ITEM3 = 2, // �R�ԖڂɎ�����q
        ID_ITEM4 = 3, // �S�ԖڂɎ�����q
        ID_EMPTY = 4, // �����S������
    };
    Sprite ptr;
    SkinnedMesh model;
    FLOAT3 pos;   // �\���ʒu
    FLOAT3 scale; // �\���T�C�Y
    FLOAT2 src;
    bool isobserve;
    bool isConsumed; // ������A�C�e�����ǂ���
    bool exist;
};

class ItemArr:public SPEC
{
public:
    static constexpr int ITEM_MAX = 8;
    SPEC itemSpec[ITEM_MAX];
    SPEC::ITEM_ID items[ITEM_MAX];
    void init();
    void uninit();

    ItemArr()
    {

        reset();
    }
    void shorten()
    {
        for (int i = 0; i < ITEM_MAX; i++)
        {
            if (items[i] != ID_EMPTY)continue;
            // �������ʂ鎞�_��items[i]�͋�
            for (int j = i; j < ITEM_MAX; j++)
            {
                if (items[j] != ID_EMPTY)
                {
                    ITEM_ID _con = items[i];
                    items[i] = items[j];
                    items[j] = _con;
                    break;
                }
            }
        }
    }

    // �S�ċ��
    void reset()
    {
        for (auto& item : items)
        {
            item = ID_EMPTY;
        }
    }

    bool isPossessed(ITEM_ID id)
    {
        for (auto& item : items)
        {
            if (id == item)return true;
        }
        return false;
    }

    // �A�C�e�����擾�ł��邩
    bool get_item(ITEM_ID id)
    {
        if (isPossessed(id)) return false;

        for (auto& item : items)
        {
            if (item == ID_EMPTY)
            {
                item = id;
                shorten();
                return true;
            }
        }
        return false;
    }
    
    // ID���w�肵�ăA�C�e�����g�p����
    bool use_item(ITEM_ID id)
    {

        for (auto& item : items)
        {
            if (item == id)
            {
                item = ID_EMPTY;
                shorten();
                return true;
            }
        }
        return false;
    }

    //�ꏊ���w�肵�ăA�C�e�����g�p����
    ITEM_ID use_item(int num)
    {
        if (num < 0 || num >= ITEM_MAX)return ID_EMPTY;

        if (items[num] != ID_EMPTY)
        {
            ITEM_ID result = items[num];
            items[num] = ID_EMPTY;
            shorten();
            return result;
        }
        return ID_EMPTY;
    }

    static ItemArr* getInstance()
    {
        static ItemArr ins;
        return &ins;
    }
};
#define arr ItemArr::getInstance()

// �RD�ł̃A�C�e��
class ItemObj:public ItemArr
{
private:
    FLOAT3 OBBscale;

    FLOAT3 rayStart;
    FLOAT3 rayEnd;

    FLOAT3 hitPos;
    Quaternion posture[8];

public:
    ItemArr item3D;

    void init();
    void update(const Camera& camera);
    void render(const Camera& camera);
    void uninit();

    static ItemObj* getInstance()
    {
        static ItemObj ins;
        return &ins;
    }
};
#define itemObj ItemObj::getInstance()

// ���j���[�̃A�C�e�����ɕ\������A�C�e��
class ItemMenu:public ItemArr
{
public:
    ItemArr menuItem;

    ItemMenu()
    {
        arr->reset();
    }
    void isChoice();
    void init();
    void update();
    void draw();

    static ItemMenu* getInstance()
    {
        static ItemMenu ins;
        return &ins;
    }
};

#define M_Item ItemMenu::getInstance()


// �Q�[�����Ƀz�C�[������Ŏg�p�����肷��A�C�e��
class GameItem:public ItemMenu
{
private:
    ItemArr gameItem;
    bool select = false;    // �I�ׂ��Ԃł���

    GameItem()
    {
        arr->reset();
    }
    int timer = 0;

public:
    void init();
    void isChoice();
    void update();
    void draw();

    static GameItem* getInstance()
    {
        static GameItem ins;
        return &ins;
    }
};

#define G_Item GameItem::getInstance()
