#pragma once

#include "AliceLib/AliceLib.h"
#include "AliceLib/Texture.h"
#include <vector>

class ScreenRecord :public TempTool
{
public:
    static constexpr int max_racord = 32;
    Sprite		records[max_racord];
    FLOAT2		ScreenSize;

private:
    struct GrayCbuffer
    {
        COLOR gray = { 0.299f, 0.587f, 0.114f,0.0f };
    };
    struct BrightnessCBuffer
    {
        float	ContrastWeight = 3.25f;	//コントラスト調整
        float	Bright = 1.0f;			//明度調整
        float	threshold = 0.525f;		//閾値
        int		flg = 1;
    };
    const BrightnessCBuffer luminance_level[5] =
    {
        {3.65f,1.10f,0.70f ,1},
        {3.75f,1.00f,0.50f ,1},
        {3.50f,1.00f,0.50f ,1},
        {3.75f,1.35f,0.60f ,1},
        {4.25f,1.60f,0.50f ,1}
    };

    int level = 2;

    ConstantBuffer<GrayCbuffer> cbuff;
    ConstantBuffer<BrightnessCBuffer> cbuff2;
    Texture		mask;
    Shaders		mask_ps;
    Shaders     brightness_ps;
    framebuffer buffer;
    
    //ID3D11ShaderResourceView* test = nullptr;
public:
    ScreenRecord()
    {
        mask.Load(L"Data/Sprite/mask.dds");
        brightness_ps.LoadPixelShader("Data/shader/Increase_brightness_ps.cso");
        mask_ps.LoadPixelShader("Data/shader/mask_ps.cso");
        ScreenSize = AliceLib::GetWindowSize();
        buffer.init(static_cast<int>(ScreenSize.x), static_cast<int>(ScreenSize.y));
        cbuff.CreateConstantBuffer();
        cbuff2.CreateConstantBuffer();
    }
    ~ScreenRecord()
    {
        //SafeRelease(test);
    }

    void init();
    //処理的には呼ばれたタイミングの1フレーム前の物を使用する
    bool save(int);
    bool erasure(int);

    //updateでは絶対に呼ばないこと
    void begin();
    void end();

    //level = 0~4
    void ChangeBrightness(int level)
    {
        this->level = Clamp<int>(level, 0, 4);
        (*cbuff2.GetData()) = luminance_level[this->level];
    }
    
    const int& getLevel()const
    {
        return level;
    }

    bool Whiteout(float);

    void _edit();

    //void demoPlay();
    static ScreenRecord* getInstance()
    {
        static ScreenRecord ins;
        return &ins;
    }
};

#define screenR ScreenRecord::getInstance() 

