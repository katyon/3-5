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
        float	ContrastWeight = 3.25f;	//�R���g���X�g����
        float	Bright = 1.0f;			//���x����
        float	threshold = 0.525f;		//臒l
        int		flg = 1;
    };
    const BrightnessCBuffer luminance_level[5] =
    {
        {3.65f,1.10f,0.70f ,1},
        {3.75f,1.00f,0.55f ,1},
        {3.25f,1.00f,0.525f ,1},
        {4.25f,1.35f,0.50f ,1},
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
        init();
    }
    ~ScreenRecord()
    {
        //SafeRelease(test);
    }

    void init();
    //�����I�ɂ͌Ă΂ꂽ�^�C�~���O��1�t���[���O�̕����g�p����
    bool save(int);
    bool erasure(int);

    //update�ł͐�΂ɌĂ΂Ȃ�����
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

    void _edit();

    //void demoPlay();
    static ScreenRecord* getInstance()
    {
        static ScreenRecord ins;
        return &ins;
    }
};

#define screenR ScreenRecord::getInstance() 

