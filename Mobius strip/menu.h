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
    int page = 0;
    int remainder = 0;

    void ScreenShot(int num)
    {
        for (int i = 0; i < screenR->max_racord; i++)
        {
            if (i % 4 == 0) SpriteRender(screenR->records[num], 257, 220, 0.3f, 0.3f, 0, 0, screenR->ScreenSize.x, screenR->ScreenSize.y, 0, 0, 0, 1, 1, 1, 1);
            if (i % 4 == 1) SpriteRender(screenR->records[num + 1], 257, 581, 0.3f, 0.3f, 0, 0, screenR->ScreenSize.x, screenR->ScreenSize.y, 0, 0, 0, 1, 1, 1, 1);
            if (i % 4 == 2) SpriteRender(screenR->records[num + 2], 1060, 220, 0.3f, 0.3f, 0, 0, screenR->ScreenSize.x, screenR->ScreenSize.y, 0, 0, 0, 1, 1, 1, 1);
            if (i % 4 == 3)SpriteRender(screenR->records[num + 3], 1060, 581, 0.3f, 0.3f, 0, 0, screenR->ScreenSize.x, screenR->ScreenSize.y, 0, 0, 0, 1, 1, 1, 1);
        }
    }

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