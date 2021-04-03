#pragma once

#include "StageData.h"

class StageManager
{
private:
	std::map<std::string, cStageModel>  model_manager;
	std::vector<StageData>			    stages;
public:

	//モデルをロード
	void LoadModels();

	template<size_t size>
	void LoadStages(std::string file_names[size])
	{
		//念のためのモデルのロードをしておく
		LoadModels();
		//必要なデータだけ渡してそれ以外は
		//ステージデータ構造体のコンストラクタに丸投げ
		for (auto file_name : file_names)
		{
			stages.push_back(file_name,&model_manager);
		}
	}



};

