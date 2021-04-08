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
	//処理的には呼ばれたタイミングの1フレーム前の物を使用する
	void save(int);

	//updateでは絶対に呼ばないこと
	void begin();
	void end();

	void demoPlay();

};

