#pragma once
#include "./AliceLib/AliceLib.h"

//******************************** 
// 　キャンドルはR1に配置する
//********************************

class Candle
{
private:
    SkinnedMesh Candle_full;
    SkinnedMesh Candle_half;
    SkinnedMesh Candle_lost;

    FLOAT3 position;
    FLOAT3 scale;
    Quaternion posture;

public:
    bool full_Flg = false;
    bool half_Flg = false;
    bool lost_Flg = false;

    Candle();

    void Init();
    void Update();
    void Render(const Camera& camera);
    void Release();

    static Candle* getInstance()
    {
        static Candle instance;
        return &instance;
    }
};