#pragma once
#include "AliceLib/AliceLib.h"

class TPSCamera : public Camera
{
private:

	struct CursorParameter
	{
		FLOAT2 preview_pos;
		FLOAT2 current_pos;
	}Cursor;

	VECTOR3D forward;
	VECTOR3D relative_pos;

	XMMATRIX rotate_to_target;
	int magnification = 15;
	static int correct_sensitivity;
	bool useADS;
private:
	VECTOR2D getCursorMoveAmount();
public:
	TPSCamera();
	void initPos();
	void update(XMMATRIX player_world_matrix, FLOAT3 center);

	VECTOR3D getForward() { return forward; }
	void zoom();
	bool getUseADS() { return useADS; }
	void setSensitivity(int s) { correct_sensitivity = s; }
};