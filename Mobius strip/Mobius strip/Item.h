#pragma once
#include <algorithm>
#include "AliceLib/AliceLib.h"
#include "common.h"

class SPEC
{
public:
    enum ITEM_ID
    {
        ID_Esc1,     // ０
        ID_Esc2,     // １
        ID_Stone1,   // ２
        ID_Stone2,   // ３
        ID_Pipe3,    // ４
        ID_Balance1, // ５
        ID_Balance2, // ６
        ID_Balance3, // ７
        ID_SafetyBox,// ８
        ID_Weight,   // ９
        ID_Key,      // １０
        ID_EMPTY,    // 消しゴムさん
    };

    Sprite ptr;
    SkinnedMesh model;
    FLOAT3 pos;   // 表示位置
    FLOAT3 scale; // 表示サイズ
    FLOAT2 src;

    bool isobserve;
    bool isConsumed; // 消費されるアイテムかどうか
    bool exist;
};

class ItemArr:public SPEC
{
public:
    static constexpr int ITEM_MAX = 15;
    SPEC itemSpec[ITEM_MAX];
    ITEM_ID items[ITEM_MAX];
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
        for (auto& item : items)
        {
            if (id == item)return true;
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
                Audio::play(6);
                item = id;
                shorten();
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
    ITEM_ID use_Disitem(int num)
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
    ItemObj()
    {
        arr->reset();
    }
    FLOAT3 OBBscale;

    FLOAT3 rayStart;
    FLOAT3 rayEnd;
    float timer=0;

    FLOAT3 hitPos;
    Quaternion posture[15];

public:
    ItemArr item3D;

    void init();
    void get();
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


// ゲーム中にホイール操作で使用したりするアイテム
class GameItem
{
private:
    ItemArr gameItem;
    FLOAT2 pos;
    int selectNum = 1;

    GameItem()
    {
        arr->reset();
    }
    int timer = 0;

public:
    bool count[2];
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
