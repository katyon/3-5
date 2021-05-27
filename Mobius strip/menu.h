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
    FLOAT2 pos;
    FLOAT2 src;
    FLOAT2 value_pos[4]; // 黒棒の位置
    FLOAT2 arrow_pos; // ←→の位置
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
            SpriteRender(menu_ptr, 246, 287, 1, 1, 536, 2160, 592, 115, 0, 0, 0, 1, 1, 1, 1);
        }
    }
    void Sele_Ctrl()
    {
        if (ColRects(515, 605, 300, 780, input::GetMousePos()))
        {
            SpriteRender(menu_ptr, 243, 500, 1, 1, 536, 2160, 592, 115, 0, 0, 0, 1, 1, 1, 1);
        }
    }
    void Sele_Exit()
    {
        if (ColRects(710, 800, 300, 780, input::GetMousePos()))
        {
            SpriteRender(menu_ptr, 243, 699, 1, 1, 536, 2160, 592, 115, 0, 0, 0, 1, 1, 1, 1);
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
    Sprite menu_ptr;
    float volumeSE;
    float volumeBGM;
    int tab;
    int content;
    void init();
    void volume(float type, int num);
    void update();
    void draw();
    void uninit();

    static Menu* getInstance()
    {
        static Menu ins;
        return &ins;
    }
};
#define menu Menu::getInstance()