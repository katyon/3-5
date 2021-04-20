#pragma once
#include "AliceLib\AliceLib.h"
#include "fps_camera.h"
#include "tps_camera.h"
#include "player.h"

class SceneGame
{
private:
	FPSCamera camera;
	Player player;
	SkinnedMesh stage;

	SceneGame();
public:

	static SceneGame* getInstance()
	{
		static SceneGame ins;
		return &ins;
	}

	void Initialize();

	void Update(float elapsed_time);
	void Render();

	void Uninitialize();

};

