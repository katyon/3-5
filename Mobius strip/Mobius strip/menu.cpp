#include "menu.h"
#include "SceneGame.h"
/*************************************************/
/*                      初期化                   */
/*************************************************/
void ItemArr::init()
{
    reset();
}

void ItemMenu::init()
{
    arr->init();
    SpriteLoad(item2D.itemSpec[0].ptr, L"Data/Sprite/ward.png");
    SpriteLoad(item2D.itemSpec[1].ptr, L"Data/Sprite/omori.png");


    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        item2D.itemSpec[i].exist = false;
    }
    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        M_Item->item2D.itemSpec[i].pos = { 318.0f + i * 162.0f,290.0f,0.0f };
    }
    
}

void Menu::init()
{
    SpriteLoad(menu_ptr, L"Data/Sprite/menu.png");
    tab = MenuTab::Item;
    content = HelpContent::None;
}

/*************************************************/
/*                    更　新                     */
/*************************************************/
// アイテムが選択されたかどうかの処理
void ItemMenu::isChoice()
{
    if (!input::TRG(VK_LBUTTON))return;

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        // アイテム欄のアイテムをクリックしたら
        if (ColRects(item2D.itemSpec[i].pos.y, item2D.itemSpec[i].pos.y + 120.0f, item2D.itemSpec[i].pos.x, item2D.itemSpec[i].pos.x + 120.0f, input::GetMousePos()) && input::TRG(VK_LBUTTON))
        {
            // クリックされたアイテムが大きく表示される
            switch (i)
            {
            case 0:
                item2D.itemSpec[0].isobserve = true;
                item2D.itemSpec[1].isobserve = false;
                item2D.itemSpec[2].isobserve = false;
                item2D.itemSpec[3].isobserve = false;
                break;

            case 1:
                item2D.itemSpec[0].isobserve = false;
                item2D.itemSpec[1].isobserve = true;
                item2D.itemSpec[2].isobserve = false;
                item2D.itemSpec[3].isobserve = false;
                break;

            case 2:
                item2D.itemSpec[0].isobserve = false;
                item2D.itemSpec[1].isobserve = false;
                item2D.itemSpec[2].isobserve = true;
                item2D.itemSpec[3].isobserve = false;
                break;

            case 4:
                item2D.itemSpec[0].isobserve = false;
                item2D.itemSpec[1].isobserve = false;
                item2D.itemSpec[2].isobserve = false;
                item2D.itemSpec[3].isobserve = true;
                break;

            default:
                item2D.itemSpec[i].isobserve = false;
                break;
            }
        }
    }
}


// メニュー画面に表示されるアイテム版
// ゲーム内での処理と連動させる
void ItemMenu::update()
{
    isChoice();
}


// ページ切り替えと各ページでの処理
void Menu::update()
{
    switch (tab)
    {
    case MenuTab::Item:
        M_Item->update();
        src = { 0,0 };

        if (input::TRG(VK_LBUTTON))
        {
            if (ColRects(100, 165, 1330, 1500, input::GetMousePos()))
            {
                tab = MenuTab::Memo;
            }
            else if (ColRects(100, 165, 1525, 1695, input::GetMousePos()))
            {
                tab = MenuTab::Help;
                content = HelpContent::None;
            }
        }
        break;

    case MenuTab::Memo:
        src = { 1920,0 };

        for (int i = 0; i < screenR->max_racord; i++)
        {
            if (screenR->records[i])
            {
                if (ColRects(515, 638, 60, 170, input::GetMousePos()) && input::TRG(VK_LBUTTON))
                {
                    page--;
                    if (page < 0)
                    {
                        page = 0;
                    }
                    break;
                }
                else if (ColRects(515, 638, 1725, 1848, input::GetMousePos()) && input::TRG(VK_LBUTTON))
                {
                    page++;
                    if (page > 7)
                    {
                        page = 7;
                    }
                    break;
                }
            }
        }

        if (input::TRG(VK_LBUTTON))
        {
            if (ColRects(100, 165, 1080, 1230, input::GetMousePos()))
            {
                for (auto i : arr->items)
                {
                    M_Item->item2D.itemSpec[i].isobserve = false;
                }
                tab = MenuTab::Item;
            }
            else if (ColRects(100, 165, 1525, 1695, input::GetMousePos()))
            {
                tab = MenuTab::Help;
                content = HelpContent::None;
            }
        }
        break;

    case MenuTab::Help:
        src = { 3840,0 };
        if (input::TRG(VK_LBUTTON))
        {
            if (ColRects(100, 165, 1085, 1230, input::GetMousePos()))
            {
                for (auto i : arr->items)
                {
                    M_Item->item2D.itemSpec[i].isobserve = false;
                }
                tab = MenuTab::Item;
            }
            else if (ColRects(100, 165, 1260, 1440, input::GetMousePos()))
            {
                tab = MenuTab::Memo;
            }
            else if (ColRects(300, 390, 300, 780, input::GetMousePos()))
            {
                content = HelpContent::Option;
            }
            else if (ColRects(515, 605, 300, 780, input::GetMousePos()))
            {
                content = HelpContent::Ctrl;
            }
            else if (ColRects(710, 800, 300, 780, input::GetMousePos()))
            {
                content = HelpContent::Exit;
            }

            if (content == HelpContent::Exit)
            {
                if (ColRects(366, 470, 1248, 1498, input::GetMousePos()))
                {
                    ChangeScene(S_TITLE);
                    SceneGame::getInstance()->game_mode = SceneGame::getInstance()->normal;
                }
                if (ColRects(669, 775, 1248, 1418, input::GetMousePos()))
                {
                    content = HelpContent::None;
                }
            }
        }
        break;
    }

}


/*************************************************/
/*                    描　画                     */
/*************************************************/
void ItemMenu::draw()
{
    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        switch (arr->items[i])
        {
        case SPEC::ITEM_ID::ID_ITEM1:
            SpriteRender(item2D.itemSpec[0].ptr,
                item2D.itemSpec[i].pos.x, item2D.itemSpec[i].pos.y,
                0.05f, 0.06f,
                0,0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case SPEC::ITEM_ID::ID_ITEM2:
            SpriteRender(item2D.itemSpec[1].ptr,
                item2D.itemSpec[i].pos.x, item2D.itemSpec[i].pos.y,
                0.5f, 0.6f,
                0, 0,
                295, 354,
                0, 0,
                0,
                1, 1, 1, 1);
            break;
        }
    }
}
void Menu::draw()
{
    switch (tab)
    {
        /* アイテムページ */
    case MenuTab::Item:
        SpriteRender(menu_ptr, 0, 0, 1, 1, src.x, src.y, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
        M_Item->draw();
        break;

        /* スクショページ */
    case MenuTab::Memo:
        SpriteRender(menu_ptr, 0, 0, 1, 1, src.x, src.y, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
        SpriteRender(menu_ptr, 170, 515, -0.5f, 0.5f, 1152, 2160, 256, 256, 0, 0, 0, 1, 1, 1, 1);  // 矢印(←)
        SpriteRender(menu_ptr, 1725, 515, 0.5f, 0.5f, 1152, 2160, 256, 256, 0, 0, 0, 1, 1, 1, 1);  // 矢印(→)

        for (int i = 0; i < screenR->max_racord; i++)
        {
            if (screenR->records[i]) // もしデータが入ってたらスクショ描画
            {
                switch (page)
                {
                case 0:
                    ScreenShot(0);
                    break;

                case 1:
                    ScreenShot(4);
                    break;

                case 2:
                    ScreenShot(8);
                    break;

                case 3:
                    ScreenShot(12);
                    break;

                case 4:
                    ScreenShot(16);
                    break;

                case 5:
                    ScreenShot(20);
                    break;

                case 6:
                    ScreenShot(24);
                    break;

                case 7:
                    ScreenShot(28);
                    break;
                }
            }
        }
        break;

        /* ヘルプページ */
    case MenuTab::Help:
        switch (content)
        {
            /* 何も選択無し */
        case HelpContent::None:
            SpriteRender(menu_ptr, 0, 0, 1, 1, src.x, src.y, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            break;

            /* オプションタブ */
        case HelpContent::Option:
            SpriteRender(menu_ptr, 0, 0, 1, 1, 0, 1080, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            break;

            /* 操作説明タブ */
        case HelpContent::Ctrl:
            SpriteRender(menu_ptr, 0, 0, 1, 1, 1920, 1080, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            break;

            /* ゲームExitタブ */
        case HelpContent::Exit:
            SpriteRender(menu_ptr, 0, 0, 1, 1, 3840, 1080, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            // YES
            SpriteRender(menu_ptr, 1248, 366, 0.8, 0.8, 0, 2160, 250, 104, 0, 0, 0, 1, 1, 1, 1);
            if (ColRects(366, 470, 1248, 1498, input::GetMousePos()))
            {
                SpriteRender(menu_ptr, 1248, 366, 0.8, 0.8, 256, 2160, 250, 104, 0, 0, 0, 1, 1, 1, 1);
            }
            // NO
            SpriteRender(menu_ptr, 1280, 669, 0.8, 0.8, 40, 2272, 247, 106, 0, 0, 0, 1, 1, 1, 1);
            if (ColRects(669, 775, 1248, 1418, input::GetMousePos()))
            {
                SpriteRender(menu_ptr, 1280, 669, 0.8, 0.8, 296, 2272, 247, 106, 0, 0, 0, 1, 1, 1, 1);
            }
            break;
        }
        Selected();
        break;
    }
}


/*************************************************/
/*                     終了                      */
/*************************************************/
void Menu::uninit()
{

}