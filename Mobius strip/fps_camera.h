#pragma once
#include "AliceLib/AliceLib.h"

class FPSCamera : public Camera
{
private:
	struct CursorParameter
	{
		FLOAT2 preview_pos;
		FLOAT2 current_pos;
	}Cursor;

	FLOAT3 focus_point;
	VECTOR3D relative_focus_point;

	VECTOR3D forward;
	VECTOR3D relative_pos;

	XMMATRIX rotate_to_target;
	int magnification = 15;
	//static int correct_sensitivity;

private:
	VECTOR2D getCursorMoveAmount();
public:
	// TODO:プレイヤーの視点方向にカメラを向ける処理

	FPSCamera();
	void init();
	void update(XMMATRIX player_world_matrix, FLOAT3 center);

	VECTOR3D getForward() { return forward; }
	//void zoom();
	//bool getUseADS() { return useADS; }
	//void setSensitivity(int s) { correct_sensitivity = s; }
};

// ---kiira_develop---
// 
//SpriteLoad(1, L"Data/Sprite/center.png");
//Camera camera;
//camera.SetPos({ 0, 0, -30 });

//Player player;
//player.init();


//player.update();
//camera.SetTarget({ 0.0f,5.0f,0.0f });
//
//player.render(camera);
//
//FLOAT2 center = ToClient(GetWindowSize() / 2.0f);
//SetCursorPos(center.x, center.y);
//
//SpriteRender(1, (GetWindowSize() / 2.0f), { 0.2f, 0.2f }, { 0, 0 }, { 0, 0 }, { 300.0f, 400.0f });
//--------------------------