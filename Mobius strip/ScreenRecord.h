#pragma once

#include "AliceLib/AliceLib.h"
#include "AliceLib/Texture.h"
#include <vector>

class ScreenRecord:public TempTool
{
private:
	FLOAT2		ScreenSize;
	Sprite		records[32u];
	Texture		mask;
	Shaders		mask_ps;
	framebuffer buffer;
	ID3D11ShaderResourceView* test = nullptr;
public:

	~ScreenRecord()
	{
		SafeRelease(test);
	}

	void init();
	//�����I�ɂ͌Ă΂ꂽ�^�C�~���O��1�t���[���O�̕����g�p����
	void save(int);

	//update�ł͐�΂ɌĂ΂Ȃ�����
	void begin();
	void end();

	void demoPlay();

};

