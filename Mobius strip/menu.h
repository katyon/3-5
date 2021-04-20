#pragma once
#include "common.h"
#include "AliceLib/AliceLib.h"
#include "Item.h"
#include "ScreenRecord.h"

enum MenuTab
{
    Item, // アイテム欄
    Memo, // メモ欄
    Help,
};

enum HelpContent
{
    Option,  // オプション
    Ctrl,    // 操作説明
    Exit,    // タイトルへ
    None,
};


class Menu
{
private:
    Sprite menu_ptr;
    FLOAT2 pos;
    FLOAT2 src;

    void Sele_Option()
    {
        if (ColRects(300, 390, 300, 780, input::GetMousePos()))
        {
            SpriteRender(menu_ptr, 246, 287, 1, 1, 960, 2160, 592, 115, 0, 0, 0, 1, 1, 1, 1);
        }
    }
    void Sele_Ctrl()
    {
        if (ColRects(515, 605, 300, 780, input::GetMousePos()))
        {
            SpriteRender(menu_ptr, 243, 500, 1, 1, 960, 2160, 592, 115, 0, 0, 0, 1, 1, 1, 1);
        }
    }
    void Sele_Exit()
    {
        if (ColRects(710, 800, 300, 780, input::GetMousePos()))
        {
            SpriteRender(menu_ptr, 243, 699, 1, 1, 960, 2160, 592, 115, 0, 0, 0, 1, 1, 1, 1);
        }
    }
    void Sele_None()
    {
        Sele_Option();
        Sele_Ctrl();
        Sele_Exit();
    }

    void Selected()
    {
        switch (content)
        {
        case HelpContent::Option:
            Sele_Ctrl();
            Sele_Exit();
            break;

        case HelpContent::Ctrl:
            Sele_Option();
            Sele_Exit();
            break;

        case HelpContent::Exit:
            Sele_Option();
            Sele_Ctrl();
            break;

        case HelpContent::None:
            Sele_None();
            break;
        }
    }

public:
    bool isPause;
    int tab;
    int content;
    void init();
    void update();
    void draw();
    void uninit();

};