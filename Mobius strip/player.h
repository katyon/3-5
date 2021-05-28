#pragma once
#include "AliceLib/AliceLib.h"
#include "OBBs.h"
#include "fps_camera.h"

class Player
{
private:
	SkinnedMesh		model;

	const FLOAT3	scale;
	XMMATRIX		world_matrix;

	FLOAT3	pos;
	Quaternion posture;
	PostureVector posture_vec;

	static const float collision_distance;

	FLOAT3 horizontal_lay_start;
	FLOAT3 horizontal_lay_end;
	FLOAT3 vertical_lay_start;
	FLOAT3 vertical_lay_end;
	enum HitPointOp { SAVE, MINIMUM };

	struct DestVec
	{
		VECTOR3D right;
		VECTOR3D left;
		VECTOR3D forward;
		VECTOR3D back;
		VECTOR3D target;
	}Dest;

	FLOAT3 attract_point;
	bool auto_control;
	int auto_control_timer;

	bool moves;
	float footstep_volume = 0.0f;

	enum AUTO_PHASE
	{
		MOVE_TO_DOOR,
		OPEN_THE_DOOR,
		LEAVE_THE_ROOM,
		CLOSE_THE_DOOR,
		PHASE_END
	}auto_control_phase;

	enum AREA_TYPE
	{
		ROOM,
		CORRIDOR,
		FAKE_CORRIDOR
	}area_type;

	AREA_TYPE current_area;

public:
	Player();

	void init();
	void update(FPSCamera& camera);
	void render(const Camera& camera);

	void move(const Camera& camera);
	void updateDestVec(VECTOR3D forward);
	void restrictArea();
	void changeAnimation();

	void colDoor(FPSCamera& camera);

	void setAutoMode(FPSCamera& camera);
	void autoControl(FPSCamera& camera);

	void colWall();
	void colFloor();

	bool getControlable() { return auto_control; }

	FLOAT3& getPos() { return pos; }
	DirectX::XMMATRIX getPlayerWorldMatrix();
};