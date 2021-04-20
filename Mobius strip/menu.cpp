#include "menu.h"
/*************************************************/
/*                      ������                   */
/*************************************************/

void ItemArr::init()
{ 
    SpriteLoad(item_ptr, L"Data/Sprite/item.png");
    reset();

}

void Menu::init()
{
    SpriteLoad(menu_ptr, L"Data/Sprite/menu.png");
    tab = MenuTab::Item;
    content = HelpContent::None;
    isPause = false;
}

/*************************************************/
/*                    �X�@�V                     */
/*************************************************/
// �A�C�e�����I�����ꂽ���ǂ����̏���
// �����悤�ȏ��������ς����ׂ������
void ItemMenu::isChoice()
{
    if (!input::TRG(VK_LBUTTON))return;

    for (int i=0;i<ITEM_MAX;i++)
    {
        if (ColRects(pos[i].y, pos[i].y + 120.0f, pos[i].x, pos[i].x + 120.0f, input::GetMousePos()) && input::TRG(VK_LBUTTON))
        {
           /* switch (items[i])
            {
            case ID_ITEM1:
                isobserve[ID_ITEM1] = true;
                isobserve[ID_ITEM2] = false;
                isobserve[ID_ITEM3] = false;
                isobserve[ID_ITEM4] = false;
                break;

            case ID_ITEM2:
                isobserve[ID_ITEM1] = false;
                isobserve[ID_ITEM2] = true;
                isobserve[ID_ITEM3] = false;
                isobserve[ID_ITEM4] = false;
                break;

            case ID_ITEM3:
                isobserve[ID_ITEM1] = false;
                isobserve[ID_ITEM2] = false;
                isobserve[ID_ITEM3] = true;
                isobserve[ID_ITEM4] = false;
                break;

            case ID_ITEM4:
                isobserve[ID_ITEM1] = false;
                isobserve[ID_ITEM2] = false;
                isobserve[ID_ITEM3] = false;
                isobserve[ID_ITEM4] = true;
                break;

            case ID_EMPTY:
                break;
            }*/
            switch (use_item(i))
            {
            case ID_ITEM1:
                break;
            case ID_ITEM2:
                break;
            case ID_ITEM3:
                break;
            case ID_ITEM4:
                break;
            case ID_EMPTY:
                break;
            }
        }
    }
}

// ���j���[��ʂɕ\�������A�C�e����
// �Q�[�����ł̏����ƘA��������
void ItemMenu::update()
{
    if (input::TRG('Q'))
    {
        get_item(ITEM_ID::ID_ITEM1);
    }
    if (input::TRG('W'))
    {
        get_item(ITEM_ID::ID_ITEM2);
    }
    if (input::TRG('E'))
    {
        get_item(ITEM_ID::ID_ITEM3);
    }
    if (input::TRG('R'))
    {
        get_item(ITEM_ID::ID_ITEM4);
    }
    ItemMenu::isChoice();
}


// �y�[�W�؂�ւ��Ɗe�y�[�W�ł̏���
void Menu::update()
{

    switch (tab)
    {
    case MenuTab::Item:
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
            if (i % 4 == 0 && screenR->records[i])
            {
                if (ColRects(400, 500, 200, 300, input::GetMousePos()))
                {

                }
            }
        }

        if (input::TRG(VK_LBUTTON))
        {
            if (ColRects(100, 165, 1080, 1230, input::GetMousePos()))
            {
                for (auto i : ItemMenu::getInstance()->items)
                {
                    ItemMenu::getInstance()->isobserve[i] = false;
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
                for (auto i : ItemMenu::getInstance()->items)
                {
                    ItemMenu::getInstance()->isobserve[i] = false;
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
    if(input::TRG(VK_LBUTTON))
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
/*                    �`�@��                     */
/*************************************************/
void ItemMenu::draw()
{
    for (int i = 0; i < ITEM_MAX; i++)
    {
        switch (items[i])
        {
        case ID_ITEM1:
            SpriteRender(item_ptr, pos[i].x, pos[i].y, 1, 1, 0, 0, 120, 120, 0, 0, 0, 1, 1, 1, 1);
            if (isobserve[ID_ITEM1])
            {
                SpriteRender(item_ptr, 900, 300, 4, 4, 0, 0, 120, 120, 0, 0, 0, 1, 1, 1, 1);
            }
            break;

        case ID_ITEM2:
            SpriteRender(item_ptr, pos[i].x, pos[i].y, 1, 1, 120, 0, 120, 120, 0, 0, 0, 1, 1, 1, 1);
            if (isobserve[ID_ITEM2])
            {
                SpriteRender(item_ptr, 1000, 300, 4, 4, 120, 0, 120, 120, 0, 0, 0, 1, 1, 1, 1);
            }
            break;

        case ID_ITEM3:
            SpriteRender(item_ptr, pos[i].x, pos[i].y, 1, 1, 240, 0, 120, 120, 0, 0, 0, 1, 1, 1, 1);
            if (isobserve[ID_ITEM3])
            {
                SpriteRender(item_ptr, 1100, 300, 4, 4, 240, 0, 120, 120, 0, 0, 0, 1, 1, 1, 1);
            }
            break;

        case ID_ITEM4:
            SpriteRender(item_ptr, pos[i].x, pos[i].y, 1, 1, 0, 120, 120, 120, 0, 0, 0, 1, 1, 1, 1);
            if (isobserve[ID_ITEM4])
            {
                SpriteRender(item_ptr, 1200, 300, 4, 4, 0, 120, 120, 120, 0, 0, 0, 1, 1, 1, 1);
            }
            break;

        case ID_EMPTY:
            break;
        }
    }
}

void Menu::draw()
{
        Debug->SetString("isPause:%d", isPause);
        switch (tab)
        {
        case MenuTab::Item:
            SpriteRender(menu_ptr, 0, 0, 1, 1, src.x, src.y, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            ItemMenu::getInstance()->draw();
            break;

        case MenuTab::Memo:
            SpriteRender(menu_ptr, 0, 0, 1, 1, src.x, src.y, 1920, 1080, 0, 0, 0, 1, 1, 1, 1);
            SpriteRender(menu_ptr, 170, 515, -0.5f, 0.5f, 1920, 2160, 256, 256, 0, 0, 0, 1, 1, 1, 1);
            SpriteRender(menu_ptr, 1725, 515, 0.5f, 0.5f, 1920, 2160, 256, 256, 0, 0, 0, 1, 1, 1, 1);
            for (int i = 0; i < screenR->max_racord; i++)
            {
                if (screenR->records[i])
                {
                    // ����
                    if (i % 4 == 1)
                    {
                        SpriteRender(screenR->records[i], 257, 220, 0.3f, 0.3f, 0, 0, screenR->ScreenSize.x, screenR->ScreenSize.y, 0, 0, 0, 1, 1, 1, 1);
                    }
                    // ����
                    else if (i % 4 == 2)
                    {
                        SpriteRender(screenR->records[i], 257, 581, 0.3f, 0.3f, 0, 0, screenR->ScreenSize.x, screenR->ScreenSize.y, 0, 0, 0, 1, 1, 1, 1);
                    }
                    // �E��
                    else if (i % 4 == 3)
                    {
                        SpriteRender(screenR->records[i], 1060, 220, 0.3f, 0.3f, 0, 0, screenR->ScreenSize.x, screenR->ScreenSize.y, 0, 0, 0, 1, 1, 1, 1);
                    }
                    // �E��
                    else if (i % 4 == 0)
                    {
                        SpriteRender(screenR->records[i], 1060, 581, 0.3f, 0.3f, 0, 0, screenR->ScreenSize.x, screenR->ScreenSize.y, 0, 0, 0, 1, 1, 1, 1);
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
/*                     �I��                      */
/*************************************************/
void Menu::uninit()
{

}