#pragma once
#include <algorithm>
#include "AliceLib/AliceLib.h"
#include "common.h"


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
    Sprite item_ptr;
    static constexpr int ITEM_MAX = 8;
    FLOAT2 pos[ITEM_MAX];   // 表示位置
    FLOAT2 scale[ITEM_MAX]; // 表示サイズ
    FLOAT2 src[ITEM_MAX];

    ITEM_ID items[ITEM_MAX];
    bool isobserve[ITEM_MAX];
    bool exist[ITEM_MAX];

    void init();
    void uninit();

    ItemArr()
    {
        for (int i = 0; i < ITEM_MAX; i++)
        {
            exist[i] = true;
        }
        reset();
    }
    void shorten()
    {
        for (int i = 0; i < ITEM_MAX; i++)
        {
            if (items[i] != ID_EMPTY)continue;
            // ここが通る時点でitems[i]は空
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

    // 全て空に
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

    // アイテムを取得できるか
    bool get_item(ITEM_ID id)
    {
        if (isPossessed(id)) return false;

        for (auto& item : items)
        {
            if (item == ID_EMPTY)
            {
                item = id;
                shorten();
                exist[item] = false;
                return true;
            }
        }
        return false;
    }

    // IDを指定してアイテムを使用する
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

    //場所を指定してアイテムを使用する
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

// ３Dでのアイテム
class ItemObj
{
private:
    SkinnedMesh kami;
    FLOAT3 pos;
    FLOAT3 scale;

    FLOAT3 OBBscale;

    FLOAT3 rayStart;
    FLOAT3 rayEnd;

    FLOAT3 hitPos;
    Quaternion posture;

public:
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

// メニューのアイテム欄に表示するアイテム
class ItemMenu
{
public:
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


//// ゲーム中にホイール操作で使用したりするアイテム
//class GameItem :public ItemArr
//{
//private:
//    // int item_num[ITEM_MAX]; 
//    bool select = false;    // 選べる状態ですよ
//
//
//    GameItem()
//    {
//        for (int i = 0; i < ITEM_MAX; i++)
//        {
//            pos[i] = { 128.0f,256.0f * i + 128.0f };
//            scale[i] = { 0.3f,0.3f };
//        }
//        reset();
//    }
//    int timer = 0;
//
//public:
//    void init();
//    void isChoice();
//    void update();
//    void draw();
//
//    static GameItem* getInstance()
//    {
//        static GameItem ins;
//        return &ins;
//    }
//};
//
//#define G_Item GameItem::getInstance()
