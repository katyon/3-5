#pragma once

#include "common.h"
#include "AliceLib/AliceLib.h"
#include "Item.h"

/* メニュータブの種類 */
enum MenuTab
{
    ItemTab,   // アイテム欄
    MemoTab,   // メモ欄
    OptionTab, // オプションとか
};


/* メニュークラス */
class Menu
{
private:
    Sprite menu_ptr;

public:
    int tab;
    void init();
    void update();
    void draw();
    void uninit();
};

enum ITEM_ID
{
    ID_KEY = 0,
    ID_MEMO1 = 1,
    ID_ITEM2 = 2,
    ID_ITEM3 = 3,
    ID_ITEM4 = 4,
    ID_ITEM5 = 5,
    ID_ITEM6 = 6,
    ID_EMPTY = 7,
};

/* アイテムマネージャー */
class Item
{
protected:
    static constexpr int ITEM_MAX = 8;
    //virtual void init() = 0;
    //virtual void update() = 0;
    //virtual void draw() = 0;
    //virtual void uninit() = 0;
};


/* ゲーム画面におけるアイテムクラス */
class ItemArr
{
private:
    ITEM_ID items[8];

public:
};


/* メニュー画面におけるアイテムクラス */




/*extern class ItemList itemlist;

class ItemList
{
private:
    std::list<ITEM_ID> items;  // itemsという名前のコンテナ作成
    Sprite item_ptr;

public:
    FLOAT2 pos[ITEM_MAX];
    FLOAT2 src[ITEM_MAX]; // 画像切り取り位置
    int cursor;
    bool observation = false;


public:
    ItemList()
    {
        // ITEM_MAXのコンテナを作成
        items.resize(static_cast<size_t>(ITEM_MAX));
        reset();
    }

    void init();
    void update();
    void draw(Menu* menu);
    void uninit();


    // 整列
    void SetUp()
    {
        items.sort([](const ITEM_ID& i1, const ITEM_ID& i2) {return i1 < i2; });
    }

    // 全て空に
    void reset()
    {
        auto item = items.begin();
        for (int i = 0; i < ITEM_MAX; i++)
        {
            (*item) = ID_EMPTY;
            item++;
        }
    }

    // アイテムを取得できるか
    bool canGetItem(ITEM_ID id)
    {
        auto item = items.begin();
        for (int i = 0; i < ITEM_MAX; i++)
        {
            if ((*item) == ID_EMPTY)
            {
                (*item) = id;
                SetUp();
                return true;
            }
            item++;
        }
        return false;
    }

    // 場所を選択してアイテムを使用する
    ITEM_ID useItem(int num)
    {
        if (num < 0 || num >= ITEM_MAX) return ID_EMPTY;
        auto item = items.begin();
        for (int i = 0; i < num; i++)
        {
            item++;
        }
        if ((*item) == ID_EMPTY) return ID_EMPTY;
        ITEM_ID result = (*item);
        (*item) = ID_EMPTY;
        SetUp();
        return result;
    }
    */
 /*   void demoPlay()
    {
        for (int i = 0; i < ITEM_MAX; i++)
        {
            if (ColRects(pos[i].y, pos[i].y + 64, ..., input::GetMousePos()))
            {
                ITEM_ID result = useItem(i);
                switch (result)
                {
                case ID_KEY:
                    //鍵を使ったときの処理
                    break;
                case ID_MEMO1:
                    this->canGetItem(ID_MEMO1);
                    break;
                default:
                    break;
                }

            }
        }

        //int count = 0;
        //for (auto item : items)
        //{
        //    switch (item)
        //    {
        //    case ID_KEY:
        //        SpriteRender(item_ptr, pos[count], ScalarToFloat2(1.0f), { 0,0 }, {64,64});
        //        break;
        //    default:
        //
        //        break;
        //    }
        //    count++;
        //}
    }

};
*/
