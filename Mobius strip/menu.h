#pragma once
#include "common.h"
#include "AliceLib/AliceLib.h"

enum MenuTab
{
    Item, // �A�C�e����
    Memo, // ������
    Exit, // �^�C�g���ɖ߂�
    Back, // �Q�[���ɖ߂�
};

class Item
{
private:
    FLOAT2 pos = {0,0};   // �\���ʒu
    FLOAT2 scale; // �\���T�C�Y
    bool HasItem[5]; // �A�C�e���������Ƃ邩
    int get_order[5]; // �A�C�e���l����(��������Ȃ�)

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