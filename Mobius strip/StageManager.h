#pragma once

#include "StageData.h"

class StageManager
{
private:
	std::map<std::string, cStageModel>  model_manager;
	std::vector<StageData>			    stages;
public:

	//���f�������[�h
	void LoadModels();

	template<size_t size>
	void LoadStages(std::string file_names[size])
	{
		//�O�̂��߂̃��f���̃��[�h�����Ă���
		LoadModels();
		//�K�v�ȃf�[�^�����n���Ă���ȊO��
		//�X�e�[�W�f�[�^�\���̂̃R���X�g���N�^�Ɋۓ���
		for (auto file_name : file_names)
		{
			stages.push_back(file_name,&model_manager);
		}
	}



};

