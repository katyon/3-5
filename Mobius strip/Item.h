#pragma once
#include <list>
#include <algorithm>
#include "AliceLib/AliceLib.h"

enum ITEM_ID
{
    ID_ITEM1 = 0,
    ID_ITEM2 = 1,
    ID_ITEM3 = 2,
    ID_ITEM4 = 3,
    ID_EMPTY = 4,
};

class ItemArr
{
public:
    static constexpr int ITEM_MAX = 8;
    FLOAT2 pos[ITEM_MAX];   // �\���ʒu
    FLOAT2 scale[ITEM_MAX]; // �\���T�C�Y
    FLOAT2 src[ITEM_MAX];
    Sprite item_ptr;
    ITEM_ID items[ITEM_MAX];
    bool isobserve[ITEM_MAX];

    void init();
    virtual void update() = 0;
    virtual void draw() = 0;
    void uninit();

    // �Q�[�����ɃA�C�e�����I�����ꂽ�Ƃ��̏���
    virtual void isChoice() = 0;

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
        for (auto i : items)
        {
            if (id == i)return true;
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
};


class ItemMenu :public ItemArr
{
public:
    ItemMenu()
    {
        for (int i = 0; i < ITEM_MAX; i++)
        {
            pos[i] = { 128.0f * i + 128.0f,256.0f };
        }
        reset();
    }
    void isChoice() override;
    void update();
    void draw();

    static ItemMenu* getInstance()
    {
        static ItemMenu ins;
        return &ins;
    }
};

#define M_Item ItemMenu::getInstance()

class GameItem :public ItemArr
{
private:
    SkinnedMesh Item;
    bool select = false;

    GameItem()
    {
        for (int i = 0; i < ITEM_MAX; i++)
        {
            pos[i] = { 128.0f,256.0f * i + 128.0f };
        }
        reset();
    }
    int timer = 0;

public:
    void init();
    void isChoice() override;
    void update();
    void draw();

    static GameItem* getInstance()
    {
        static GameItem ins;
        return &ins;
    }
};

#define G_Item GameItem::getInstance()
