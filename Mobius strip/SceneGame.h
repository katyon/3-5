#pragma once

#include "AliceLib\AliceLib.h"

class SceneGame
{
private:
	SceneGame();
public:
	// �ǉ��@�{�^����������
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

