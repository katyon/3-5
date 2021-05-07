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

    //update�ł͐�΂ɌĂ΂Ȃ�����
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

