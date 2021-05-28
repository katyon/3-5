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
    SpriteLoad(menuItem.itemSpec[0].ptr, L"Data/Sprite/EscHint/esc1.png");         // ID_Esc1
    SpriteLoad(menuItem.itemSpec[1].ptr, L"Data/Sprite/EscHint/esc2.png");         // ID_Esc2     
    SpriteLoad(menuItem.itemSpec[2].ptr, L"Data/Sprite/StoneHint/stone1.png");     // ID_Stone1   
    SpriteLoad(menuItem.itemSpec[3].ptr, L"Data/Sprite/StoneHint/stone2.png");     // ID_Stone2   
    SpriteLoad(menuItem.itemSpec[4].ptr, L"Data/Sprite/pipe.png");                 // ID_Pipe
    SpriteLoad(menuItem.itemSpec[5].ptr, L"Data/Sprite/BalanceHint/balance1.png"); // ID_Balance1 
    SpriteLoad(menuItem.itemSpec[6].ptr, L"Data/Sprite/BalanceHint/balance2.png"); // ID_Balance2 
    SpriteLoad(menuItem.itemSpec[7].ptr, L"Data/Sprite/BalanceHint/balance3.png"); // ID_Balance3 
    SpriteLoad(menuItem.itemSpec[8].ptr, L"Data/Sprite/safety.png");               // ID_SafetyBox
    SpriteLoad(menuItem.itemSpec[9].ptr, L"Data/Sprite/omori.png");                // ID_Weight
    SpriteLoad(menuItem.itemSpec[10].ptr, L"Data/Sprite/key.png");               // ID_Key   

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        if (i % 3 == 0) { menuItem.itemSpec[i].pos.x = 318.0f; }
        if (i % 3 == 1) { menuItem.itemSpec[i].pos.x = 483.0f; }
        if (i % 3 == 2) { menuItem.itemSpec[i].pos.x = 645.0f; }

        if (i / 3 == 0) { menuItem.itemSpec[i].pos.y = 290.0f; }
        if (i / 3 == 1) { menuItem.itemSpec[i].pos.y = 520.0f; }
        if (i / 3 == 2) { menuItem.itemSpec[i].pos.y = 730.0f; }
    }
}

void Menu::init()
{
    SpriteLoad(menu_ptr, L"Data/Sprite/menu.png");
    tab = MenuTab::Item;
    content = HelpContent::None;
    value_pos[0] = { 1364,299 };
    value_pos[1] = { 1364,481 };
    value_pos[2] = { 1364,660 };
    value_pos[3] = { 1364,836 };
    arrow_pos = { 0,0 };
    volumeSE = 0.4f;
    volumeBGM = 0.4f;
}

/*************************************************/
/*                    更　新                     */
/*************************************************/
// アイテムが選択されたかどうかの処理
bool ItemMenu::isObserve(int num)
{
    if (!menuItem.itemSpec[num].isobserve)
    { 
        menuItem.itemSpec[num].isobserve = true; 
        for (int i = 0; i < arr->ITEM_MAX; i++)
        {
            if (i != num)
            {
                menuItem.itemSpec[i].isobserve = false;
            }
        }
        return true;
    }
    return false;
}

void ItemMenu::isChoice()
{
    if (!input::TRG(VK_LBUTTON))return;

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        // アイテム欄のアイテムをクリックしたら
        if (ColRects(menuItem.itemSpec[i].pos.y, menuItem.itemSpec[i].pos.y + 120.0f, menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.x + 120.0f, input::GetMousePos()) && input::TRG(VK_LBUTTON))
        {
            // クリックされたアイテムが大きく表示される
            switch (arr->items[i])
            {
            case SPEC::ITEM_ID::ID_Esc1:
                isObserve(0);
                break;

            case SPEC::ITEM_ID::ID_Esc2:
                isObserve(1);
                break;

            case SPEC::ITEM_ID::ID_Stone1:
                isObserve(2);
                break;

            case SPEC::ITEM_ID::ID_Stone2:
                isObserve(3);
                break;

            case SPEC::ITEM_ID::ID_Pipe3:
                isObserve(4);
                break;

            case SPEC::ITEM_ID::ID_Balance1:
                isObserve(5);
                break;

            case SPEC::ITEM_ID::ID_Balance2:
                isObserve(6);
                break;

            case SPEC::ITEM_ID::ID_Balance3:
                isObserve(7);
                break;

            case SPEC::ITEM_ID::ID_SafetyBox:
                isObserve(8);
                break;

            case SPEC::ITEM_ID::ID_Weight:
                isObserve(9);
                break;

            case SPEC::ITEM_ID::ID_Key:
                isObserve(10);
                break;

            default:
                menuItem.itemSpec[i].isobserve = false;
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
    Audio::SetVolume(1, volumeBGM);
    
    for (int i = 2; i < 7; i++)
    {
        Audio::SetVolume(i, volumeSE);
    }


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
                    M_Item->menuItem.itemSpec[i].isobserve = false;
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
                    M_Item->menuItem.itemSpec[i].isobserve = false;
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

            switch (content)
            {
            case HelpContent::Option:
                // マウス感度操作(←)
                if (ColRects(293, 341, 1100, 1165, input::GetMousePos()))
                {
                    if (input::TRG(VK_LBUTTON) && FPSCamera::correct_sensitivity > 0)
                    {
                        FPSCamera::correct_sensitivity--;
                        value_pos[0].x -= 38.0f;
                    }
                }
                //マウス感度操作(→)
                if (ColRects(293, 341, 1572, 1638, input::GetMousePos()))
                {
                    if (input::TRG(VK_LBUTTON) && FPSCamera::correct_sensitivity < 10)
                    {
                        FPSCamera::correct_sensitivity++;
                        value_pos[0].x += 38.0f;
                    }
                }

                // 画面明るさ(←)
                if (ColRects(475, 523, 1100, 1165, input::GetMousePos()))
                {

                }
                // 画面明るさ(→)
                if (ColRects(475, 523, 1572, 1637, input::GetMousePos()))
                {

                }

                // 効果音(←)
                if (ColRects(654, 702, 1100, 1165, input::GetMousePos()))
                {
                    if (volumeSE > 0.0f && input::TRG(VK_LBUTTON))
                    { 
                        value_pos[2].x -= 95.0f;
                        volumeSE -= 0.2f;

                        if (volumeSE <= 0.0f)
                        {
                            value_pos[2].x = 1174.0f;
                            volumeSE = 0.0f;
                        }
                    }
                }
                // 効果音(→)
                if (ColRects(654, 702, 1572, 1637, input::GetMousePos()))
                {
                    if (volumeSE < 0.8f && input::TRG(VK_LBUTTON))
                    {
                        value_pos[2].x += 95.0f;
                        volumeSE += 0.2f;
                    }
                }
                
                // BGM(←)
                if (ColRects(830, 878, 1100, 1165, input::GetMousePos())) 
                {
                    if (volumeBGM > 0.0f && input::TRG(VK_LBUTTON))
                    {
                        value_pos[3].x -= 95.0f;
                        volumeBGM -= 0.2f;

                        if (volumeBGM <= 0.0f)
                        {
                            value_pos[3].x = 1174.0f;
                            volumeBGM = 0.0f;
                        }
                    }
                }
                // BGM(→)
                if (ColRects(830, 878, 1572, 1637, input::GetMousePos()))
                {
                    if (volumeBGM < 0.8f && input::TRG(VK_LBUTTON))
                    {
                        value_pos[3].x += 95.0f;
                        volumeBGM += 0.2f;
                    }
                }

                break;

            case HelpContent::Exit:
                if (ColRects(366, 470, 1248, 1498, input::GetMousePos()))
                {
                    ChangeScene(S_TITLE);
                    SceneGame::getInstance()->game_mode = SceneGame::getInstance()->normal;
                }
                if (ColRects(669, 775, 1248, 1418, input::GetMousePos()))
                {
                    content = HelpContent::None;
                }
                break;
            }
        }
        break;
    }
}


/*************************************************/
/*                    描　画                     */
/*************************************************/
void ItemMenu::origin_Draw(int num)
{
    if (menuItem.itemSpec[num].isobserve) {
        SpriteRender(menuItem.itemSpec[num].ptr, 1189, 310, 0.2f, 0.27f, 0, 0, 2048, 2048, 0, 0, 0, 1, 1, 1, 1);
    }
}

void LeftArrow(FLOAT2 pos,int num)
{
    switch (num)
    {
    case 0:
        pos = { 1099, 293 };
        break;
    case 1:
        pos = { 1099, 475 };
        break;
    case 2:
        pos = { 1099, 654 };
        break;
    case 3:
        pos = { 1099, 830 };
        break;
    }
    SpriteRender(menu->menu_ptr, pos.x, pos.y, 1, 1, 0, 2371, 68, 51, 0, 0, 0, 1, 1, 1, 1);
}

void RightArrow(FLOAT2 pos,int num)
{
    switch (num)
    {
    case 0:
        pos = { 1572, 293 };
        break;
    case 1:
        pos = { 1572, 475 };
        break;
    case 2:
        pos = { 1572, 654 };
        break;
    case 3:
        pos = { 1572, 830 };
        break;
    }
    SpriteRender(menu->menu_ptr, pos.x, pos.y, 1, 1, 68, 2371, 68, 51, 0, 0, 0, 1, 1, 1, 1);
}

void Value(FLOAT2* pos,int num)
{
    SpriteRender(menu->menu_ptr, pos[num].x, pos[num].y, 1, 1, 0, 2422, 11, 37, 0, 0, 0, 1, 1, 1, 1);
}

void ItemMenu::draw()
{
    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        switch (arr->items[i])
        {
        case ItemArr::ITEM_ID::ID_Esc1:
            SpriteRender(menuItem.itemSpec[0].ptr,
                menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.y,
                0.05f, 0.06f,
                0, 0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case ItemArr::ITEM_ID::ID_Esc2:
            SpriteRender(menuItem.itemSpec[1].ptr,
                menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.y,
                0.05f, 0.06f,
                0, 0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case ItemArr::ITEM_ID::ID_Stone1:
            SpriteRender(menuItem.itemSpec[2].ptr,
                menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.y,
                0.05f, 0.06f,
                0, 0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case ItemArr::ITEM_ID::ID_Stone2:
            SpriteRender(menuItem.itemSpec[3].ptr,
                menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.y,
                0.05f, 0.06f,
                0, 0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case ItemArr::ITEM_ID::ID_Pipe3:
            SpriteRender(menuItem.itemSpec[4].ptr,
                menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.y,
                0.05f, 0.06f,
                0, 0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case ItemArr::ITEM_ID::ID_Balance1:
            SpriteRender(menuItem.itemSpec[5].ptr,
                menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.y,
                0.05f, 0.06f,
                0, 0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case ItemArr::ITEM_ID::ID_Balance2:
            SpriteRender(menuItem.itemSpec[6].ptr,
                menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.y,
                0.05f, 0.06f,
                0, 0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case ItemArr::ITEM_ID::ID_Balance3:
            SpriteRender(menuItem.itemSpec[7].ptr,
                menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.y,
                0.05f, 0.06f,
                0, 0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case ItemArr::ITEM_ID::ID_SafetyBox:
            SpriteRender(menuItem.itemSpec[8].ptr,
                menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.y,
                0.05f, 0.06f,
                0, 0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case ItemArr::ITEM_ID::ID_Weight:
            SpriteRender(menuItem.itemSpec[9].ptr,
                menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.y,
                0.05f, 0.06f,
                0, 0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);
            break;

        case ItemArr::ITEM_ID::ID_Key:
            SpriteRender(menuItem.itemSpec[10].ptr,
                menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.y,
                0.05f, 0.06f,
                0, 0,
                2048, 2048,
                0, 0,
                0,
                1, 1, 1, 1);
            break;
        }
        origin_Draw(i);
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
        if (page != 0)SpriteRender(menu_ptr, 170, 515, -0.5f, 0.5f, 1152, 2160, 256, 256, 0, 0, 0, 1, 1, 1, 1);  // 矢印(←)
        if (page != 7)SpriteRender(menu_ptr, 1725, 515, 0.5f, 0.5f, 1152, 2160, 256, 256, 0, 0, 0, 1, 1, 1, 1);  // 矢印(→)

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
            Debug->SetString("volumeSE:%f",volumeSE);
            Debug->SetString("volumeBGM:%f", volumeBGM);
            SpriteRender(menu_ptr, 0, 0, 1, 1, 0, 1080, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);


            /*   感度   */
            /************/
            // ←のところにカーソルが合ったら
            if (ColRects(293, 341, 1100, 1165, input::GetMousePos())) { LeftArrow(arrow_pos,0); }
            // →のところにカーソルが合ったら
            if (ColRects(293, 341, 1572, 1637, input::GetMousePos())) { RightArrow(arrow_pos, 0); }
            // 黒棒
            Value(value_pos, 0);

            /*  明るさ  */
            /************/
             // ←のところにカーソルが合ったら
            if (ColRects(475, 523, 1100, 1165, input::GetMousePos())) { LeftArrow(arrow_pos, 1); }
            // →のところにカーソルが合ったら
            if (ColRects(475, 523, 1572, 1637, input::GetMousePos())) { RightArrow(arrow_pos, 1); }
            // 黒棒
            Value(value_pos, 1);

            /*  効果音  */
            /************/
            // ←のところにカーソルが合ったら
            if (ColRects(654, 702, 1100, 1165, input::GetMousePos())) { LeftArrow(arrow_pos, 2); }
            // →のところにカーソルが合ったら
            if (ColRects(654, 702, 1572, 1637, input::GetMousePos())) { RightArrow(arrow_pos, 2); }
            // 黒棒
            Value(value_pos, 2);

            /*    BGM   */
            /************/
            // ←のところにカーソルが合ったら
            if (ColRects(830, 878, 1100, 1165, input::GetMousePos())) { LeftArrow(arrow_pos, 3); }
            // →のところにカーソルが合ったら
            if (ColRects(830, 878, 1572, 1637, input::GetMousePos())) { RightArrow(arrow_pos, 3); }
            // 黒棒
            Value(value_pos, 3);


            break;

            /* 操作説明タブ */
        case HelpContent::Ctrl:
            SpriteRender(menu_ptr, 0, 0, 1, 1, 1920, 1080, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            break;

            /* ゲームExitタブ */
        case HelpContent::Exit:
            SpriteRender(menu_ptr, 0, 0, 1, 1, 3840, 1080, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            // YES
            SpriteRender(menu_ptr, 1248, 366, 0.8, 0.8, 0, 2160, 250, 110, 0, 0, 0, 1, 1, 1, 1);
            if (ColRects(366, 470, 1248, 1498, input::GetMousePos()))
            {
                SpriteRender(menu_ptr, 1248, 366, 0.8, 0.8, 256, 2160, 250, 110, 0, 0, 0, 1, 1, 1, 1);
            }
            // NO
            SpriteRender(menu_ptr, 1280, 669, 0.8, 0.8, 40, 2272, 247, 98, 0, 0, 0, 1, 1, 1, 1);
            if (ColRects(669, 775, 1248, 1418, input::GetMousePos()))
            {
                SpriteRender(menu_ptr, 1280, 669, 0.8, 0.8, 296, 2272, 247, 98, 0, 0, 0, 1, 1, 1, 1);
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