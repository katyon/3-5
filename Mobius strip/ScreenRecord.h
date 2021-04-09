#pragma once

#include "AliceLib/AliceLib.h"
#include "AliceLib/Texture.h"
#include <vector>

class ScreenRecord:public TempTool
{
public:
	static constexpr int max_racord = 32;
private:

	struct GrayCbuffer
	{
		COLOR gray = { 0.299f, 0.587f, 0.114f,0.0f };
	};
	ConstantBuffer<GrayCbuffer> cbuff;
	FLOAT2		ScreenSize;
	Sprite		records[max_racord];
	Texture		mask;
	Shaders		mask_ps;
	framebuffer buffer;
	//ID3D11ShaderResourceView* test = nullptr;
public:

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

	//void demoPlay();

};

