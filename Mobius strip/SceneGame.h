#pragma once

#include "AliceLib\AliceLib.h"

class SceneGame
{
private:
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

