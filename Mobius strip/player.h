#pragma once
#include "AliceLib/AliceLib.h"

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

	bool moves;

public:
	Player();

	void init();
	void update(const Camera& camera);
	void render(const Camera& camera);

	void move(const Camera& camera);
	void updateDestVec(VECTOR3D forward);
	void restrict_area();

	void colWall();
	void colFloor();

	FLOAT3& getPos() { return pos; }
	DirectX::XMMATRIX getPlayerWorldMatrix();
};