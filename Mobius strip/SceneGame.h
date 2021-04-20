#pragma once
#include "AliceLib\AliceLib.h"
#include "PipePuzzle.h"
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

	PipePuzzle pipe_puzzle;


public:
	// 追加　ボタン押し込み
	//Camera camera;
	//Camera camera;

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

