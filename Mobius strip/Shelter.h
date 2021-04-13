#pragma once

#include "AliceLib/AliceLib.h"
#include <fstream>

//線とOBBの交差判定
bool ColLineOBB(const FLOAT3& start, const FLOAT3& end, const OBB& obb, FLOAT3& hitPoint);
//AliceLib内のScreenToWorld関数が間違ってたので
//代わりを用意しました
_NODISCARD FLOAT3 screen_to_world(const Camera& eye,const FLOAT3& screen_pos);

class Shelter
{
private://5*5
	int map[6][5]=
	{
	//  0 1 2 3 4
		0,0,0,0,0,//0
		0,0,0,0,0,//1
		0,0,0,0,0,//2
		0,0,0,0,0,//3
		0,0,0,0,0,//4
		1,1,0,1,1,//5
	};

	enum SHELTER_STATE
	{
		SS_CHOICE,
		SS_CALCULATION,
		SS_MOVE,
		SS_REJUDGMENT
	};

	enum MOVE_VECTOR
	{
		MV_F,
		MV_B,
		MV_L,
		MV_R,
	}vector_move;

	struct BLOCK
	{
		DirectX::XMINT2		trout;
		FLOAT3				pos;
		FLOAT3				size = {1.0f,1.0f,1.0f};
		Quaternion			angles;
		int					type;
		const int			pair;

		BLOCK(DirectX::XMINT2 _trout, int _type ,int _pair = -1)
			:trout(_trout),type(_type),pair(_pair)
		{
			pos.x = static_cast<float>((trout.x - 2) *  1.0f);
			pos.z = static_cast<float>((trout.y - 2) * -1.0f);
			pos.y = 0.5f;
		}

		const bool isPair()
		{
			return (pair >= 0 && pair < BLOCK_MAX);
		}
	};

	int		state;
	
	FLOAT2	mouse_pos;
	FLOAT2	mouse_pos_o;
	
	static constexpr int BLOCK_MAX = 8;
	static constexpr float SPEED = 1.0f;
	BLOCK	blocks[BLOCK_MAX] =
	{
	//＠マップチップ上での座標	＠種類		ペア
		BLOCK({0,0},				0,		-1),// 0
		BLOCK({0,1},				0,		-1),// 1
		BLOCK({0,2},				0,		 3),// 2
		BLOCK({1,2},				0,		 2),// 3
		BLOCK({0,3},				0,		-1),// 4
		BLOCK({0,4},				0,		-1),// 5
		BLOCK({3,0},				1,		-1),// 6
		BLOCK({2,0},				0,		-1)	// 7
	};
	int		operation;

	Camera* eye;

	bool isClick();
	bool isMove(BLOCK&);
	bool Move(BLOCK&,float);

	void Maping();
	void getVector();

	Sprite cursor;

public:
	
	
	bool isClear;


	void init(Camera* camera) 
	{
		eye = camera;
		if(std::wifstream(L"Data/Sprite/cursor.dds").is_open())
		SpriteLoad(cursor, L"Data/Sprite/cursor.dds");
		assert(eye);
	}
	void update(float delta_time);


	void render();
	void Ui();

	//void damoSprite()
	//{
	//	//primitive::rect(mouse_pos_o, { 384.0f,128.0f },{ 192.0f,0.0f });
	//	SpriteRender(cursor, mouse_pos_o,
	//		ScalarToFloat2(.3f), 
	//		{},
	//		{ 384.0f,128.0f },
	//		{ 192.0f,256.0f }
	//		);
	//	SpriteRender(cursor, mouse_pos_o,
	//		ScalarToFloat2(.3f),
	//		{},
	//		{ 384.0f,128.0f },
	//		{ 192.0f,256.0f },
	//		toRadian(90.0f)
	//	);
	//	SpriteRender(cursor, mouse_pos_o,
	//		ScalarToFloat2(.3f),
	//		{},
	//		{ 384.0f,128.0f },
	//		{ 192.0f,256.0f },
	//		toRadian(180.0f)
	//	);
	//	SpriteRender(cursor, mouse_pos_o,
	//		ScalarToFloat2(.3f),
	//		{},
	//		{ 384.0f,128.0f },
	//		{ 192.0f,256.0f },
	//		toRadian(270.0f)
	//	);
	//}
};

