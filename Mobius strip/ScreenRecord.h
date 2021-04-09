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
	//処理的には呼ばれたタイミングの1フレーム前の物を使用する
	bool save(int);

	//updateでは絶対に呼ばないこと
	void begin();
	void end();

	//void demoPlay();

};

