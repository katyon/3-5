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

	AmbientLight ambient;

	SceneGame();

	PipePuzzle pipe_puzzle;

	enum GameMode
	{
		normal = 0,
		menue,
		balance,
	};
	int game_mode = 0;

public:
	// í«â¡Å@É{É^ÉìâüÇµçûÇ›
	//Camera camera;
	//Camera camera;
	bool ClearButoon = false;

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

