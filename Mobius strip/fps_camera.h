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
	void zoom();
	//bool getUseADS() { return useADS; }
	//void setSensitivity(int s) { correct_sensitivity = s; }
};