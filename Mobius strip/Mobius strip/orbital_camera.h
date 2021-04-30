#pragma once
#include "AliceLib/AliceLib.h"

class OrbitalCamera : public Camera
{
private:

	struct CursorParameter
	{
		FLOAT2 preview_pos;
		FLOAT2 current_pos;
	}Cursor;

	VECTOR3D forward;
	VECTOR3D relative_pos;
	
private:
	VECTOR2D getCursorMoveAmount();
public:
	OrbitalCamera();
	void update(XMMATRIX player_world_matrix);

	VECTOR3D getForward() { return VECTOR3D::normalize(GetTarget() - GetPos()); }
};