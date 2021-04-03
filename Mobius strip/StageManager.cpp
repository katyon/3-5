#include "StageManager.h"

//�X�e�[�W�G�f�B�^�[�Ŏ����ς�
bool getFileNames(std::string folderPath, std::vector<std::string>& file_names);

void StageManager::LoadModels()
{
	std::vector<std::string> load_files;
	//	Data\\Objects�t�H���_���ɂ���S�Ẵt�@�C�����擾
	if (getFileNames("Data\\Objects", load_files))
	{
		for (auto& file_pass : load_files)
		{
			static std::vector<std::string> fo;
			fo.clear();
			fo = Split(file_pass, '.');
			std::string f = fo.at(fo.size() - 1u);
			std::transform(f.begin(), f.end(), f.begin(), tolower);
			//���f���t�@�C���ȊO�͖���
			if (f != "obj" && f != "fbx")continue;
			//���d���[�h�΍�
			auto it = model_manager.find(file_pass.substr(strlen("Data\\Objects\\")));
			if (it == model_manager.end())
			{
				model_manager.insert(std::make_pair(file_pass.substr(strlen("Data\\Objects\\")), file_pass));
			}
		}
	}
}
