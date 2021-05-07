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
        init();
    }
    ~ScreenRecord()
    {
        //SafeRelease(test);
    }

    void init();
    //処理的には呼ばれたタイミングの1フレーム前の物を使用する
    bool save(int);

    //updateでは絶対に呼ばないこと
    void begin();
    void end();

    void _edit();

    //void demoPlay();
    static ScreenRecord* getInstance()
    {
        static ScreenRecord ins;
        return &ins;
    }
};

#define screenR ScreenRecord::getInstance() 

