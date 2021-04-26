#pragma once
#include "StageData.h"



inline void LoadColBoxs(const std::string& file_pass, 
	std::vector<ColBox>& data)
{
	//�t�@�C����������ΏI��
	if (!checkFileExistence(file_pass))return;
	//�t�@�C���|�C���^���擾
	FILE* fp = fopen(file_pass.c_str(), "r");
	if (fp)
	{
		//�f�[�^����ɂ��Ă���
		data.clear();
		int data_size = 0;
		//�f�[�^�����擾
		fscanf(fp, "%d", &data_size);
		fprintf(fp, "\n");
		//�f�[�^��0�ɖ����Ȃ��ꍇ�I��
		if (data_size <= 0)
		{
			fclose(fp);
			return;
		}
		//�f�[�^���������R���e�i���쐬����
		data.resize(static_cast<size_t>(data_size));
		//�f�[�^�����[�v����
		for (auto& d: data)
		{
			//���W�f�[�^
			fscanf(fp, "%f,", &d.obb.pos.x);
			fscanf(fp, "%f,", &d.obb.pos.y);
			fscanf(fp, "%f,", &d.obb.pos.z);

			//�X�P�[���l�̃f�[�^
			fscanf(fp, "%f,", &d.obb.len.x);
			fscanf(fp, "%f,", &d.obb.len.y);
			fscanf(fp, "%f,", &d.obb.len.z);

			//�����x�N�g���̐����f�[�^
			//Right
			fscanf(fp, "%f,", &d.obb.direct.right.x);
			fscanf(fp, "%f,", &d.obb.direct.right.y);
			fscanf(fp, "%f,", &d.obb.direct.right.z);
			//Up
			fscanf(fp, "%f,", &d.obb.direct.up.x);
			fscanf(fp, "%f,", &d.obb.direct.up.y);
			fscanf(fp, "%f,", &d.obb.direct.up.z);
			//Forward
			fscanf(fp, "%f,", &d.obb.direct.forward.x);
			fscanf(fp, "%f,", &d.obb.direct.forward.y);
			fscanf(fp, "%f,", &d.obb.direct.forward.z);

			//�I�v�V����(����p�̃I�v�V����)
			fscanf(fp, "%d,", &d.option);

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

