#include "menu.h"
/*************************************************/
/*                      初期化                   */
/*************************************************/
ItemArr itemarr;
void ItemArr::init()
{
    SpriteLoad(item_ptr, L"Data/Sprite/item.png");
    reset();

    pos[0].x = 315.0f;
    pos[0].y = 286.0f;
    pos[1].x = 480.0f;
    pos[1].y = 286.0;
    pos[2].x = 645.0f;
    pos[2].y = 286.0;
}

void Menu::init()
{
    SpriteLoad(menu_ptr, L"Data/Sprite/menu.png");
    tab = MenuTab::Item;
    content = HelpContent::None;
    isPause = false;


}

/*************************************************/
/*                    更　新                     */
/*************************************************/
// アイテムが選択されたかどうかの処理
// 同じような処理いっぱい並べちゃった
void ItemMenu::isChoice()
{
    if (!input::TRG(VK_LBUTTON))return;

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        if (ColRects(arr->pos[i].y, arr->pos[i].y + 120.0f, arr->pos[i].x, arr->pos[i].x + 120.0f, input::GetMousePos()) && input::TRG(VK_LBUTTON))
        {
            switch (arr->items[i])
            {
            case ID_ITEM1:
                arr->isobserve[ID_ITEM1] = true;
                arr->isobserve[ID_ITEM2] = false;
                arr->isobserve[ID_ITEM3] = false;
                arr->isobserve[ID_ITEM4] = false;
                break;

            case ID_ITEM2:
                arr->isobserve[ID_ITEM1] = false;
                arr->isobserve[ID_ITEM2] = true;
                arr->isobserve[ID_ITEM3] = false;
                arr->isobserve[ID_ITEM4] = false;
                break;

            case ID_ITEM3:
                arr->isobserve[ID_ITEM1] = false;
                arr->isobserve[ID_ITEM2] = false;
                arr->isobserve[ID_ITEM3] = true;
                arr->isobserve[ID_ITEM4] = false;
                break;

            case ID_ITEM4:
                arr->isobserve[ID_ITEM1] = false;
                arr->isobserve[ID_ITEM2] = false;
                arr->isobserve[ID_ITEM3] = false;
                arr->isobserve[ID_ITEM4] = true;
                break;

            case ID_EMPTY:
                break;
            }
        }
    }
}

void ItemMenu::init()
{
    arr->init();
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
                    arr->isobserve[i] = false;
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
                    arr->isobserve[i] = false;
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
        }
        break;
    }
    if (input::TRG(VK_LBUTTON))
    {
        if (ColRects(50, 140, 100, 190, input::GetMousePos()))
        {
            isPause = false;
        }
        if (ColRects(366, 470, 1248, 1498, input::GetMousePos()))
        {
            ChangeScene(S_TITLE);
        }
        if (ColRects(669, 775, 1248, 1418, input::GetMousePos()))
        {
            content = HelpContent::None;
        }
    }
}


/*************************************************/
/*                    描　画                     */
/*************************************************/
void ItemMenu::draw()
{
    Debug->SetString("存在[0]:%d", arr->exist[0]);

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        if (!arr->exist[i])
        {
            switch (arr->items[i])
            {
            case ID_ITEM1:
                SpriteRender(arr->item_ptr, arr->pos[0].x, arr->pos[0].y, 0.4f, 0.5f, 0, 0, 256, 256, 0, 0, 0, 1, 1, 1, 1);
                if (arr->isobserve[ID_ITEM1])
                {
                    SpriteRender(arr->item_ptr, 900, 286, 3, 3, 0, 0, 256, 256, 0, 0, 0, 1, 1, 1, 1);
                }
                break;

            case ID_ITEM2:
                SpriteRender(arr->item_ptr, arr->pos[1].x, arr->pos[1].y, 0.4f, 0.5f, 256, 0, 256, 256, 0, 0, 0, 1, 1, 1, 1);
                if (arr->isobserve[ID_ITEM2])
                {
                    SpriteRender(arr->item_ptr, 900, 286, 3, 3, 256, 0, 120, 256, 0, 0, 0, 1, 1, 1, 1);
                }
                break;

            case ID_ITEM3:
                SpriteRender(arr->item_ptr, arr->pos[2].x, arr->pos[2].y, 0.4f, 0.5f, 512, 0, 256, 256, 0, 0, 0, 1, 1, 1, 1);
                if (arr->isobserve[ID_ITEM3])
                {
                    SpriteRender(arr->item_ptr, 900, 285, 3, 3, 512, 0, 256, 256, 0, 0, 0, 1, 1, 1, 1);
                }
                break;

            case ID_EMPTY:
                break;
            }
        }
        break;
    }
           
}

void Menu::draw()
{
    Debug->SetString("isPause:%d", isPause);
    Debug->SetString("page:%d", page);
    switch (tab)
    {
    case MenuTab::Item:
        SpriteRender(menu_ptr, 0, 0, 1, 1, src.x, src.y, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
        M_Item->draw();
        break;

    case MenuTab::Memo:
        SpriteRender(menu_ptr, 0, 0, 1, 1, src.x, src.y, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
        SpriteRender(menu_ptr, 170, 515, -0.5f, 0.5f, 1920, 2160, 256, 256, 0, 0, 0, 1, 1, 1, 1);
        SpriteRender(menu_ptr, 1725, 515, 0.5f, 0.5f, 1920, 2160, 256, 256, 0, 0, 0, 1, 1, 1, 1);

        for (int i = 0; i < screenR->max_racord; i++)
        {
            if (screenR->records[i]) // もしデータが入ってたら
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

    case MenuTab::Help:
        switch (content)
        {
        case HelpContent::None:
            SpriteRender(menu_ptr, 0, 0, 1, 1, 3840, 0, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            break;

        case HelpContent::Option:
            SpriteRender(menu_ptr, 0, 0, 1, 1, 0, 1080, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            break;

        case HelpContent::Ctrl:
            SpriteRender(menu_ptr, 0, 0, 1, 1, 1920, 1080, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            break;

        case HelpContent::Exit:
            SpriteRender(menu_ptr, 0, 0, 1, 1, 3840, 1080, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            SpriteRender(menu_ptr, 1248, 366, 0.8, 0.8, 0, 2160, 250, 104, 0, 0, 0, 1, 1, 1, 1);
            if (ColRects(366, 470, 1248, 1498, input::GetMousePos()))
            {
                SpriteRender(menu_ptr, 1248, 366, 0.8, 0.8, 251, 2160, 250, 104, 0, 0, 0, 1, 1, 1, 1);
            }
            SpriteRender(menu_ptr, 1280, 669, 0.8, 0.8, 536, 2160, 170, 106, 0, 0, 0, 1, 1, 1, 1);
            if (ColRects(669, 775, 1248, 1418, input::GetMousePos()))
            {
                SpriteRender(menu_ptr, 1280, 669, 0.8, 0.8, 784, 2160, 170, 106, 0, 0, 0, 1, 1, 1, 1);
            }
            break;
        }
        Selected();
        break;
    }
    if (ColRects(50, 140, 100, 190, input::GetMousePos()))
    {
        SpriteRender(menu_ptr, 98, 51, 0.5f, 0.5f, 195, 2266, 205, 192, 0, 0, 0, 1, 1, 1, 1);
    }
    else
    {
        SpriteRender(menu_ptr, 100, 50, 0.5f, 0.5f, 0, 2266, 192, 192, 0, 0, 0, 1, 1, 1, 1);
    }
}


/*************************************************/
/*                     終了                      */
/*************************************************/
void Menu::uninit()
{

}