#pragma once
#include "common.h"
#include "AliceLib/AliceLib.h"
#include "Item.h"

enum MenuTab
{
    Item, // �A�C�e����
    Memo, // ������
    Exit, // �^�C�g���ɖ߂�
    Back, // �Q�[���ɖ߂�
};

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
private:
    FLOAT2 pos;   // �\���ʒu
    FLOAT2 scale; // �\���T�C�Y
    
public:
    Sprite item_ptr;
    static constexpr int ITEM_MAX = 8;
    ITEM_ID items[8];
    int get_order[5]; // �A�C�e���l����(��������Ȃ�)

    void init();
    virtual void update() = 0;
    virtual void draw() = 0;
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

    // �A�C�e�����擾�ł��邩
    bool get_item(ITEM_ID id)
    {
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

    void Setnum()
    {
        for (auto& item : items)
        {
            if (get_item(item))
            {
                
            }
        }
    }


};

class ItemMenu:public ItemArr
{
public:
    bool observe = false;

    void update() override;
    void draw() override;
};

class GameItem :public ItemArr
{
public:
    void update() override;
    void draw() override;
};

class Menu
{
private:
    Sprite menu_ptr;
    FLOAT2 pos;
    int tab;

public:
    ItemMenu item_menu;
    void init();
    void update();
    void draw();
    void uninit();
};