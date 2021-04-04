#pragma once

#include "StageData.h"

class StageManager
{
private:
	std::map<std::string, cStageModel>  model_manager;
	std::vector<StageData>				stages;
	UINT								now_stage = 0;
	
	//ƒ‚ƒfƒ‹‚ğƒ[ƒh
	void LoadModels();
public:


	template<size_t size>
	void LoadStages(std::string (&file_names)[size])
	{
		if (!stages.empty())return;
		LoadModels();
		stages.resize(size);
		for (int i = 0; i < size; i++)
		{
			stages[i].Load(file_names[i],&model_manager);
		}
	}

	void Render();

	bool Switching(UINT next);

	const UINT& getStageNum()const { return now_stage; }



};

