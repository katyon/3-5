#pragma once
#include "AliceLib/AliceLib.h"
#define DEBUG_SENSITIVITY_SETTING

//class FPSCamera : public Camera
//{
//private:
//	struct CursorParameter
//	{
//		FLOAT2 preview_pos;
//		FLOAT2 current_pos;
//	}Cursor;
//
//	FLOAT3 focus_point;
//	VECTOR3D relative_focus_point;
//
//	VECTOR3D forward;
//	VECTOR3D relative_pos;
//
//	XMMATRIX rotate_to_target;
//	int magnification = 15;
//	//static int correct_sensitivity;
//
//private:
//	VECTOR2D getCursorMoveAmount();
//public:
//	// TODO:プレイヤーの視点方向にカメラを向ける処理
//
//	FPSCamera();
//	void init();
//	void update(FLOAT3 player_pos);
//
//	VECTOR3D getForward() { return forward; }
//	//void zoom();
//	//bool getUseADS() { return useADS; }
//	//void setSensitivity(int s) { correct_sensitivity = s; }
//};

class FPSCamera : public Camera
{
private:

	struct CursorParameter
	{
		FLOAT2 preview_pos;
		FLOAT2 current_pos;
	}Cursor;

	VECTOR3D forward;
	VECTOR3D relative_pos;

	FLOAT3 focus_pos;

	XMMATRIX rotate_to_target;
	int magnification = 15;
	static int correct_sensitivity;

	bool auto_focus;
	FLOAT3 focus_target;
	float complement;


	const float CAMERA_DISTANCE = 1.0f;
	const float FOCUS_RANGE = 5.0f;
private:
	VECTOR2D getCursorMoveAmount();
public:
	FPSCamera();
	void initPos();
	void update(XMMATRIX player_world_matrix, FLOAT3 center);

	void control(XMMATRIX player_world_matrix, FLOAT3 center);
	VECTOR3D getForward() { return forward; }
	void zoom();
	void setSensitivity(int s) { correct_sensitivity = s; }
	void setFocusPos(FLOAT3 pos) { focus_pos = pos; }
	void autoFin() { auto_focus = false; }

	void setAutoFocus(FLOAT3 focus_point, float complement);
	void focusCompulsion(XMMATRIX player_world_matrix, FLOAT3 center);
};