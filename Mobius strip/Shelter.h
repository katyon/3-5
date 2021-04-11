#pragma once

#include "AliceLib/AliceLib.h"

//ê¸Ç∆OBBÇÃåç∑îªíË
bool ColLineOBB(const FLOAT3& start, const FLOAT3& end, const OBB& obb, FLOAT3& hitPoint);
//AliceLibì‡ÇÃScreenToWorldä÷êîÇ™ä‘à·Ç¡ÇƒÇΩÇÃÇ≈
//ë„ÇÌÇËÇópà”ÇµÇ‹ÇµÇΩ
_NODISCARD FLOAT3 screen_to_world(const Camera& eye,const FLOAT3& screen_pos);

class Shelter
{
private://5*5

	int map[7][7]=
	{
		1,1,1,1,1,1,1,
		1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,
		1,0,0,0,0,0,1,
		1,1,1,1,1,1,1
	};

	enum SHELTER_STATE
	{
		SS_CHOICE,
		SS_CALCULATION,
		SS_MOVE,
		SS_REJUDGMENT
	};

	struct BLOCK
	{
		FLOAT3		pos;
		FLOAT3		size;
		Quaternion	angles;
	};

	int		state;
	FLOAT2	mouse_pos_o;
	static constexpr int BLOCK_MAX = 8;
	BLOCK	blocks[BLOCK_MAX];

	bool isClick(const Camera& eye,int& num);

public:

	void update();

};

