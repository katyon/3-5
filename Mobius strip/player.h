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

	bool moves;

public:
	Player();

	void init();
	void update();
	void render(const Camera& camera);
};