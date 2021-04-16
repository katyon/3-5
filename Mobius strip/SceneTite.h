#pragma once
#include "AliceLib\AliceLib.h"
class SceneTitle
{
private:
	SceneTitle();
public:

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

