#pragma once
#include <map>
#include "AliceLib/AliceLib.h"
#include "StageData.h"



class StageEditor
{
private:

	std::map<std::string, SE_Model>	manager;
	//ƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‘‚«‚Ì“s‡ã128ŒÂŒÅ’è
	StageObject						objects[128u];
	AmbientLight					ambient;
	Camera							camera;
	bool							showV = true;
	char							stage_name[256] = "stage_data";
	
	void load_object();
	void load_stage();
	void clear_stage();
	void save();
	void Update();
	void Render();
	
	static constexpr float n180 = -(180 * OnceInRadians);//-180‹
	static constexpr float n90  = -(90 * OnceInRadians);//-90‹
	static constexpr float n30 = -(30 * OnceInRadians);//-30‹
	static constexpr float n15 = -(15 * OnceInRadians);//-15‹

	static constexpr float p180 = 180 * OnceInRadians;//180‹
	static constexpr float p90 = 90 * OnceInRadians;//90‹
	static constexpr float p30 = 30 * OnceInRadians;//30‹
	static constexpr float p15 = 15 * OnceInRadians;//15‹

	StageEditor();

	void run()
	{
		ImGuiNewFrame();
		Update();
		Render();
		ImGuiRender();
	}

public:

	static void Run()
	{
		static StageEditor ins;
		ins.run();
	}

	~StageEditor();
};

