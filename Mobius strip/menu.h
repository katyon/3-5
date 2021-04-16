#pragma once
#include "common.h"
#include "AliceLib/AliceLib.h"

enum MenuTab
{
    Item, // アイテム欄
    Memo, // メモ欄
    Exit, // タイトルに戻る
    Back, // ゲームに戻る
};

class Item
{
private:
    FLOAT2 pos = {0,0};   // 表示位置
    FLOAT2 scale; // 表示サイズ
    bool HasItem[5]; // アイテムを持っとるか
    int get_order[5]; // アイテム獲得順(注文じゃない)

public:
    void init();
    void update();
    void draw();
    void uninit();
};

class Menu
{
private:
    FLOAT2 pos;
    FLOAT2 scale;
    int tab;

public:
    void init();
    void update();
    void draw();
    void uninit();


};