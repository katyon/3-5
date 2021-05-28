#pragma once
#include "./AliceLib/AliceLib.h"

//******************************** 
// 　キャンドルはR1に配置する
//********************************

class Candle
{
private:

public:
    bool full_Flg = false;
    bool half_Flg = false;
    bool lost_Flg = false;

    Candle();

    void Init();
    void Update();

    int RenderFlg();

    static Candle* getInstance()
    {
        static Candle instance;
        return &instance;
    }
};