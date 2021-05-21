#include "menu.h"
#include "SceneGame.h"
/*************************************************/
/*                      ������                   */
/*************************************************/
void ItemArr::init()
{
    reset();
}

void ItemMenu::init()
{
    arr->init();
    SpriteLoad(menuItem.itemSpec[0].ptr, L"Data/Sprite/esc1.png");     // ID_Esc1
    SpriteLoad(menuItem.itemSpec[1].ptr, L"Data/Sprite/esc2.png");     // ID_Esc2     
    SpriteLoad(menuItem.itemSpec[2].ptr, L"Data/Sprite/ward.png");     // ID_Stone1   
    SpriteLoad(menuItem.itemSpec[3].ptr, L"Data/Sprite/ward.png");     // ID_Stone2   
    SpriteLoad(menuItem.itemSpec[4].ptr, L"Data/Sprite/ward.png");     // ID_Pipe3   
    SpriteLoad(menuItem.itemSpec[5].ptr, L"Data/Sprite/balance1.png"); // ID_Balance1 
    SpriteLoad(menuItem.itemSpec[6].ptr, L"Data/Sprite/balance2.png"); // ID_Balance2 
    SpriteLoad(menuItem.itemSpec[7].ptr, L"Data/Sprite/balance3.png"); // ID_Balance3 
    SpriteLoad(menuItem.itemSpec[8].ptr, L"Data/Sprite/ward.png");     // ID_SafetyBox
    SpriteLoad(menuItem.itemSpec[9].ptr, L"Data/Sprite/omori.png");    // ID_Weight
    SpriteLoad(menuItem.itemSpec[10].ptr, L"Data/Sprite/omori.png");   // ID_Key   
 
    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        M_Item->menuItem.itemSpec[i].pos = { 318.0f + i * 162.0f,290.0f,0.0f };
    }
}

void Menu::init()
{
    SpriteLoad(menu_ptr, L"Data/Sprite/menu.png");
    tab = MenuTab::Item;
    content = HelpContent::None;
}

/*************************************************/
/*                    �X�@�V                     */
/*************************************************/
// �A�C�e�����I�����ꂽ���ǂ����̏���
void ItemMenu::isChoice()
{
    if (!input::TRG(VK_LBUTTON))return;

    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        if (menuItem.itemSpec[i].exist)
        {
            // �A�C�e�����̃A�C�e�����N���b�N������
            if (ColRects(menuItem.itemSpec[i].pos.y, menuItem.itemSpec[i].pos.y + 120.0f, menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.x + 120.0f, input::GetMousePos()) && input::TRG(VK_LBUTTON))
            {
                // �N���b�N���ꂽ�A�C�e�����傫���\�������
                switch (i)
                {
                case 0:
                    menuItem.itemSpec[0].isobserve = true;
                    menuItem.itemSpec[1].isobserve = false;
                    menuItem.itemSpec[2].isobserve = false;
                    menuItem.itemSpec[3].isobserve = false;
                    break;

                case 1:
                    menuItem.itemSpec[0].isobserve = false;
                    menuItem.itemSpec[1].isobserve = true;
                    menuItem.itemSpec[2].isobserve = false;
                    menuItem.itemSpec[3].isobserve = false;
                    break;

                case 2:
                    menuItem.itemSpec[0].isobserve = false;
                    menuItem.itemSpec[1].isobserve = false;
                    menuItem.itemSpec[2].isobserve = true;
                    menuItem.itemSpec[3].isobserve = false;
                    break;

                case 4:
                    menuItem.itemSpec[0].isobserve = false;
                    menuItem.itemSpec[1].isobserve = false;
                    menuItem.itemSpec[2].isobserve = false;
                    menuItem.itemSpec[3].isobserve = true;
                    break;

                default:
                    menuItem.itemSpec[i].isobserve = false;
                    break;
                }
            }
        }
    }
}


// ���j���[��ʂɕ\�������A�C�e����
// �Q�[�����ł̏����ƘA��������
void ItemMenu::update()
{
    isChoice();
}


// �y�[�W�؂�ւ��Ɗe�y�[�W�ł̏���
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
/*                    �`�@��                     */
/*************************************************/
void ItemMenu::draw()
{
    for (int i = 0; i < arr->ITEM_MAX; i++)
    {
        switch (arr->items[i])
        {
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

        case ItemArr::ITEM_ID::ID_Weight:
            SpriteRender(menuItem.itemSpec[9].ptr,
                menuItem.itemSpec[i].pos.x, menuItem.itemSpec[i].pos.y,
                0.3f, 0.4f,
                0, 0,
                256, 324,
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
        /* �A�C�e���y�[�W */
    case MenuTab::Item:
        SpriteRender(menu_ptr, 0, 0, 1, 1, src.x, src.y, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
        M_Item->draw();
        break;

        /* �X�N�V���y�[�W */
    case MenuTab::Memo:
        SpriteRender(menu_ptr, 0, 0, 1, 1, src.x, src.y, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
        SpriteRender(menu_ptr, 170, 515, -0.5f, 0.5f, 1152, 2160, 256, 256, 0, 0, 0, 1, 1, 1, 1);  // ���(��)
        SpriteRender(menu_ptr, 1725, 515, 0.5f, 0.5f, 1152, 2160, 256, 256, 0, 0, 0, 1, 1, 1, 1);  // ���(��)

        for (int i = 0; i < screenR->max_racord; i++)
        {
            if (screenR->records[i]) // �����f�[�^�������Ă���X�N�V���`��
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

        /* �w���v�y�[�W */
    case MenuTab::Help:
        switch (content)
        {
            /* �����I�𖳂� */
        case HelpContent::None:
            SpriteRender(menu_ptr, 0, 0, 1, 1, src.x, src.y, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            break;

            /* �I�v�V�����^�u */
        case HelpContent::Option:
            SpriteRender(menu_ptr, 0, 0, 1, 1, 0, 1080, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            break;

            /* ��������^�u */
        case HelpContent::Ctrl:
            SpriteRender(menu_ptr, 0, 0, 1, 1, 1920, 1080, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            break;

            /* �Q�[��Exit�^�u */
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
/*                     �I��                      */
/*************************************************/
void Menu::uninit()
{

}