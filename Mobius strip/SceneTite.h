#pragma once
#include "AliceLib\AliceLib.h"
#include "fps_camera.h"
#include "tps_camera.h"
#include "player.h"

class SceneTitle
{
private:
	//FPSCamera camera;
	//Player player;
	//SkinnedMesh stage;

	SceneTitle();
public:
	//Camera camera;

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

