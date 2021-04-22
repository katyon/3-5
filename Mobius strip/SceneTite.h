#pragma once
#include "AliceLib\AliceLib.h"
#include "AliceLib\Animation.h"
#include "fps_camera.h"
#include "tps_camera.h"
#include "player.h"

class SceneTitle
{
private:
	//FPSCamera camera;
	//Player player;
	SkinnedMesh title;
	FLOAT3	title_pos;
	Quaternion title_posture;

	FLOAT3 cPos;
	FLOAT3 cTarget;

	Sprite spr;
	AnimaData nowdata;

	SceneTitle();
public:
	Camera camera;

	static SceneTitle* getInstance()
	{
		static SceneTitle ins;
		return &ins;
	}

	void Initialize();

	void Update(float elapsed_time);
	void Render();
	void Uninitialize();
};