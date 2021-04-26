#pragma once
#include "StageData.h"



inline void LoadColBoxs(const std::string& file_pass, 
	std::vector<ColBox>& data)
{
	FILE* fp = fopen(file_pass.c_str(), "r");
	if (fp)
	{
		data.clear();
		OBB obb;
		int option = -1;
		int loop_end = 0;
		//OBB�̃f�[�^�����擾
		fscanf(fp, "%d", &loop_end);
		fprintf(fp, "\n");
		//�f�[�^�����[�v����
		for (int i = 0; i < loop_end; i++)
		{
			//���W�f�[�^
			fscanf(fp, "%f,", &obb.pos.x);
			fscanf(fp, "%f,", &obb.pos.y);
			fscanf(fp, "%f,", &obb.pos.z);

			//�X�P�[���l�̃f�[�^
			fscanf(fp, "%f,", &obb.len.x);
			fscanf(fp, "%f,", &obb.len.y);
			fscanf(fp, "%f,", &obb.len.z);

			//�����x�N�g���̐����f�[�^
			//Right
			fscanf(fp, "%f,", &obb.direct.right.x);
			fscanf(fp, "%f,", &obb.direct.right.y);
			fscanf(fp, "%f,", &obb.direct.right.z);
			//Up
			fscanf(fp, "%f,", &obb.direct.up.x);
			fscanf(fp, "%f,", &obb.direct.up.y);
			fscanf(fp, "%f,", &obb.direct.up.z);
			//Forward
			fscanf(fp, "%f,", &obb.direct.forward.x);
			fscanf(fp, "%f,", &obb.direct.forward.y);
			fscanf(fp, "%f,", &obb.direct.forward.z);

			//�I�v�V����(����p�̃I�v�V����)
			fscanf(fp, "%d,", &option);

			//�f�[�^��ۑ�
			data.emplace_back(ColBox(obb, option));

			fprintf(fp, "\n");
		}
		fclose(fp);
	}
}

inline void SaveColBoxs(const std::string& stage_name,
	const std::vector<ColBox>& data)
{
	//if (std::string("When_finished") == stage_name)
	//{
	//	MessageBoxW(nullptr, L"�ʂ̖��O�ŕۑ����Ă�������", L"���̖��O�͎g�p�ł��܂���", MB_OK);
	//	return;
	//}
	std::string pass = "Data\\StageData\\";
	pass += stage_name;
	pass += "_CD.csv";
	if (checkFileExistence(pass))
	{
		int result = MessageBoxW(nullptr, L"�㏑�����ĕۑ����܂����H",
			L"�t�@�C�������ɑ��݂��܂�", MB_YESNO);
		if (result != IDYES)return;
	
	}
	FILE* fp = fopen(pass.c_str(), "w");
	if (fp)
	{
		//�f�[�^����ۑ�
		fprintf(fp, "%d \n",static_cast<int>(data.size()) );
		for (const auto& d: data)
		{
			fprintf(fp,
				"%f,%f,%f,\
				%f,%f,%f,\
				%f,%f,%f,\
				%f,%f,%f,\
				%f,%f,%f,\
				%d\n",
				d.obb.pos.x, d.obb.pos.y, d.obb.pos.z,
				d.obb.len.x, d.obb.len.y, d.obb.len.z,
				d.obb.direct.right.x, d.obb.direct.right.y, d.obb.direct.right.z,
				d.obb.direct.up.x, d.obb.direct.up.y, d.obb.direct.up.z,
				d.obb.direct.forward.x, d.obb.direct.forward.y, d.obb.direct.forward.z,
				d.option);
		}
		fclose(fp);
	}
}

class CollisionEditer
{
private:

public:
};

