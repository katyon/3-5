#pragma once
#include <map>
#include "AliceLib/AliceLib.h"




struct StageObject
{
	std::string		ID;
	FLOAT3			position;
	FLOAT3			scales;
	Quaternion		posture;
	bool			isShow = true;
	ModelReplica	body;

	void	Load(Model*		body_data,const StageObject&	data)
	{
		ID = data.ID;
		position = data.position;
		scales = data.scales;
		posture = data.posture;
		isShow = data.isShow;
		body.SetModel(body_data);
	}
	
	void	Render() { isShow ? ModelRender(body, position, scales, posture) : 0; }


	void	Clear()
	{
		ID = "";
		position = {};
		scales = { 1.0f,1.0f,1.0f };
		posture.reset();
		body.ReSet();
	}
};


struct SE_Model
{
	Model m;
	SE_Model(std::string file_pass)
	{
		//全てのモデルはMayaで作られているていで設定
		ModelLoad(m, file_pass.c_str(),MAYA);
	}
};

class StageEditor
{
private:

	std::map<std::string, SE_Model>	manager;
	//ファイルの読み書きの都合上128個固定
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
	
	static constexpr float n180 = -(180 * OnceInRadians);//-180°
	static constexpr float n90  = -(90 * OnceInRadians);//-90°
	static constexpr float n30 = -(30 * OnceInRadians);//-30°
	static constexpr float n15 = -(15 * OnceInRadians);//-15°

	static constexpr float p180 = 180 * OnceInRadians;//180°
	static constexpr float p90 = 90 * OnceInRadians;//90°
	static constexpr float p30 = 30 * OnceInRadians;//30°
	static constexpr float p15 = 15 * OnceInRadians;//15°

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

