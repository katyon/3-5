#pragma once
#include "AliceLib/AliceLib.h"

class Reticle
{
public:
	enum RETICLE_TYPE
	{
		CROSS_HAIR,
		LOUPE,
		EXIT
	};

private:
	Reticle();
	RETICLE_TYPE current_type;

	Sprite spr;

public:

	void setReticleType(RETICLE_TYPE type) { current_type = type; }
	RETICLE_TYPE getReticleType() { return current_type; }

	void Render();

	static Reticle* getInstance()
	{
		static Reticle instance;
		return &instance;
	}
};