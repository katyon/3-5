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

	FLOAT3& getPos() { return pos; }
	DirectX::XMMATRIX getPlayerWorldMatrix();
};